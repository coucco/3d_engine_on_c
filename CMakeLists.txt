cmake_minimum_required(VERSION 3.10)

# Название проекта
project(3d_engine)

# Установка стандарта языка C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Указание на оптимизацию
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# Включить SDL директорию
add_subdirectory(src/lib/SDL)

# Включить директории SDL2
include_directories(src/lib/SDL/include src/bin/include)

# Добавить исполняемый файл
add_executable(main src/bin/math.cpp src/bin/model.cpp src/bin/main.cpp)

# Линковка с библиотеками SDL2
target_link_libraries(main SDL2)
