// src/States/HubState.hpp

#pragma once

#include <raylib.h>

#include "States/State.hpp"

class Application;  // Опережающее объявление. Мы говорим "такой класс есть", чтобы использовать указатель на него.

class HubState final : public State
{
public:
    // Конструктор теперь принимает указатель на Application
    HubState(Application& app);
    ~HubState() override;

    void HandleInput() override;
    void Update(float deltaTime) override;
    void Draw() override;

private:
    Application& _app;  // Ссылка на главный класс приложения
};