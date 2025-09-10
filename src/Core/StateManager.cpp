// src/Core/StateManager.cpp

#include "Core/StateManager.hpp"

StateManager::StateManager(Application& app) : _app(app), _isPopping(false), _isAdding(false)
{
}

void StateManager::PushState(std::unique_ptr<State> state)
{
    _isAdding = true;
    _newState = std::move(state);  // Перемещаем владение во временное хранилище
}

void StateManager::PopState()
{
    _isPopping = true;
}

void StateManager::ProcessStateChanges()
{
    // Сначала проверяем, нужно ли снять состояние
    if (_isPopping && !_states.empty())
    {
        _states.pop();
        _isPopping = false;
    }

    // Затем проверяем, нужно ли добавить новое
    if (_isAdding)
    {
        _states.push(std::move(_newState));
        _isAdding = false;
    }
}

void StateManager::Update(float deltaTime)
{
    if (!_states.empty())
    {
        _states.top()->HandleInput();
        _states.top()->Update(deltaTime);
    }
}

void StateManager::Draw()
{
    if (!_states.empty())
    {
        _states.top()->Draw();
    }
}