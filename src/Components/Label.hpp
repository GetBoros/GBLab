// src/Components/Label.hpp

#pragma once

#include <raylib.h>

#include <string>

/// @brief Переиспользуемый UI-компонент для отображения текста.
/// Инкапсулирует в себе логику отрисовки текста, включая позицию, шрифт,
/// размер, цвет и межсимвольный интервал.
class Label
{
public:
    /// @brief Конструктор для создания текстовой метки.
    /// @param text Изначальный текст для отображения.
    /// @param position Позиция верхнего левого угла текста на экране.
    /// @param font Ссылка на загруженный шрифт (не копируется, а используется по ссылке).
    /// @param fontSize Размер шрифта.
    /// @param color Цвет текста.
    /// @param spacing Межсимвольный интервал (может быть отрицательным).
    Label(const std::string& text, Vector2 position, const Font& font, float fontSize, Color color,
          float spacing = 2.0f);

    /// @brief Отрисовывает текст на экране.
    /// Метод константный, так как отрисовка не изменяет состояние объекта.
    void Draw() const;

    /// @brief Обновляет отображаемый текст.
    /// @param text Новый текст для метки.
    void SetText(const std::string& text);

    /// @brief Устанавливает новую позицию для текста.
    /// @param position Новая позиция.
    void SetPosition(Vector2 position);

    /// @brief Изменяет цвет текста.
    /// @param color Новый цвет.
    void SetColor(Color color);

private:
    std::string _text;
    Vector2 _position;
    const Font& _font;  // Храним ссылку, а не копию. Label не владеет шрифтом.
    float _fontSize;
    float _spacing;
    Color _color;
};