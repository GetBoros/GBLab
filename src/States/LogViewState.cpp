// src/States/LogViewState.cpp

#include "States/LogViewState.hpp"

#include <format>

#include "Core/Application.hpp"
#include "Core/Config/Config.hpp"

LogViewState::LogViewState(Application& app) : _app(app)
{
    // Создаем кнопку "Добавить" в правом верхнем углу
    Rectangle buttonBounds = {AsConfig::WindowWidth - 150.0f, 20.0f, 130.0f, 40.0f};
    _addButton = std::make_unique<Button>(buttonBounds, "Добавить", AsConfig::DefaultFontSize, _app.GetFont());

    // Добавим пару сообщений для старта
    AddMessage();
    AddMessage();

    TraceLog(LOG_INFO, "LogViewState Constructed");
}

LogViewState::~LogViewState()
{
    TraceLog(LOG_INFO, "LogViewState Destructed");
}

// Приватный метод-помощник для добавления нового сообщения
void LogViewState::AddMessage()
{
    // Генерируем новое сообщение
    _messageCounter++;
    std::string newMessage = std::format("Это сообщение номер {}", _messageCounter);

    // Добавляем его в НАЧАЛО очереди
    _messages.push_front(newMessage);

    // Если сообщений стало больше 9, удаляем самое старое (с КОНЦА очереди)
    if (_messages.size() > 9)
    {
        _messages.pop_back();
    }
}

void LogViewState::HandleInput()
{
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        _app.PopState();
    }
}

void LogViewState::Update(float deltaTime)
{
    _addButton->Update();
    if (_addButton->IsClicked())
    {
        AddMessage();
    }
}

void LogViewState::Draw()
{
    // Рисуем кнопку
    _addButton->Draw();

    // Рисуем список сообщений
    float startY = 20.0f;      // Начальная Y-координата
    float lineHeight = 30.0f;  // Высота строки

    for (const auto& msg : _messages)
    {
        DrawTextEx(_app.GetFont(), msg.c_str(), {20.0f, startY}, 24, 1, RAYWHITE);
        startY += lineHeight;  // Сдвигаем Y для следующей строки
    }

    // Рисуем подсказку
    DrawTextEx(_app.GetFont(), "Нажми Backspace для возврата", {20, 400}, 20, 1, LIGHTGRAY);
}