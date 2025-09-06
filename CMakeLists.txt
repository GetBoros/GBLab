#-------------------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.28)
#-------------------------------------------------------------------------------------------------------------
project(HelloWorld VERSION 1.0)  # Project name and version

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_FETCHCONTENT_SOURCE_DIR_FETCHCONTENT ${CMAKE_BINARY_DIR}/fetchcontent)  # put to build/fetchcontent
#-------------------------------------------------------------------------------------------------------------
find_package(X11)# check if OS has libs and ask user to install

if(NOT X11_FOUND)  # if not found message to output
    message(FATAL_ERROR "X11 development libraries not found! \n"
                        "Please install them using your system's package manager. \n"
                        "For Debian/Ubuntu, run: sudo apt install xorg-dev")
endif()
#-------------------------------------------------------------------------------------------------------------
include(FetchContent)  # include modules

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 5.0  # Use last stable version
)
FetchContent_MakeAvailable(raylib)  # 

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0 # Указываем конкретную стабильную версию
  GIT_SHALLOW    TRUE    # Скачиваем только последнюю версию, без всей истории коммитов
)
FetchContent_MakeAvailable(googletest)
#-------------------------------------------------------------------------------------------------------------
add_executable(HelloWorld 
    src/main.cpp  # main.cpp to main.o
    src/Config.cpp)

target_link_libraries(HelloWorld PRIVATE raylib)
#-------------------------------------------------------------------------------------------------------------
enable_testing()  # add new feature
add_executable(runTests
    tests/main_test.cpp
    )
target_include_directories(runTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)  # where look files
target_link_libraries(runTests PRIVATE gtest_main)  # 

include(GoogleTest)  # include module

gtest_discover_tests(runTests)  # find all TEST, TEST_F in our code and add to test system CTest
#-------------------------------------------------------------------------------------------------------------

# HELP

# ${CMAKE_BINARY_DIR} ../Hello_World/build