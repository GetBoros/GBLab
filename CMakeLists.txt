#-------------------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.28)
project(HelloWorld VERSION 1.0) # Имя проекта, используется для IDE

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_FETCHCONTENT_SOURCE_DIR_FETCHCONTENT ${CMAKE_BINARY_DIR}/fetchcontent)
#-------------------------------------------------------------------------------------------------------------

# --- Проверки зависимостей ---
find_package(X11 REQUIRED)
#-------------------------------------------------------------------------------------------------------------

# --- Подключение внешних библиотек ---
include(FetchContent)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 5.0
)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
  GIT_SHALLOW    TRUE
)

FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG        v3.11.3
)

FetchContent_MakeAvailable(raylib googletest json)
#-------------------------------------------------------------------------------------------------------------

# === ШАГ 1: Создаем статическую библиотеку GBLabCore, содержащую всё наше "ядро" ===

file(GLOB_RECURSE CORE_SOURCES 
    "src/Components/*.cpp"
    "src/Core/*.cpp"
    "src/Core/Config/*.cpp"
    "src/Core/Tools/*.cpp"
    "src/States/*.cpp"
)

add_library(GBLabCore STATIC ${CORE_SOURCES})

target_include_directories(GBLabCore PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(GBLabCore PUBLIC raylib nlohmann_json::nlohmann_json)

# ИСПРАВЛЕНИЕ: Макрос теперь привязан к GBLabCore, так как код, его использующий, живет здесь.
target_compile_definitions(GBLabCore PUBLIC "ASSETS_PATH=\"${CMAKE_SOURCE_DIR}/assets\"")

#-------------------------------------------------------------------------------------------------------------

# === ШАГ 2: Создаем основное приложение HelloWorld ===

add_executable(HelloWorld src/main.cpp)
target_link_libraries(HelloWorld PRIVATE GBLabCore)
# Старая строка с target_compile_definitions отсюда УДАЛЕНА, так как она "переехала" выше.

#-------------------------------------------------------------------------------------------------------------

# === ШАГ 3: Создаем тестовое приложение runTests ===
enable_testing()
add_executable(runTests tests/main_test.cpp)
target_link_libraries(runTests PRIVATE gtest_main GBLabCore)

include(GoogleTest)
gtest_discover_tests(runTests)
#-------------------------------------------------------------------------------------------------------------