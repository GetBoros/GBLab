// src/Core/Tools/Tools.hpp

#pragma once
#include <raylib.h>  // Нам нужен доступ к структурам Raylib, таким как Color

/// @brief Статический класс-утилита.
/// Содержит набор полезных, переиспользуемых функций для всего проекта.
/// Объект этого класса создать нельзя.
class AsTools
{
public:
    /// @brief Линейно интерполирует цвет от начального к конечному.
    /// @param c1 Начальный цвет.
    /// @param c2 Конечный цвет.
    /// @param amount Коэффициент интерполяции (0.0 = c1, 1.0 = c2).
    /// @return Промежуточный цвет.
    static Color ColorLerp(Color c1, Color c2, float amount);

    // В будущем здесь могут появиться другие полезные функции:
    // static Vector2 GetTextCenter(const Font& font, const std::string& text, ...);

private:
    /// @brief Приватный конструктор, чтобы нельзя было создать экземпляр этого класса.
    AsTools() = default;
};