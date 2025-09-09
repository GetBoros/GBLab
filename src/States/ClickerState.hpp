// src/States/ClickerState.hpp

#pragma once

#include <raylib.h>

#include "States/State.hpp"

class Application;  // Опережающее объявление

class ClickerState final : public State
{
public:
    ClickerState(Application& app);
    ~ClickerState() override;

    // Реализуем "контракт" базового класса
    void HandleInput() override;
    void Update(float deltaTime) override;
    void Draw() override;

private:
    Application& _app;  // Ссылка на главный класс приложения
};