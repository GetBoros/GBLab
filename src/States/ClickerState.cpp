// src/States/ClickerState.cpp

#include "States/ClickerState.hpp"

#include <chrono>
#include <ctime>
#include <format>
#include <fstream>
#include <string>

#include "Core/Application.hpp"
#include "Core/Config/Config.hpp"
#include "Core/StateManager.hpp"

ClickerState::ClickerState(Application &app, StateManager &stateManager)
    : _app(app), _stateManager(stateManager), _clickCount(0), _sessionCount(0)
{
    // Определяем геометрию кнопки
    const float buttonWidth = 200.0f;
    const float buttonHeight = 100.0f;
    Rectangle buttonBounds = {(AsConfig::WindowWidth - buttonWidth) / 2, (AsConfig::WindowHeight - buttonHeight) / 2,
                              buttonWidth, buttonHeight};

    std::ifstream saveFile(AsConfig::GetClickerSavePath());

    // Создаем наш объект Button одной строкой!
    _clickerButton = std::make_unique<Button>(buttonBounds, "Кликай!", AsConfig::DefaultFontSize, _app.GetFont());

    TraceLog(LOG_INFO, "ClickerState Constructed");

    // Проверяем, открылся ли файл и не пуст ли он
    if (!saveFile.is_open())
    {
        // Файла нет (первый запуск), ничего не делаем, _score останется 0
        return;
    }

    // 2. Создаем JSON-объект, в который будем парсить данные
    nlohmann::json loadData;
    try
    {
        saveFile >> loadData;

        // Загружаем 'score'. Метод .value() великолепен:
        // если ключ "score" есть, он вернет его значение.
        // Если ключа нет, он вернет значение по умолчанию (второй аргумент), не вызывая ошибки!
        _clickCount = loadData.value("score", 0LL);  // 0LL - long long

        // Точно так же загружаем 'sessionCount'
        _sessionCount = loadData.value("sessionCount", 0);
        TraceLog(LOG_INFO, "Last session count was : %lld", _sessionCount);

        // Дату последнего сохранения можно просто вывести в лог для проверки
        if (loadData.contains("lastSaveTime"))
        {
            std::string lastSave = loadData.value("lastSaveTime", "never");
            TraceLog(LOG_INFO, "Last save time was: %s", lastSave.c_str());
        }
    }
    catch (const nlohmann::json::parse_error &e)
    {
        // Обработка ошибки, если файл поврежден
        TraceLog(LOG_WARNING, "JSON parse error in clicker save: %s", e.what());
    }
}

ClickerState::~ClickerState()
{
    // -- -ЛОГИКА СОХРАНЕНИЯ-- -
    // Открываем файл для записи. Если файла нет, он будет создан.
    // Если есть, его содержимое будет перезаписано.
    std::ofstream saveFile(AsConfig::GetClickerSavePath());

    nlohmann::json saveData;

    // 1. Увеличиваем счетчик сессий ПЕРЕД сохранением
    _sessionCount++;

    // 2. Получаем текущее время
    const auto now = std::chrono::system_clock::now();
    const auto time_t_now = std::chrono::system_clock::to_time_t(now);
    // std::put_time требует буфер, безопаснее использовать std::string
    char time_buf[26];
    ctime_r(&time_t_now, time_buf);  // Используем потокобезопасную ctime_r
    std::string time_str(time_buf);
    time_str.pop_back();  // Убираем лишний символ новой строки, который добавляет ctime_r

    // 3. Наполняем JSON-объект новыми данными
    saveData["score"] = _clickCount;
    saveData["sessionCount"] = _sessionCount;
    saveData["lastSaveTime"] = time_str;

    if (saveFile.is_open())
    {
        saveFile << saveData.dump(4);
        TraceLog(LOG_INFO, "Clicker score saved: %lld", _clickCount);
    }
    else
    {
        TraceLog(LOG_ERROR, "Failed to open save file for writing!");
    }

    TraceLog(LOG_INFO, "ClickerState Destructed");
}

// HandleInput теперь не нужен, т.к. кнопка сама обрабатывает ввод в своем Update
void ClickerState::HandleInput()
{
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        _stateManager.PopState();
    }
}

// Update стал невероятно простым!
void ClickerState::Update(float deltaTime)
{
    // Просто обновляем кнопку
    _clickerButton->Update();

    // И спрашиваем ее, была ли она нажата
    if (_clickerButton->IsClicked())
    {
        _clickCount++;
    }
}

// Draw тоже стал намного чище
void ClickerState::Draw()
{
    DrawRectangle(0, 0, AsConfig::WindowWidth, AsConfig::WindowHeight, Fade(BLACK, 0.3f));

    // Просто просим кнопку нарисовать себя
    _clickerButton->Draw();

    // Логика отрисовки счета и подсказок остается здесь
    std::string scoreText = std::format("Сделано кликов: {}", _clickCount);
    const Vector2 scoreTextSize = MeasureTextEx(_app.GetFont(), scoreText.c_str(), 30, 2);
    const Vector2 scorePos = {(800 - scoreTextSize.x) / 2, 150};  // y-координату лучше задать явно
    DrawTextEx(_app.GetFont(), scoreText.c_str(), scorePos, 30, 2, RAYWHITE);

    DrawTextEx(_app.GetFont(), "Нажми Backspace для возврата в меню", {210, 400}, 20, 1, LIGHTGRAY);
}