// src/States/HubState.cpp

#include "States/HubState.hpp"

#include <format>  // Для std::format

#include "Core/Application.hpp"
#include "States/LogViewState.hpp"

HubState::HubState(Application& app) : _app(app)
{
    // 1. Иконка Кликера
    const std::string clickerIconPath = std::format("{}/icons/icon_clicker.png", ASSETS_PATH);
    _icons.push_back(std::make_unique<Icon>(clickerIconPath, Vector2{100.0f, 150.0f}));

    // 2. Иконка Логгера (НОВАЯ)
    const std::string loggerIconPath = std::format("{}/icons/icon_logger.png", ASSETS_PATH);
    _icons.push_back(std::make_unique<Icon>(loggerIconPath, Vector2{300.0f, 150.0f}));

    // 3. Иконка Выхода
    const std::string exitIconPath = std::format("{}/icons/icon_exit.png", ASSETS_PATH);
    _icons.push_back(std::make_unique<Icon>(exitIconPath, Vector2{500.0f, 150.0f}));  // Сдвинем ее правее

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
        int clickerIndex = static_cast<int>(HubIcon::Clicker);
        int loggerIndex = static_cast<int>(HubIcon::Logger);  // <--- Добавляем
        int exitIndex = static_cast<int>(HubIcon::Exit);

        if (_icons[clickerIndex]->IsClicked(GetMousePosition()))
        {
            _app.PushState(std::make_unique<ClickerState>(_app));
        }

        // --- НОВАЯ ЛОГИКА ---
        if (_icons[loggerIndex]->IsClicked(GetMousePosition()))
        {
            TraceLog(LOG_INFO, "Logger icon clicked! Pushing LogViewState.");
            _app.PushState(std::make_unique<LogViewState>(_app));
        }
        // ---------------------

        if (_icons[exitIndex]->IsClicked(GetMousePosition()))
        {
            _app.PopState();
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