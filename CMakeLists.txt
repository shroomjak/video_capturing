cmake_minimum_required(VERSION 3.10)
project(video_capturing)

set(CMAKE_CXX_STANDARD 20)

# Поиск OpenCV
find_package(OpenCV REQUIRED)

# 1. Указываем правильный путь к файлу main.cpp внутри папки src
add_executable(main src/main.cpp)

# 2. Указываем CMake, где искать заголовочные файлы проекта (директорию src)
target_include_directories(main PRIVATE src)

# 3. Линковка библиотек OpenCV
target_link_libraries(main PRIVATE ${OpenCV_LIBS})