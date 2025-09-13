#include <gtest/gtest.h>  // GoogleTest library

#include "Core/Tools/Tools.hpp"  // target_link_libraries(runTests PRIVATE gtest_main AsTools)

// Test Suite: AsToolsTests, Test Case: ColorLerpWorks
TEST(AsToolsTests, ColorLerpWorks)
{
    // Arrange: Готовим исходные данные
    const Color black = {0, 0, 0, 255};
    const Color white = {255, 255, 255, 255};
    Color result;  // Сюда будем сохранять результат

    // Act & Assert: Действуем и проверяем

    // 1. Проверка крайних значений
    result = AsTools::ColorLerp(black, white, 0.0f);
    EXPECT_EQ(result.r, black.r);
    EXPECT_EQ(result.g, black.g);
    EXPECT_EQ(result.b, black.b);

    result = AsTools::ColorLerp(black, white, 1.0f);
    EXPECT_EQ(result.r, white.r);
    EXPECT_EQ(result.g, white.g);
    EXPECT_EQ(result.b, white.b);

    // 2. Проверка середины (50% серый)
    result = AsTools::ColorLerp(black, white, 0.5f);
    EXPECT_EQ(result.r, 127);  // (0 + (255-0) * 0.5) = 127.5, кастуется к 127
    EXPECT_EQ(result.g, 127);
    EXPECT_EQ(result.b, 127);

    // 3. Проверка альфа-канала
    const Color transparent_black = {0, 0, 0, 0};
    const Color opaque_black = {0, 0, 0, 255};
    result = AsTools::ColorLerp(transparent_black, opaque_black, 0.25f);
    EXPECT_EQ(result.a, 63);  // (0 + (255-0) * 0.25) = 63.75, кастуется к 63
}
