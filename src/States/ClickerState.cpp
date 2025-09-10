// src/States/ClickerState.cpp

#include "States/ClickerState.hpp"

#include <format>
#include <string>

#include "Core/Application.hpp"
#include "Core/Config/Config.hpp"
#include "Core/StateManager.hpp"

ClickerState::ClickerState(Application &app, StateManager &stateManager)
    : _app(app), _stateManager(stateManager), _clickCount(0)
{
    // Определяем геометрию кнопки
    const float buttonWidth = 200.0f;
    const float buttonHeight = 100.0f;
    Rectangle buttonBounds = {(AsConfig::WindowWidth - buttonWidth) / 2, (AsConfig::WindowHeight - buttonHeight) / 2,
                              buttonWidth, buttonHeight};

    // Создаем наш объект Button одной строкой!
    _clickerButton = std::make_unique<Button>(buttonBounds, "Кликай!", AsConfig::DefaultFontSize, _app.GetFont());

    TraceLog(LOG_INFO, "ClickerState Constructed");
}

ClickerState::~ClickerState()
{
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