#pragma once

#include <raylib.h>

#include <memory>
#include <string>

#include "Core/StateManager.hpp"  // <--- Меняем State.hpp на StateManager.hpp

class Application
{
public:
    Application(int width, int height, const std::string& title);
    ~Application();

    void Run();

    Font& GetFont()
    {
        return _cyrillicFont;
    }
    StateManager& GetStateManager()
    {
        return *_stateManager;
    }  // <--- Геттер для менеджера

private:
    void LoadAssets();
    void UnloadAssets();

    int _screenWidth;
    int _screenHeight;
    Font _cyrillicFont;

    // Заменяем стек на один указатель на StateManager
    std::unique_ptr<StateManager> _stateManager;
};