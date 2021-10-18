#include "TiroController.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
using namespace std;

TiroController::TiroController(){}

void TiroController::calcular_posicao(Tiro &tiro){ 
    float novoy = tiro.get_y_atual() + tiro.get_vy_atual() * tiro.get_dt();
    tiro.set_y_atual(novoy);  
}

void TiroController::update(vector<Tiro> &tiro){
    for(int i = 0; i < tiro.size(); i++) {
        calcular_posicao(tiro[i]);   
    }              
}