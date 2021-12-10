# Versao minima do cmake
cmake_minimum_required(VERSION 3.0)

# Nome do meu projeto
project(Asteroids)

#
add_executable(Asteroids src/cliente.cpp)
add_executable(Servidor src/Servidor.cpp)

# Especificar onde estao os header files
include_directories(include)

# Bibliotecas locais (estaticas)
add_library(Nave src/Nave.cpp)
target_link_libraries(Asteroids Nave)
target_link_libraries(Servidor Nave)

add_library(View src/View.cpp)
target_link_libraries(Asteroids View)
target_link_libraries(Servidor View)

add_library(NaveController src/NaveController.cpp)
target_link_libraries(Asteroids NaveController)

add_library(Asteroid src/Asteroid.cpp)
target_link_libraries(Asteroids Asteroid)
target_link_libraries(Servidor Asteroid)

add_library(AsteroidController src/AsteroidController.cpp)
target_link_libraries(Asteroids AsteroidController)
target_link_libraries(Servidor AsteroidController)

add_library(Tiro src/Tiro.cpp)
target_link_libraries(Asteroids Tiro)
target_link_libraries(Servidor Tiro)

add_library(TiroController src/TiroController.cpp)
target_link_libraries(Asteroids TiroController)
target_link_libraries(Servidor TiroController)

add_library(Keyboard src/Keyboard.cpp)
target_link_libraries(Asteroids Keyboard)
target_link_libraries(Servidor Keyboard)

add_library(ModelFinal src/ModelFinal.cpp)
target_link_libraries(Asteroids ModelFinal)
target_link_libraries(Servidor ModelFinal)

add_library(ControllerGeral src/ControllerGeral.cpp)
target_link_libraries(Asteroids ControllerGeral)
target_link_libraries(Servidor ControllerGeral)

# Garantir que usaremos C++11 (ou superior, se preciso)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-g")

# Bibliotecas linkadas externamente
target_link_libraries(Asteroids SDL2)
target_link_libraries(Asteroids SDL2_image)
target_link_libraries(Asteroids SDL2_ttf)
target_link_libraries(Asteroids pthread)
target_link_libraries(Servidor SDL2)
target_link_libraries(Servidor SDL2_image)
target_link_libraries(Servidor SDL2_ttf)
target_link_libraries(Servidor pthread)
