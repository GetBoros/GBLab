#include <raylib.h>

#include "Config.hpp"

Font Init_Load_Font_Ex()
{
    const char *fontPath = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
    int codepoints[256];
    int count = 0;

    codepoints[count++] = 32;  // Пробел

    for (int i = 48; i <= 57; ++i) codepoints[count++] = i;      // Цифры 0-9
    for (int i = 65; i <= 90; ++i) codepoints[count++] = i;      // A-Z
    for (int i = 97; i <= 122; ++i) codepoints[count++] = i;     // a-z
    for (int i = 1040; i <= 1103; ++i) codepoints[count++] = i;  // А-я

    codepoints[count++] = 1025;  // Ё
    codepoints[count++] = 1105;  // ё
    codepoints[count++] = 33;    // !
    codepoints[count++] = 46;    // .

    return LoadFontEx(fontPath, 96, codepoints, count);
}

int main()
{
    bool isDragging = false;
    int *ptr = 0;
    const int screenWidth = 800;
    const int screenHeight = 450;
    Vector2 dragOffset = {0.0f, 0.0f};

    SetConfigFlags(FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_UNDECORATED);
    InitWindow(screenWidth, screenHeight, "GBLab - Плавное прозрачное окно!");
    SetWindowPosition(0, 0);

    if (ptr != 0)
    {
        /* code */
    }

    SetTargetFPS(60);

    Font cyrillicFont = Init_Load_Font_Ex();

    while (!WindowShouldClose())
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            isDragging = true;

            dragOffset.x = GetMousePosition().x;
            dragOffset.y = GetMousePosition().y;
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) isDragging = false;

        if (isDragging)
        {
            Vector2 currentMousePos = GetMousePosition();
            Vector2 windowPos = GetWindowPosition();

            SetWindowPosition(windowPos.x + currentMousePos.x - dragOffset.x,
                              windowPos.y + currentMousePos.y - dragOffset.y);
        }

        BeginDrawing();

        ClearBackground(BLANK);

        DrawTextEx(cyrillicFont, "Теперь точно работает как надо!", {190, 200}, 20, 1, LIME);
        DrawTextEx(cyrillicFont, "Никакого дрожания и убегания.", {240, 230}, 16, 1, GRAY);

        EndDrawing();
    }

    UnloadFont(cyrillicFont);
    CloseWindow();

    return 0;
}