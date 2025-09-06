#pragma once // Стандартная защита от двойного включения

#include "Utils.hpp"
namespace AsConfig {

// Объявляем (declare) наши константы. Они "видны" всем,
// кто подключит этот заголовок, но их "тело" будет в .cpp файле.
extern const std::string_view ProjectName;
extern const int ProjectVersionMajor;
extern const int ProjectVersionMinor;

} // namespace AsConfig