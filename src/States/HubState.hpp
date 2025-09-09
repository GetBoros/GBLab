// src/States/HubState.hpp

#pragma once

#include <raylib.h>

#include <memory>  // Для std::unique_ptr
#include <vector>  // Подключаем std::vector

#include "Components/Icon.hpp"  // Подключаем наш новый компонент
#include "States/State.hpp"

enum class HubIcon
{
    Clicker,
    Exit
};

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
    std::vector<std::unique_ptr<Icon>> _icons;
};