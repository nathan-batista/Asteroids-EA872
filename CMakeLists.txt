# Versao minima do cmake
cmake_minimum_required(VERSION 3.0)

# Nome do meu projeto
project(Asteroids)

#
add_executable(Asteroids src/main.cpp)

# Especificar onde estao os header files
include_directories(include)

# Bibliotecas locais (estaticas)
add_library(Model src/Model.cpp)
target_link_libraries(Asteroids Model)
add_library(View src/View.cpp)
target_link_libraries(Asteroids View)
add_library(Controller src/Controller.cpp)
target_link_libraries(Asteroids Controller)

# Garantir que usaremos C++11 (ou superior, se preciso)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Bibliotecas linkadas externamente
target_link_libraries(Asteroids SDL2)
target_link_libraries(Asteroids SDL2_image)