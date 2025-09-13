// src/Components/Button.cpp

#include "Components/Button.hpp"

#include <utility>  // для std::move

#include "Core/Tools/Tools.hpp"

Button::Button(Rectangle bounds, std::string text, int textSize, const Font& font)
    : _bounds(bounds),
      _text(std::move(text)),
      _textSize(textSize),
      _font(font),
      _baseColor(MAROON),
      _hoverColor(DARKGREEN),
      _textColor(WHITE),
      _currentColor(_baseColor),
      _animationSpeed(8.0f),
      _isHovered(false),
      _wasHovered(false),
      _isClicked(false)
{
}

void Button::Update()
{
    _isClicked = false;

    // 1. Узнаем текущее состояние наведения
    _isHovered = CheckCollisionPointRec(GetMousePosition(), _bounds);

    // 2. СРАВНИВАЕМ текущее состояние с состоянием из прошлого кадра
    if (_isHovered != _wasHovered)
    {
        // Если состояние изменилось, здесь мы можем поставить Logpoint!
        // Это сработает ТОЛЬКО ОДИН РАЗ в момент наведения или ухода курсора.
    }

    // Логика клика остается без изменений
    if (_isHovered && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        _isClicked = true;
    }

    Color targetColor = _isHovered ? _hoverColor : _baseColor;
    _currentColor = AsTools::ColorLerp(_currentColor, targetColor, _animationSpeed * GetFrameTime());

    // 3. В САМОМ КОНЦЕ, "запоминаем" текущее состояние для следующего кадра
    _wasHovered = _isHovered;
}

void Button::Draw() const
{
    DrawRectangleRec(_bounds, _currentColor);

    const Vector2 textSize = MeasureTextEx(_font, _text.c_str(), _textSize, 1);
    const Vector2 textPos = {_bounds.x + (_bounds.width - textSize.x) / 2,
                             _bounds.y + (_bounds.height - textSize.y) / 2};

    DrawTextEx(_font, _text.c_str(), textPos, _textSize, 1, _textColor);
}

bool Button::IsClicked() const
{
    return _isClicked;
}