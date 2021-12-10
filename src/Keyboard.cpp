#include <SDL2/SDL.h>
#include "Keyboard.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

using namespace std;

Keyboard::Keyboard(){
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
        cout << "Voce Pressionou Para Cima" << endl;
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

void Keyboard::atualizaEvento() {
    while(SDL_PollEvent(&(this->evento))){
        if(this->evento.type == SDL_QUIT) {
            this->saiu = 1;     
        }   
        else if(this->evento.type == SDL_KEYDOWN){
            if(state[SDL_SCANCODE_SPACE]){
                this->atirou = 1;
            }
        }
    }
}
int Keyboard::eventoDeSaida(){
    if(this->evento.type == SDL_QUIT) {
        this->saiu = 1;     
    } 

    else  {
        this->saiu = 0;
    }

    return this->saiu;
}

int Keyboard::eventoEspaco(){
    if(this->evento.type == SDL_KEYDOWN){
        if(state[SDL_SCANCODE_SPACE]){
            this->atirou = 1;
        }
        else{
            this->atirou = 0;
        }
    }

    else {
        this->atirou = 0;
    }

    return this->atirou;
}

int Keyboard::verTecla(int numTecla){
    return this->teclas[numTecla];
}

int Keyboard::verEspaco(){
    return this->atirou;
}

int Keyboard::verSaiu(){
    return this->saiu;
}