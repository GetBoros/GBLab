// src/Components/Button.hpp

#pragma once

#include <raylib.h>

#include <string>

class Button
{
public:
    // Конструктор, принимающий все параметры для настройки кнопки
    Button(Rectangle bounds, std::string text, int textSize, const Font& font);  // Улучшение: const Font&

    // Запрещаем копирование, т.к. кнопка - уникальный UI элемент
    Button(const Button&) = delete;
    Button& operator=(const Button&) = delete;

    // Метод для обновления состояния кнопки
    void Update();

    // Метод для отрисовки кнопки
    void Draw() const;  // Улучшение: const

    // Геттер, чтобы узнать, была ли кнопка нажата в этом кадре
    bool IsClicked() const;

private:
    // Геометрия и текст
    Rectangle _bounds;
    std::string _text;
    int _textSize;
    const Font& _font;  // Храним КОНСТАНТНУЮ ссылку на шрифт

    // Цвета для разных состояний
    Color _baseColor;
    Color _hoverColor;
    Color _textColor;

    // --- Поля для анимации и состояния ---
    Color _currentColor;    // Текущий, анимируемый цвет фона
    float _animationSpeed;  // Скорость анимации
    bool _isHovered;        // Флаг наведения
    bool _isClicked;        // Флаг клика
};