#include "NaveController.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Tiro.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

NaveController::NaveController(Nave &nave,vector<Asteroid> &asteroid) : nave(nave), asteroid(asteroid){
        this->rodando = true;
        this->state = SDL_GetKeyboardState(nullptr);
}

void NaveController::polling(){
      SDL_PumpEvents(); // atualiza estado do teclado
      if (state[SDL_SCANCODE_LEFT]) nave.set_x_atual(nave.get_x_atual()-10);
      if (state[SDL_SCANCODE_RIGHT]) nave.set_x_atual(nave.get_x_atual() + 10);
      if (state[SDL_SCANCODE_UP]) nave.set_y_atual(nave.get_y_atual() - 10);
      if (state[SDL_SCANCODE_DOWN]) nave.set_y_atual(nave.get_y_atual() + 10);

      while (SDL_PollEvent(&(this->evento))) {
        if (this->evento.type == SDL_QUIT) {
          this->rodando = false;
        }

        else if(this->evento.type == SDL_KEYDOWN){
            if(state[SDL_SCANCODE_SPACE]){
                float x = nave.get_x_atual();
                float y = nave.get_y_atual();
                float vy = -100;
                float dt = nave.get_dt();

                Tiro tiroNave = Tiro(x, y, 0, vy, dt);
                nave.atirar(tiroNave);            
            }
        }
    }

    if(asteroid.size() < 20) {
        int x_rand = rand() % 1000 + 1;
        int y_rand = -120;
        int vx_rand = rand() % 20 + (-10);
        int vy_rand = rand() % 10 + 1;

        Asteroid asteroids = Asteroid(x_rand, y_rand, vx_rand, vy_rand, 0.1);
        asteroid.push_back(asteroids);
    }
  
} 

bool NaveController::get_rodando(){
      return this->rodando;
}

void NaveController::calcular_velocidade(){
    nave.set_v_atual(nave.get_v_atual() + a * nave.get_dt());
}

void NaveController::calcular_posicao(){
    nave.set_x_atual(nave.get_x_atual() + nave.get_v_atual() * nave.get_dt());
}

void NaveController::update(){
    vector<int> ast1, tir1;
    vector<Tiro> &tiro = nave.getTiro();
    int i = 0;

    for(i = 0; i < asteroid.size(); i++) {
        if (nave.get_x_atual() < asteroid[i].get_x_atual() + asteroid[i].width &&
        nave.get_x_atual() + nave.width > asteroid[i].get_x_atual() &&
        nave.get_y_atual() < asteroid[i].get_y_atual() + asteroid[i].height &&
        nave.get_y_atual() + nave.height > asteroid[i].get_y_atual()) {
       
            //this->rodando = false;
            nave.gameover();
        }

        if((asteroid[i].get_x_atual() > 1200 || asteroid[i].get_x_atual() < -200) || (asteroid[i].get_y_atual() < -800)) {
            ast1.push_back(i);   
        }
    }
    if(!ast1.empty()){
        for(i = ast1.size()-1; i>-1;i--){
            asteroid.erase(asteroid.begin() + ast1[i]);
            ast1.pop_back();
        }
    }
    
    for(i = 0; i < tiro.size(); i ++) {
        if(tiro[i].get_y_atual() < -200) {
            tir1.push_back(i);
        }
    }

    if(!tir1.empty()){
        for(i = tir1.size()-1; i>-1;i--){
            tiro.erase(tiro.begin() + tir1[i]);
            tir1.pop_back();
        }
    }


    int j = 0;
    for(i = 0; i < tiro.size(); i++) {
        for(j = 0; j < asteroid.size(); j ++) {
            if (tiro[i].get_x_atual() < asteroid[j].get_x_atual() + asteroid[j].width &&
            tiro[i].get_x_atual() + tiro[i].width > asteroid[j].get_x_atual() &&
            tiro[i].get_y_atual() < asteroid[j].get_y_atual() + asteroid[j].height &&
            tiro[i].get_y_atual() + tiro[i].height > asteroid[j].get_y_atual()) {
                ast1.push_back(j);
                if(find(tir1.begin(),tir1.end(),i) == tir1.end()){
                    tir1.push_back(i);
                }
                nave.update_score(30);
            }   
        }
        int k = 0;
        if(!ast1.empty()){
            for(k=ast1.size()-1;k>-1;k--){
                asteroid.erase(asteroid.begin() + ast1[k]);
                ast1.pop_back();
            }
        }
    }
    for(i=0; i<tir1.size();i++){
        cout << tir1[i] << endl;
    }
    if(!tir1.empty()){
        for(i = tir1.size()-1; i > -1; i--) {
            tiro.erase(tiro.begin() + tir1[i]);
            tir1.pop_back();
        }
    }
}

void NaveController::set_rodando(bool valor){
    this->rodando=valor;
}