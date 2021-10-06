#include "TiroController.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

TiroController::TiroController(){
       // this->state = SDL_GetKeyboardState(nullptr);
}

void TiroController::calcular_posicao(Tiro &tiro){ 
    std::cout << "To aqui" << std::endl;
    if(tiro.getFlag()){
        std::cout << "To no TiroController e y atual = " <<  tiro.get_y_atual() << std::endl;
        std::cout << tiro.get_vy_atual() << std::endl;
        float novoy = tiro.get_y_atual() + tiro.get_vy_atual() * tiro.get_dt();
        tiro.set_y_atual(novoy);
        std::cout << "Novo y: " << tiro.get_y_atual()<< std::endl;
    }
}
void TiroController::update(Tiro &tiro){
    calcular_posicao(tiro);              
}