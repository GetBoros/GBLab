// src/Core/Application.hpp

#pragma once

#include <raylib.h>

#include <memory>  // Для std::unique_ptr
#include <stack>   // Для std::stack
#include <string>

#include "States/State.hpp"  // Подключаем наш базовый класс состояния

class Application
{
public:
    Application(int width, int height, const std::string& title);
    ~Application();

    void Run();

    // --- Новые публичные методы для управления состояниями ---
    void PushState(std::unique_ptr<State> state);
    void PopState();

    // Сделаем шрифт публичным, чтобы состояния могли его использовать
    Font GetFont() const
    {
        return _cyrillicFont;
    }

private:
    void LoadAssets();
    void UnloadAssets();

    int _screenWidth;
    int _screenHeight;
    Font _cyrillicFont;

    // --- Новые приватные поля для машины состояний ---

    // Стек состояний. std::stack - это как стопка тарелок.
    // Мы можем положить новую тарелку сверху (push) или снять верхнюю (pop).
    // Верхняя тарелка - это всегда активное состояние.
    std::stack<std::unique_ptr<State>> _states;
};