// src/Core/Config/Config.hpp

#pragma once

class AsConfig
{
public:
    // Запрещаем создавать экземпляры этого класса.
    // Он должен использоваться только статически.
    AsConfig() = delete;

    // --- Окно приложения ---
    static inline constexpr int WindowWidth = 800;
    static inline constexpr int WindowHeight = 450;
    static inline constexpr const char *WindowTitle = "GBLab";

    // --- Шрифты ---
    static inline constexpr int DefaultFontSize = 20;
};