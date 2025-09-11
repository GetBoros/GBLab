// src/Components/Icon.hpp

#pragma once

#include <raylib.h>

#include <string>

/// @brief UI-компонент, представляющий кликабельную иконку.
/// Управляет собственным ресурсом - текстурой. Загружает ее при создании
/// и автоматически выгружает при уничтожении.
class Icon
{
public:
    /// @brief Конструктор. Загружает текстуру из файла и вычисляет границы.
    /// @param texturePath Путь к файлу с изображением.
    /// @param position Позиция верхнего левого угла иконки на экране.
    Icon(const std::string& texturePath, Vector2 position);

    /// @brief Деструктор. Выгружает текстуру из памяти GPU.
    ~Icon();

    // Запрещаем копирование, чтобы избежать двойного освобождения текстуры.
    Icon(const Icon&) = delete;
    Icon& operator=(const Icon&) = delete;

    /// @brief Отрисовывает иконку.
    /// Не изменяет состояние объекта, поэтому помечен как const.
    void Draw() const;  // Улучшение: Добавлен const

    /// @brief Проверяет, находится ли точка (курсор) в границах иконки.
    /// @param point Координаты точки для проверки.
    /// @return true, если точка внутри, иначе false.
    bool IsClicked(Vector2 point) const;  // Улучшение: Добавлен const

private:
    Texture2D _texture;  ///< Ресурс текстуры, управляемый этим объектом.
    Vector2 _position;   ///< Позиция на экране.
    Rectangle _bounds;   ///< Границы для проверки столкновений.
};