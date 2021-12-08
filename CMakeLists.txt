# Versao minima do cmake
cmake_minimum_required(VERSION 3.0)

# Nome do meu projeto
project(Asteroids)

#
add_executable(Asteroids src/Servidor.cpp)

# Especificar onde estao os header files
include_directories(include)

# Bibliotecas locais (estaticas)
add_library(Nave src/Nave.cpp)
target_link_libraries(Asteroids Nave)
add_library(View src/View.cpp)
target_link_libraries(Asteroids View)
add_library(NaveController src/NaveController.cpp)
target_link_libraries(Asteroids NaveController)
add_library(Asteroid src/Asteroid.cpp)
target_link_libraries(Asteroids Asteroid)
add_library(AsteroidController src/AsteroidController.cpp)
target_link_libraries(Asteroids AsteroidController)
add_library(Tiro src/Tiro.cpp)
target_link_libraries(Asteroids Tiro)
add_library(TiroController src/TiroController.cpp)
target_link_libraries(Asteroids TiroController)
add_library(Keyboard src/Keyboard.cpp)
target_link_libraries(Asteroids Keyboard)
add_library(ModelFinal src/ModelFinal.cpp)
target_link_libraries(Asteroids ModelFinal)
add_library(ControllerGeral src/ControllerGeral.cpp)
target_link_libraries(Asteroids ControllerGeral)

# Garantir que usaremos C++11 (ou superior, se preciso)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-g")

# Bibliotecas linkadas externamente
target_link_libraries(Asteroids SDL2)
target_link_libraries(Asteroids SDL2_image)
target_link_libraries(Asteroids SDL2_ttf)
target_link_libraries(Asteroids pthread)
