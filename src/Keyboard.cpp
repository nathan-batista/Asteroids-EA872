#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#pragma once

using namespace std;

Keyboard::Keyboard(){
        this->evento = true;
        this->state = SDL_GetKeyboardState(nullptr);
}

void Keyboard::verificaTecla() {
    if(state[SDL_SCANCODE_LEFT]) {
        this->teclas[0] = 1;
    }
    else{
        this->teclas[0] = 0;
    }
    if(state[SDL_SCANCODE_RIGHT]) {
        this->teclas[1] = 1;
    }
    else{
        this->teclas[1] = 0;
    }
    if(state[SDL_SCANCODE_UP]) {
        this->teclas[2] = 1;
    }
    else{
        this->teclas[2] = 0;
    }
    if(state[SDL_SCANCODE_DOWN]) {
        this->teclas[3] = 1;
    }
    else{
        this->teclas[3] = 0;
    }
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

void Keyboard::eventoEspaco(){
    if(this->evento.type == SDL_KEYDOWN){
        if(state[SDL_SCANCODE_SPACE]){
            this->atirou = 1;
        }
        else{
            this->atirou = 0;
        }
    }
}

int Keyboard::verTecla(int numTecla){
    return this->teclas[numTecla];
}

int Keyboard::verEspaco(){
    return this->atirou;
}

