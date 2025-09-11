// src/Core/Tools/Tools.cpp

#include "Core/Tools/Tools.hpp"

#include <algorithm>  // Для std::clamp

Color AsTools::ColorLerp(Color c1, Color c2, float amount)
{
    // Используем std::clamp, чтобы amount всегда был в диапазоне [0.0, 1.0].
    // Это более современный и лаконичный способ, чем два if.
    amount = std::clamp(amount, 0.0f, 1.0f);

    return Color{static_cast<unsigned char>(c1.r + (c2.r - c1.r) * amount),
                 static_cast<unsigned char>(c1.g + (c2.g - c1.g) * amount),
                 static_cast<unsigned char>(c1.b + (c2.b - c1.b) * amount),
                 static_cast<unsigned char>(c1.a + (c2.a - c1.a) * amount)};
}