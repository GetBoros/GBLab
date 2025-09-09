// src/Components/Button.hpp

#pragma once

#include <raylib.h>

#include <functional>  // Для std::function
#include <string>

class Button
{
public:
    // Конструктор, принимающий все параметры для настройки кнопки
    Button(Rectangle bounds, std::string text, int textSize, Font& font);

    // Запрещаем копирование, т.к. кнопка - уникальный UI элемент
    Button(const Button&) = delete;
    Button& operator=(const Button&) = delete;

    // Метод для обновления состояния кнопки (проверка наведения, клика)
    // Должен вызываться каждый кадр в методе Update состояния.
    void Update();

    // Метод для отрисовки кнопки
    // Должен вызываться каждый кадр в методе Draw состояния.
    void Draw();

    // Геттер, чтобы узнать, была ли кнопка нажата в этом кадре
    bool IsClicked() const
    {
        return _isClicked;
    }

private:
    // Геометрия и текст
    Rectangle _bounds;
    std::string _text;
    int _textSize;
    Font& _font;  // Храним ссылку на шрифт, не владеем им

    // Цвета для разных состояний
    Color _baseColor = MAROON;
    Color _hoverColor = RED;
    Color _textColor = WHITE;

    // Внутренние флаги состояния
    bool _isHovered = false;
    bool _isClicked = false;
};