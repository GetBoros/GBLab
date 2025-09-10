// src/Core/StateManager.hpp

#pragma once

#include <memory>
#include <stack>

#include "States/State.hpp"

class Application;  // Опережающее объявление

class StateManager
{
public:
    StateManager(Application& app);

    void PushState(std::unique_ptr<State> state);
    void PopState();

    // Метод для "отложенного" изменения стека
    void ProcessStateChanges();

    void Update(float deltaTime);
    void Draw();

    bool IsEmpty() const
    {
        return _states.empty();
    }

private:
    Application& _app;
    std::stack<std::unique_ptr<State>> _states;

    // --- Новая логика для безопасного изменения стека ---
    std::unique_ptr<State> _newState;
    bool _isPopping = false;
    bool _isAdding = false;
};