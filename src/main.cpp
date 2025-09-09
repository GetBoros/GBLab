#include "Core/Application.hpp"
#include "Core/Config/Config.hpp"

int main()
{
    // Создаем экземпляр нашего приложения
    Application app(AsConfig::WindowWidth, AsConfig::WindowHeight, AsConfig::WindowTitle);

    // Запускаем главный цикл
    app.Run();

    return 0;
}
