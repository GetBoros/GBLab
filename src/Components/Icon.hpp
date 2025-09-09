// src/Components/Icon.hpp

#pragma once

#include <raylib.h>

#include <string>

class Icon
{
public:
    // Конструктор: загружает текстуру из файла и устанавливает позицию
    Icon(const std::string& texturePath, Vector2 position);
    ~Icon();

    // Запрещаем копирование, т.к. текстуру нельзя просто так скопировать.
    // Это хорошая практика для классов, управляющих ресурсами.
    Icon(const Icon&) = delete;
    Icon& operator=(const Icon&) = delete;

    // Метод для отрисовки иконки
    void Draw();

    // Метод для проверки, находится ли точка (например, курсор мыши) внутри иконки
    bool IsClicked(Vector2 mousePosition);

private:
    Texture2D _texture;  // Текстура из raylib
    Vector2 _position;   // Позиция верхнего левого угла иконки
    Rectangle _bounds;   // Прямоугольник, описывающий границы иконки
};