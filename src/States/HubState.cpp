// src/States/HubState.cpp

#include "States/HubState.hpp"

#include "Core/Application.hpp"  // Теперь подключаем полный заголовок здесь

HubState::HubState(Application& app) : _app(app)  // Инициализируем ссылку
{
    TraceLog(LOG_INFO, "HubState Constructed");
}

HubState::~HubState()
{
    TraceLog(LOG_INFO, "HubState Destructed");
}

void HubState::HandleInput()
{
    // Добавим выход по нажатию Q для теста
    if (IsKeyPressed(KEY_Q))
    {
        _app.PopState();  // Говорим приложению "снять" нас со стека
    }
}

void HubState::Update(float deltaTime)
{
    // Пока пусто
}

void HubState::Draw()
{
    // Получаем шрифт из Application и используем его
    DrawTextEx(_app.GetFont(), "Привет из HubState!", {230, 200}, 32, 2, RAYWHITE);
    DrawTextEx(_app.GetFont(), "Нажми Q для выхода", {260, 240}, 20, 1, LIGHTGRAY);
}