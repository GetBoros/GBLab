// src/Components/Label.cpp

#include "Components/Label.hpp"

// Используем список инициализации членов класса - это более эффективный
// и правильный способ в C++, чем присваивание в теле конструктора.
Label::Label(const std::string& text, Vector2 position, const Font& font, float fontSize, Color color, float spacing)
    : _text(text), _position(position), _font(font), _fontSize(fontSize), _spacing(spacing), _color(color)
{
    // Тело конструктора остается пустым, вся работа сделана в списке инициализации.
}

void Label::Draw() const
{
    DrawTextEx(_font, _text.c_str(), _position, _fontSize, _spacing, _color);
}

void Label::SetText(const std::string& text)
{
    _text = text;
}

void Label::SetPosition(Vector2 position)
{
    _position = position;
}

void Label::SetColor(Color color)
{
    _color = color;
}