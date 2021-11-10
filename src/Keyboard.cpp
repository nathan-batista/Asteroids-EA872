#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#pragma once

using namespace std;

Keyboard::Keyboard(){
        this->evento = true;
        this->state = SDL_GetKeyboardState(nullptr);
}

bool Keyboard::verificaTecla(string tecla) {

    SDL_PumpEvents(); 

    if(tecla.compare("LEFT")) {
        return state[SDL_SCANCODE_LEFT];
    }

    else if(tecla.compare("RIGHT")) {
        return state[SDL_SCANCODE_RIGHT];
    }

    else if(tecla.compare("UP")) {
        return state[SDL_SCANCODE_UP];
    }

    else if(tecla.compare("DOWN")) {
        return state[SDL_SCANCODE_DOWN];
    }

    return false;
}

bool Keyboard::verificaSaida() {

    while (SDL_PollEvent(&(this->evento))) {
        if (this->evento.type == SDL_QUIT) {
          return true;
        }
    }

    return false;

}


