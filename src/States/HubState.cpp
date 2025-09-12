// src/States/HubState.cpp

#include "States/HubState.hpp"

#include <format>  // Для std::format

#include "Core/Application.hpp"
#include "Core/StateManager.hpp"
#include "States/ClickerState.hpp"
#include "States/LogViewState.hpp"

HubState::HubState(Application& app, StateManager& stateManager) : _app(app), _stateManager(stateManager)
{
    const std::string clickerIconPath = std::format("{}/icons/icon_clicker.png", ASSETS_PATH);
    _icons.push_back(std::make_unique<Icon>(clickerIconPath, Vector2{100.0f, 150.0f}));

    const std::string loggerIconPath = std::format("{}/icons/icon_logger.png", ASSETS_PATH);
    _icons.push_back(std::make_unique<Icon>(loggerIconPath, Vector2{300.0f, 150.0f}));

    const std::string exitIconPath = std::format("{}/icons/icon_exit.png", ASSETS_PATH);
    _icons.push_back(std::make_unique<Icon>(exitIconPath, Vector2{500.0f, 150.0f}));

    TraceLog(LOG_INFO, "HubState Constructed");
}

HubState::~HubState()
{
    TraceLog(LOG_INFO, "HubState Destructed");
}

void HubState::HandleInput()
{
    if (IsKeyPressed(KEY_Q))
    {
        _stateManager.PopState();  // Например, для быстрого выхода
    }
}

void HubState::Update(float deltaTime)
{
    // 1. Сначала обновляем все иконки. Внутри этого метода выставится флаг _isClicked, если нужно.
    for (const auto& icon : _icons)
    {
        icon->Update();
    }

    // 2. ТЕПЕРЬ, когда флаги в актуальном состоянии, проверяем их.
    int clickerIndex = static_cast<int>(HubIcon::Clicker);
    if (_icons[clickerIndex]->IsClicked())
    {
        _stateManager.PushState(std::make_unique<ClickerState>(_app, _stateManager));
    }

    int loggerIndex = static_cast<int>(HubIcon::Logger);
    if (_icons[loggerIndex]->IsClicked())
    {
        _stateManager.PushState(std::make_unique<LogViewState>(_app, _stateManager));
    }

    int exitIndex = static_cast<int>(HubIcon::Exit);
    if (_icons[exitIndex]->IsClicked())
    {
        _stateManager.PopState();
    }
}

void HubState::Draw()
{
    DrawTextEx(_app.GetFont(), "Добро пожаловать в GBLab!", {200, 50}, 32, 2, RAYWHITE);
    for (const auto& icon : _icons)
    {
        icon->Draw();
    }
}