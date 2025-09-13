// src/States/ClickerState.cpp

#include "States/ClickerState.hpp"

#include <chrono>
#include <ctime>
#include <format>
#include <fstream>
#include <string>

#include "ClickerState.hpp"
#include "Core/Application.hpp"
#include "Core/Config/Config.hpp"
#include "Core/StateManager.hpp"

ClickerState::ClickerState(Application &app, StateManager &stateManager)
    : _app(app), _stateManager(stateManager), _clickCount(0), _sessionCount(0)
{
    // 1. Создаем кнопку (она ни от чего не зависит)
    const float buttonWidth = 200.0f;
    const float buttonHeight = 100.0f;
    Rectangle buttonBounds = {(AsConfig::WindowWidth - buttonWidth) / 2, (AsConfig::WindowHeight - buttonHeight) / 2,
                              buttonWidth, buttonHeight};
    _clickerButton = std::make_unique<Button>(buttonBounds, "Кликай!", AsConfig::DefaultFontSize, _app.GetFont());

    // 2. Загружаем данные из файла, обновляя _clickCount
    std::ifstream saveFile(AsConfig::GetClickerSavePath());
    if (saveFile.is_open())
    {
        try
        {
            nlohmann::json loadData;
            saveFile >> loadData;
            _clickCount = loadData.value("score", 0LL);
            _sessionCount = loadData.value("sessionCount", 0);
            // ... остальная логика загрузки ...
        }
        catch (const nlohmann::json::parse_error &e)
        {
            TraceLog(LOG_WARNING, "JSON parse error: %s", e.what());
        }
    }

    // 3. И ТОЛЬКО ТЕПЕРЬ создаем/обновляем лейбл, когда все данные готовы
    _updateScoreLabel();

    TraceLog(LOG_INFO, "ClickerState Constructed");
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
// --- КРОСС-ПЛАТФОРМЕННОЕ РЕШЕНИЕ ---
#if defined(__linux__) || defined(__APPLE__)
    // На Linux/macOS используем потокобезопасную ctime_r
    ctime_r(&time_t_now, time_buf);
#elif defined(_WIN32)
    // На Windows используем "безопасную" ctime_s
    ctime_s(time_buf, sizeof(time_buf), &time_t_now);
#endif
    // ------------------------------------
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

void ClickerState::HandleInput()
{
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        _stateManager.PopState();
    }
}

void ClickerState::Update(float deltaTime)
{
    // Просто обновляем кнопку
    _clickerButton->Update();

    // И спрашиваем ее, была ли она нажата
    if (_clickerButton->IsClicked())
    {
        _clickCount++;
        _updateScoreLabel();
    }
}

void ClickerState::Draw()
{
    DrawRectangle(0, 0, AsConfig::WindowWidth, AsConfig::WindowHeight, Fade(BLACK, 0.3f));

    _scoreLabel->Draw();
    _clickerButton->Draw();

    DrawTextEx(_app.GetFont(), "Нажми Backspace для возврата в меню", {210, 400}, 20, 1, LIGHTGRAY);
}

void ClickerState::_updateScoreLabel()
{
    // 1. Формируем новый текст
    std::string newScoreText = std::format("Сделано кликов: {}", _clickCount);

    // 2. Если лейбл еще не создан (первый вызов из конструктора), создаем его
    if (!_scoreLabel)
    {
        const float fontSize = 30.0f;
        const float fontSpacing = 2.0f;
        const Vector2 scoreTextSize = MeasureTextEx(_app.GetFont(), newScoreText.c_str(), fontSize, fontSpacing);
        const Vector2 scorePos = {(AsConfig::WindowWidth - scoreTextSize.x) / 2.0f, 150.0f};
        _scoreLabel = std::make_unique<Label>(newScoreText, scorePos, _app.GetFont(), fontSize, RAYWHITE, fontSpacing);
    }
    // 3. Если лейбл уже существует, просто обновляем его
    else
    {
        _scoreLabel->SetText(newScoreText);
        // Пересчитываем позицию для центрирования
        const Vector2 scoreTextSize = MeasureTextEx(_app.GetFont(), newScoreText.c_str(), 30.0f, 2.0f);
        const Vector2 newScorePos = {(AsConfig::WindowWidth - scoreTextSize.x) / 2.0f, 150.0f};
        _scoreLabel->SetPosition(newScorePos);
    }
}