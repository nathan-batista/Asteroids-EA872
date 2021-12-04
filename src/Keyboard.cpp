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
    else if(tecla.compare("SPACE")){
        return state[SDL_SCANCODE_SPACE];
    }
    return false;
}

void Keyboard::atualizarEstadoTeclado(){
        SDL_PumpEvents(); 
}

bool Keyboard::atualizaEvento() {
    SDL_PollEvent(&(this->evento));
}
bool Keyboard::eventoDeSaida(){
    if(this->evento.type == SDL_QUIT) return true;
    else return false;
}

bool Keyboard::eventoEspaco(){
    if(this->evento.type == SDL_KEYDOWN){
        if(state[SDL_SCANCODE_SPACE]){
            return true;
        }
    }
    return false;
}


