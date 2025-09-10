// src/States/HubState.hpp

#pragma once

#include <raylib.h>

#include <memory>  // Для std::unique_ptr
#include <vector>  // Подключаем std::vector

#include "Components/Icon.hpp"
#include "States/ClickerState.hpp"
#include "States/State.hpp"

enum class HubIcon
{
    Clicker,
    Logger,  // <--- Добавляем новую иконку
    Exit
};

class Application;
class StateManager;

class HubState final : public State
{
public:
    // Конструктор теперь принимает Application (для ресурсов) и StateManager (для навигации)
    HubState(Application &app, StateManager &stateManager);
    ~HubState() override;

    void HandleInput() override;
    void Update(float deltaTime) override;
    void Draw() override;

private:
    Application &_app;
    StateManager &_stateManager;

    // Храним нашу иконку в умном указателе.
    // Это гарантирует, что она будет правильно создана и уничтожена вместе с HubState.
    std::vector<std::unique_ptr<Icon>> _icons;
};