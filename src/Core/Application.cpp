#include "Core/Application.hpp"

// --- НАЧАЛО ИСПРАВЛЕНИЯ: Кросс-платформенные инклюды ---
#if defined(__linux__) || defined(__APPLE__)
#include <unistd.h>  // Для getcwd в Linux/macOS
#elif defined(_WIN32)
#include <direct.h>  // Для _getcwd в Windows
#endif

#include <format>
#include <vector>

#include "Core/Config/Config.hpp"
#include "States/HubState.hpp"

Application::Application(int width, int height, const std::string &title)
    : _screenWidth(width), _screenHeight(height), _cyrillicFont{}
{
    // ... InitWindow, SetTargetFPS ...
    SetConfigFlags(FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TOPMOST);
    InitWindow(_screenWidth, _screenHeight, title.c_str());
    SetTargetFPS(60);

    LoadAssets();

    // Создаем StateManager
    _stateManager = std::make_unique<StateManager>(*this);
    _stateManager->PushState(std::make_unique<HubState>(*this, *_stateManager));
    _stateManager->ProcessStateChanges();
    char currentPath[1024];
    char *result = nullptr;  // Используем общую переменную для результата

#if defined(__linux__) || defined(__APPLE__)
    result = getcwd(currentPath, sizeof(currentPath));
#elif defined(_WIN32)
    result = _getcwd(currentPath, sizeof(currentPath));
#endif

    if (result != nullptr)
    {
        TraceLog(LOG_WARNING, "Current Working Directory is: %s", currentPath);
    }
    else
    {
        TraceLog(LOG_ERROR, "Failed to get current working directory!");
    }
}

Application::~Application()
{
    // --- ПРАВИЛЬНЫЙ ПОРЯДОК ---

    // 1. Сначала уничтожаем StateManager.
    // Это приведет к вызову деструкторов всех активных состояний,
    // которые, в свою очередь, вызовут деструкторы всех иконок и кнопок,
    // и все текстуры будут корректно выгружены, ПОКА ГРАФИЧЕСКИЙ КОНТЕКСТ ЕЩЕ ЖИВ.
    _stateManager.reset();  // У unique_ptr есть метод reset() для явного уничтожения объекта.

    // 2. Затем выгружаем глобальные ресурсы самого приложения (шрифт).
    UnloadAssets();

    // 3. И только в самом конце, когда все наши ресурсы освобождены,
    // мы закрываем окно и уничтожаем графический контекст.
    CloseWindow();
}

void Application::LoadAssets()
{
    // Путь к нашему шрифту в папке assets
    const std::string fontPath = std::format("{}/fonts/DejaVuSans.ttf", ASSETS_PATH);
    TraceLog(LOG_INFO, "Loading font from: %s", fontPath.c_str());

    // --- Новый, надежный способ загрузки символов ---
    std::vector<int> codepoints;

    // 1. Добавляем базовые символы (ASCII 32-126)
    for (int i = 32; i <= 126; ++i)
    {
        codepoints.push_back(i);
    }

    // 2. Добавляем весь основной кириллический блок из Unicode
    for (int i = 0x0400; i <= 0x04FF; ++i)
    {
        codepoints.push_back(i);
    }

    // Загружаем шрифт с сгенерированным набором символов
    _cyrillicFont = LoadFontEx(fontPath.c_str(), 32, codepoints.data(), codepoints.size());

    TraceLog(LOG_INFO, "Loaded %d glyphs into font.", _cyrillicFont.glyphCount);  // Обрати внимание
}

void Application::UnloadAssets()
{
    UnloadFont(_cyrillicFont);
}

void Application::Run()
{
    // Логику перетаскивания окна оставляем здесь, т.к. она глобальна для приложения
    Vector2 windowPos = {100.0f, 100.0f};
    SetWindowPosition(static_cast<int>(windowPos.x), static_cast<int>(windowPos.y));
    bool isDragging = false;
    Vector2 dragOffset = {0.0f, 0.0f};

    while (!WindowShouldClose() && !_stateManager->IsEmpty())
    {
        // 1. Применяем все отложенные изменения состояний
        _stateManager->ProcessStateChanges();

        // 2. Обновляем логику текущего состояния
        _stateManager->Update(GetFrameTime());

        // --- Отрисовка ---
        BeginDrawing();
        {
            ClearBackground(BLANK);
            DrawRectangle(0, 0, _screenWidth, _screenHeight, Fade(DARKGRAY, 0.7f));

            // 3. Рисуем текущее состояние
            _stateManager->Draw();
        }
        EndDrawing();
    }
}