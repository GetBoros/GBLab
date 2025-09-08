#include "Core/Application.hpp"

int main()
{
    // Создаем экземпляр нашего приложения
    Application app(800, 450, "GBLab");

    // Запускаем главный цикл
    app.Run();

    return 0;
}
