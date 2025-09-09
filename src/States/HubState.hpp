// src/States/HubState.hpp

#pragma once

#include <raylib.h>

#include <memory>  // Для std::unique_ptr

#include "Components/Icon.hpp"  // Подключаем наш новый компонент
#include "States/State.hpp"

class Application;

class HubState final : public State
{
public:
    HubState(Application& app);
    ~HubState() override;

    void HandleInput() override;
    void Update(float deltaTime) override;
    void Draw() override;

private:
    Application& _app;

    // Храним нашу иконку в умном указателе.
    // Это гарантирует, что она будет правильно создана и уничтожена вместе с HubState.
    std::unique_ptr<Icon> _clickerIcon;
};