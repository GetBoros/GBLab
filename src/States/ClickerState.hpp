// src/States/ClickerState.hpp

#pragma once

#include <raylib.h>

#include "States/State.hpp"

class Application;

class ClickerState final : public State
{
public:
    ClickerState(Application& app);
    ~ClickerState() override;

    void HandleInput() override;
    void Update(float deltaTime) override;
    void Draw() override;

private:
    Application& _app;

    // --- Новые поля для логики кликера ---

    long long _clickCount;   // Используем long long на случай, если ты очень увлечешься :)
    Rectangle _clickButton;  // Прямоугольник, описывающий нашу кнопку
    Color _buttonColor;      // Цвет кнопки, который мы будем менять
};