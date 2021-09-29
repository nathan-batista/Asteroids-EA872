#include "AsteroidController.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

AsteroidController::AsteroidController(Asteroid &asteroid) : asteroid(asteroid){

       // this->state = SDL_GetKeyboardState(nullptr);
}



void AsteroidController::calcular_posicao(){  
    asteroid.set_x_atual(asteroid.get_x_atual() + asteroid.get_vx_atual() * asteroid.get_dt());
    asteroid.set_y_atual(asteroid.get_y_atual() + asteroid.get_vy_atual() * asteroid.get_dt());
}
void AsteroidController::update(){
    calcular_posicao();              
}