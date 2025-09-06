#include "Config.hpp"
// Подключаем заголовочные файлы библиотеки, которую мы только что "нашли"
#include <raylib.h> // Один заголовочный файл для всего!

int main() {
    // Настройки окна
    const int screenWidth = 800;
    const int screenHeight = 600;

    // Инициализация окна. Заголовок берем из нашего конфига!
    InitWindow(screenWidth, screenHeight, AsConfig::ProjectName.data());

    // Устанавливаем целевой FPS
    SetTargetFPS(60);

    // Главный цикл программы (работает, пока не нажмут ESC или крестик)
    while (!WindowShouldClose()) {
        // --- ОБНОВЛЕНИЕ ЛОГИКИ (у нас ее нет) ---

        // --- ОТРИСОВКА ---
        BeginDrawing();

            // Очищаем фон светло-серым цветом
            ClearBackground(RAYWHITE);

            // Рисуем текст
            DrawText("Congrats! You created your first window with Raylib!", 130, 200, 20, LIGHTGRAY);
            
            // Рисуем красный круг
            DrawCircle(screenWidth / 2, screenHeight / 2, 50, MAROON);

        EndDrawing();
    }

    // Закрываем окно и освобождаем ресурсы
    CloseWindow();

    return 0;
}