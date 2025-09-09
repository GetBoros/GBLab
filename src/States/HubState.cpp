// src/States/HubState.cpp

#include "States/HubState.hpp"

#include <format>  // Для std::format

#include "Core/Application.hpp"

HubState::HubState(Application& app) : _app(app)
{
    // --- Создаем наши иконки и добавляем их в вектор ---

    // 1. Иконка Кликера
    const std::string clickerIconPath = std::format("{}/icons/icon_clicker.png", ASSETS_PATH);
    _icons.push_back(std::make_unique<Icon>(clickerIconPath, Vector2{100.0f, 150.0f}));

    // 2. Иконка Выхода
    const std::string exitIconPath = std::format("{}/icons/icon_exit.png", ASSETS_PATH);
    // Разместим ее правее первой
    _icons.push_back(std::make_unique<Icon>(exitIconPath, Vector2{300.0f, 150.0f}));

    TraceLog(LOG_INFO, "HubState Constructed");
}

HubState::~HubState()
{
    TraceLog(LOG_INFO, "HubState Destructed");
    // _clickerIcon будет автоматически уничтожен здесь, и его деструктор вызовется сам.
}

void HubState::HandleInput()
{
    int clickerIndex = static_cast<int>(HubIcon::Clicker);
    int exitIndex = static_cast<int>(HubIcon::Exit);

    if (IsKeyPressed(KEY_Q))
    {
        _app.PopState();
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        // Проверяем клик по каждой иконке

        // Клик по иконке Кликера (она у нас первая в векторе, индекс 0)
        if (_icons[clickerIndex]->IsClicked(GetMousePosition()))
        {
            TraceLog(LOG_INFO, "Clicker icon clicked! Pushing ClickerState.");
            _app.PushState(std::make_unique<ClickerState>(_app));  // Вот он, переход!
                                                                   // Здесь будет переход в состояние кликера
        }

        // Клик по иконке Выхода (вторая в векторе, индекс 1)
        if (_icons[exitIndex]->IsClicked(GetMousePosition()))
        {
            TraceLog(LOG_INFO, "Exit icon clicked! Popping HubState.");
            _app.PopState();  // Просто выходим из текущего состояния. Т.к. оно одно, приложение закроется.
        }
    }
}

void HubState::Update(float deltaTime)
{
    // Пока пусто
}

void HubState::Draw()
{
    // Рисуем текст-подсказку
    DrawTextEx(_app.GetFont(), "Добро пожаловать в GBLab!", {200, 50}, 32, 2, RAYWHITE);

    // Рисуем все иконки из вектора
    for (const auto& icon : _icons)
    {
        icon->Draw();
    }
}