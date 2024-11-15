cmake_minimum_required(VERSION 3.10)

# Название проекта
project(3d_engine)

# Установка стандарта языка C++
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Указание на оптимизацию
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# Найти пакет SDL2
set(SDL2_DIR "${CMAKE_SOURCE_DIR}/src/lib/SDL")

# Включить SDL директорию
add_subdirectory(${SDL2_DIR})

# Включить директории SDL2
include_directories(${SDL2_DIR}/include)

# Добавить исполняемый файл
add_executable(main src/bin/main.cpp)

# Линковка с библиотеками SDL2
target_link_libraries(main SDL2)
