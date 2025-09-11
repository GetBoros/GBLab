// src/States/HubState.hpp

#pragma once

#include <raylib.h>

#include <memory>
#include <vector>

#include "Components/Icon.hpp"
#include "States/State.hpp"

// Forward-декларации для уменьшения зависимостей в заголовках
class Application;
class StateManager;

/// @brief Перечисление для удобного доступа к иконкам в векторе по индексу.
enum class HubIcon
{
    Clicker = 0,
    Logger = 1,
    Exit = 2
};

/// @brief Главное меню (Хаб).
/// Представляет собой основной экран, с которого можно перейти в другие состояния (мини-приложения).
class HubState final : public State
{
public:
    /// @brief Конструктор. Создает и располагает все UI-элементы хаба.
    /// @param app Ссылка на приложение для доступа к общим ресурсам (шрифты).
    /// @param stateManager Ссылка на менеджер состояний для навигации.
    HubState(Application &app, StateManager &stateManager);

    /// @brief Деструктор.
    ~HubState() override;

    /// @brief Обрабатывает пользовательский ввод (клики по иконкам).
    void HandleInput() override;

    /// @brief Обновляет логику состояния (в будущем - анимации иконок).
    void Update(float deltaTime) override;

    /// @brief Отрисовывает все элементы хаба.
    void Draw() override;

private:
    Application &_app;            ///< Ссылка на приложение для доступа к глобальным ресурсам.
    StateManager &_stateManager;  ///< Ссылка на менеджер для переключения состояний.

    /// @brief Вектор умных указателей на иконки.
    /// Использование std::vector и std::unique_ptr автоматизирует управление памятью.
    std::vector<std::unique_ptr<Icon>> _icons;
};