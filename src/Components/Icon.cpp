// src/Components/Icon.cpp

#include "Components/Icon.hpp"

#include "Core/Tools/Tools.hpp"

Icon::Icon(const std::string& texturePath, Vector2 position)
    : _position(position),
      // --- Инициализируем новые поля ---
      _baseTint({120, 120, 120, 255}),  // Темно-серый оттенок (иконка будет "в тени")
      _hoverTint(WHITE),
      _currentTint(_baseTint),
      _animationSpeed(6.0f),
      _isHovered(false),
      _isClicked(false)
{
    _texture = LoadTexture(texturePath.c_str());
    _bounds = {_position.x, _position.y, (float)_texture.width, (float)_texture.height};
}

Icon::~Icon()
{
    UnloadTexture(_texture);
}

// --- НОВЫЙ МЕТОД UPDATE ---
void Icon::Update()
{
    _isClicked = false;
    _isHovered = CheckCollisionPointRec(GetMousePosition(), _bounds);

    if (_isHovered && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        _isClicked = true;
    }

    Color targetTint = _isHovered ? _hoverTint : _baseTint;
    _currentTint = AsTools::ColorLerp(_currentTint, targetTint, _animationSpeed * GetFrameTime());
}

void Icon::Draw() const
{
    // Рисуем текстуру в заданной позиции без дополнительного окрашивания (WHITE)
    DrawTextureV(_texture, _position, WHITE);
}

// --- ОБНОВЛЕННЫЙ МЕТОД ISCLICKED ---
bool Icon::IsClicked() const
{
    // Теперь мы просто возвращаем флаг, который выставляется в Update()
    return _isClicked;
}