// src/States/LogViewState.hpp

#pragma once

#include <raylib.h>

#include <deque>  // Используем deque вместо vector
#include <memory>
#include <string>

#include "Components/Button.hpp"
#include "States/State.hpp"

class Application;
class StateManager;

class LogViewState final : public State
{
public:
    LogViewState(Application &app, StateManager &stateManager);
    ~LogViewState() override;

    void HandleInput() override;
    void Update(float deltaTime) override;
    void Draw() override;

private:
    void AddMessage();

    Application &_app;
    StateManager &_stateManager;

    // Кнопка для добавления сообщений
    std::unique_ptr<Button> _addButton;

    // Контейнер для хранения сообщений.
    // std::deque - "двусторонняя очередь". Она очень эффективна
    // для добавления элементов в начало и удаления с конца.
    std::deque<std::string> _messages;

    // Переменная для нумерации сообщений
    int _messageCounter = 0;
};