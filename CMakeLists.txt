# Minimalna wymagana wersja CMake
cmake_minimum_required(VERSION 3.10)

# Nazwa projektu i język (CXX to C++)
project(AsciiArtGenerator VERSION 1.0.0 LANGUAGES CXX)

# Wymuszamy standard C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Wskazujemy, że chcemy stworzyć plik wykonywalny (.exe / ELF)
# Pierwszy argument to nazwa gotowego programu, kolejne to pliki źródłowe
add_executable(ascii_generator src/main.cpp)

# Mówimy kompilatorowi, żeby szukał plików nagłówkowych (.h) w folderze 'src'.
# Dzięki temu w main.cpp zawsze zadziała #include "stb_image.h"
target_include_directories(ascii_generator PRIVATE src)