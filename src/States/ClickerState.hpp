// src/States/ClickerState.hpp

#pragma once

#include <raylib.h>

#include <memory>  // Для std::unique_ptr

#include "Components/Button.hpp"  // Подключаем наш новый компонент
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
    long long _clickCount;

    // Заменяем Rectangle и Color на один умный указатель на нашу кнопку!
    std::unique_ptr<Button> _clickerButton;
};