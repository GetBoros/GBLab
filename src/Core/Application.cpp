// src/Core/Application.cpp

#include "Core/Application.hpp"

#include <format>
#include <vector>

#include "Core/Config/Config.hpp"
#include "States/HubState.hpp"  // Подключаем наше первое конкретное состояние

Application::Application(int width, int height, const std::string& title)
    : _screenWidth(width), _screenHeight(height), _cyrillicFont{}
{
    SetConfigFlags(FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TOPMOST);
    InitWindow(_screenWidth, _screenHeight, title.c_str());
    SetTargetFPS(30);

    LoadAssets();

    // --- Инициализируем машину состояний ---
    // Сразу после запуска "включаем" наш первый "канал" - HubState
    // PushState(std::make_unique<HubState>());
    PushState(std::make_unique<HubState>(*this));
}

Application::~Application()
{
    // Очищаем стек состояний перед выходом
    while (!_states.empty())
    {
        PopState();
    }

    UnloadAssets();
    CloseWindow();
}

// --- Реализация новых методов ---

void Application::PushState(std::unique_ptr<State> state)
{
    _states.push(std::move(state));  // Перемещаем владение указателем в стек
}

void Application::PopState()
{
    if (!_states.empty())
    {
        _states.pop();  // unique_ptr автоматически вызовет деструктор и освободит память
    }
}

// ... методы LoadAssets и UnloadAssets остаются без изменений ...
// (просто скопируй их из своей текущей версии)

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

// --- Главное изменение: обновляем метод Run() ---

void Application::Run()
{
    // Логику перетаскивания окна оставляем здесь, т.к. она глобальна для приложения
    Vector2 windowPos = {100.0f, 100.0f};
    SetWindowPosition(static_cast<int>(windowPos.x), static_cast<int>(windowPos.y));
    bool isDragging = false;
    Vector2 dragOffset = {0.0f, 0.0f};

    while (!WindowShouldClose() && !_states.empty())  // Цикл работает, пока есть состояния
    {
        // Получаем указатель на текущее активное состояние (верхнее в стеке)
        State* currentState = _states.top().get();

        // --- Логика обновления ---

        // Глобальная логика (перетаскивание)
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            isDragging = true;
            dragOffset = GetMousePosition();
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            isDragging = false;
        }
        if (isDragging)
        {
            Vector2 currentMousePos = GetMousePosition();
            windowPos.x += currentMousePos.x - dragOffset.x;
            windowPos.y += currentMousePos.y - dragOffset.y;
            SetWindowPosition(static_cast<int>(windowPos.x), static_cast<int>(windowPos.y));
        }

        // Делегируем обработку ввода текущему состоянию
        currentState->HandleInput();
        if (_states.empty() || currentState != _states.top().get())
        {
            continue;  // Начать следующую итерацию цикла немедленно
        }

        // Делегируем обновление логики текущему состоянию
        currentState->Update(GetFrameTime());

        // --- Отрисовка ---
        BeginDrawing();
        {
            ClearBackground(BLANK);
            DrawRectangle(0, 0, _screenWidth, _screenHeight, Fade(DARKGRAY, 0.7f));

            // Делегируем отрисовку текущему состоянию
            currentState->Draw();
        }
        EndDrawing();
    }
}