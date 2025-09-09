// src/Components/Button.cpp

#include "Components/Button.hpp"

Button::Button(Rectangle bounds, std::string text, int textSize, Font& font)
    : _bounds(bounds),
      _text(std::move(text)),  // std::move эффективнее для строк
      _textSize(textSize),
      _font(font)
{
}

void Button::Update()
{
    // Сбрасываем флаг клика в начале каждого кадра
    _isClicked = false;

    // Проверяем наведение мыши
    _isHovered = CheckCollisionPointRec(GetMousePosition(), _bounds);

    // Если мышь наведена и была нажата ЛКМ, взводим флаг клика
    if (_isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        _isClicked = true;
    }
}

void Button::Draw()
{
    // Выбираем цвет фона в зависимости от того, наведена ли мышь
    Color currentColor = _isHovered ? _hoverColor : _baseColor;
    DrawRectangleRec(_bounds, currentColor);

    // Рассчитываем позицию текста, чтобы он был по центру кнопки
    const Vector2 textSize = MeasureTextEx(_font, _text.c_str(), _textSize, 1);
    const Vector2 textPos = {_bounds.x + (_bounds.width - textSize.x) / 2,
                             _bounds.y + (_bounds.height - textSize.y) / 2};

    // Рисуем текст
    DrawTextEx(_font, _text.c_str(), textPos, _textSize, 1, _textColor);
}