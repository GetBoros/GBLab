// src/States/HubState.cpp

#include "States/HubState.hpp"

#include <format>  // Для std::format

#include "Core/Application.hpp"

HubState::HubState(Application& app) : _app(app)
{
    // --- Создаем нашу иконку ---
    // Формируем полный путь к файлу иконки
    const std::string iconPath = std::format("{}/icons/icon_clicker.png", ASSETS_PATH);

    // Создаем объект Icon и передаем владение в наш unique_ptr
    _clickerIcon = std::make_unique<Icon>(iconPath, Vector2{100.0f, 100.0f});

    TraceLog(LOG_INFO, "HubState Constructed");
}

HubState::~HubState()
{
    TraceLog(LOG_INFO, "HubState Destructed");
    // _clickerIcon будет автоматически уничтожен здесь, и его деструктор вызовется сам.
}

void HubState::HandleInput()
{
    if (IsKeyPressed(KEY_Q))
    {
        _app.PopState();
    }

    // --- Проверяем клик по иконке ---
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (_clickerIcon->IsClicked(GetMousePosition()))
        {
            // Если кликнули, выводим сообщение в лог
            TraceLog(LOG_INFO, "Clicker icon has been clicked!");
            // В будущем здесь будет переход в другое состояние:
            // _app.PushState(std::make_unique<ClickerState>(_app));
        }
    }
}

void HubState::Update(float deltaTime)
{
    // Пока пусто
}

void HubState::Draw()
{
    // Рисуем текст
    DrawTextEx(_app.GetFont(), "Кликни по иконке!", {230, 200}, 32, 2, RAYWHITE);
    DrawTextEx(_app.GetFont(), "Нажми Q для выхода", {260, 240}, 20, 1, LIGHTGRAY);

    // --- Рисуем нашу иконку ---
    _clickerIcon->Draw();
}