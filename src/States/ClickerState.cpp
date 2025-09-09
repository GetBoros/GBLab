// src/States/ClickerState.cpp

#include "States/ClickerState.hpp"

#include "Core/Application.hpp"  // Подключаем полный заголовок для доступа к методам app

ClickerState::ClickerState(Application& app) : _app(app)
{
    TraceLog(LOG_INFO, "ClickerState Constructed");
}

ClickerState::~ClickerState()
{
    TraceLog(LOG_INFO, "ClickerState Destructed");
}

void ClickerState::HandleInput()
{
    // При нажатии Escape мы выходим из этого состояния
    // !!! if (IsKeyPressed(KEY_ESCAPE))
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        _app.PopState();  // Снимаем текущее состояние (ClickerState) со стека
    }
}

void ClickerState::Update(float deltaTime)
{
    // Пока пусто. Здесь будет логика кликера.
}

void ClickerState::Draw()
{
    // Просто рисуем текст, чтобы идентифицировать это состояние
    DrawTextEx(_app.GetFont(), "Это Кликер!", {300, 200}, 32, 2, SKYBLUE);
    DrawTextEx(_app.GetFont(), "Нажми ESC для возврата в меню", {210, 240}, 20, 1, LIGHTGRAY);
}