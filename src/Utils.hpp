#pragma once

#include <format>
#include <iostream>
#include <string>
#include <string_view>

// Пространство имен для утилит
namespace Utils
{

// Простая функция, которая форматирует и возвращает строку
// inline - подсказка компилятору, что функцию можно "встроить"
// в место вызова для оптимизации. Идеально для маленьких функций.
inline std::string GetWelcomeMessage()
{
    return std::format("Welcome to our project!");
}

} // namespace Utils
