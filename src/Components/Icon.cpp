// src/Components/Icon.cpp

#include "Components/Icon.hpp"

Icon::Icon(const std::string& texturePath, Vector2 position)
    : _texture(LoadTexture(texturePath.c_str())), _position(position)
{
    // Инициализируем границы иконки на основе ее размера и позиции
    _bounds.x = _position.x;
    _bounds.y = _position.y;
    _bounds.width = static_cast<float>(_texture.width);
    _bounds.height = static_cast<float>(_texture.height);
}

Icon::~Icon()
{
    // Очень важно освобождать текстуру, когда иконка больше не нужна
    UnloadTexture(_texture);
}

void Icon::Draw()
{
    // Рисуем текстуру в заданной позиции без дополнительного окрашивания (WHITE)
    DrawTextureV(_texture, _position, WHITE);
}

bool Icon::IsClicked(Vector2 mousePosition)
{
    // Raylib предоставляет удобную функцию для проверки столкновения точки и прямоугольника
    return CheckCollisionPointRec(mousePosition, _bounds);
}