#include "AsteroidController.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
using namespace std;

AsteroidController::AsteroidController(vector<Asteroid> &asteroid) : asteroid(asteroid){}

void AsteroidController::calcular_posicao(){  
    for(int i = 0; i < asteroid.size(); i++) {
        asteroid[i].set_x_atual(asteroid[i].get_x_atual() + asteroid[i].get_vx_atual() * asteroid[i].get_dt());
        asteroid[i].set_y_atual(asteroid[i].get_y_atual() + asteroid[i].get_vy_atual() * asteroid[i].get_dt());
    }
}

void AsteroidController::update(){
    calcular_posicao();              
}
