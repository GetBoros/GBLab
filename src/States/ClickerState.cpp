// src/States/ClickerState.cpp

#include "States/ClickerState.hpp"

#include <format>  // Для std::format
#include <string>  // Для std::to_string

#include "Core/Application.hpp"

// Конструктор: инициализируем все наши переменные
ClickerState::ClickerState(Application& app) : _app(app), _clickCount(0), _buttonColor(MAROON)  // Начальный цвет кнопки
{
    // Определяем геометрию кнопки. Разместим ее по центру.
    const float buttonWidth = 200.0f;
    const float buttonHeight = 100.0f;
    // Координаты окна у нас 800x450
    _clickButton = {(800 - buttonWidth) / 2, (450 - buttonHeight) / 2, buttonWidth, buttonHeight};

    TraceLog(LOG_INFO, "ClickerState Constructed");
}

ClickerState::~ClickerState()
{
    TraceLog(LOG_INFO, "ClickerState Destructed");
}

void ClickerState::HandleInput()
{
    // Возврат в меню по Backspace
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        _app.PopState();
    }

    // Проверяем клик по кнопке
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(GetMousePosition(), _clickButton))
        {
            _clickCount++;  // Увеличиваем счетчик!
        }
    }
}

void ClickerState::Update(float deltaTime)
{
    // Этот метод идеально подходит для визуальных эффектов, не связанных с кликом.
    // Например, изменение цвета кнопки при наведении мыши.
    if (CheckCollisionPointRec(GetMousePosition(), _clickButton))
    {
        _buttonColor = RED;  // Мышь над кнопкой - делаем ее ярче
    }
    else
    {
        _buttonColor = MAROON;  // Мышь ушла - возвращаем обычный цвет
    }
}

void ClickerState::Draw()
{
    // 1. Рисуем фон (хотя у нас уже есть глобальный полупрозрачный)
    // Для этого состояния можно сделать его чуть другим, например, темнее.
    DrawRectangle(0, 0, 800, 450, Fade(BLACK, 0.3f));

    // 2. Рисуем саму кнопку
    DrawRectangleRec(_clickButton, _buttonColor);

    // 3. Рисуем текст на кнопке
    const char* buttonText = "Кликай!";
    const Font& font = _app.GetFont();
    const Vector2 textSize = MeasureTextEx(font, buttonText, 20, 1);
    const Vector2 textPos = {_clickButton.x + (_clickButton.width - textSize.x) / 2,
                             _clickButton.y + (_clickButton.height - textSize.y) / 2};
    DrawTextEx(font, buttonText, textPos, 20, 1, WHITE);

    // 4. Рисуем счетчик кликов над кнопкой
    std::string scoreText = std::format("Сделано кликов: {}", _clickCount);
    const Vector2 scoreTextSize = MeasureTextEx(font, scoreText.c_str(), 30, 2);
    const Vector2 scorePos = {(800 - scoreTextSize.x) / 2, _clickButton.y - 50};
    DrawTextEx(font, scoreText.c_str(), scorePos, 30, 2, RAYWHITE);

    // 5. Рисуем подсказку для выхода
    DrawTextEx(font, "Нажми Backspace для возврата в меню", {210, 400}, 20, 1, LIGHTGRAY);
}
