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
    vector <Tiro> tiros; 

    for(int i = 0; i < asteroid.size(); i++) {
        if (nave.get_x_atual() < asteroid[i].get_x_atual() + asteroid[i].width &&
        nave.get_x_atual() + nave.width > asteroid[i].get_x_atual() &&
        nave.get_y_atual() < asteroid[i].get_y_atual() + asteroid[i].height &&
        nave.get_y_atual() + nave.height > asteroid[i].get_y_atual() && !asteroid[i].destruir) {
       
            this->rodando = false;
        }

        if((asteroid[i].get_x_atual() > 1200 || asteroid[i].get_x_atual() < -200) || (asteroid[i].get_y_atual() < -800)) {
            ast1.push_back(i);   
        }
    }
    if(!ast1.empty()){
        for(int i = 0; i<ast1.size();i++){
            asteroid.erase(asteroid.begin() + ast1[i]);
            for(int k = i+1;k<ast1.size();k++){
                ast1[k] -= 1;
            }
        }
    }
    

    ast1.clear();
    
    tiros = nave.getTiro();
    for(int i = 0; i < tiros.size(); i ++) {
        if(tiros[i].get_y_atual() < -200) {
            tir1.push_back(i);
        }
    }
    
    for(int i = 0; i<tir1.size();i++){
        tiros.erase(tiros.begin() + tir1[i]);
        for(int k = i+1; k<tir1.size(); k++){
            tir1[k] -= 1;
        }
    }

    tir1.clear();

    
    for(int i = 0; i < tiros.size(); i++) {
        for(int j = 0; j < asteroid.size(); j ++) {
  
            if (tiros[i].get_x_atual() < asteroid[j].get_x_atual() + asteroid[j].width &&
            tiros[i].get_x_atual() + tiros[i].width > asteroid[j].get_x_atual() &&
            tiros[i].get_y_atual() < asteroid[j].get_y_atual() + asteroid[j].height &&
            tiros[i].get_y_atual() + tiros[i].height > asteroid[j].get_y_atual()&& !asteroid[j].destruir) {
                 
                ast1.push_back(j);
                tir1.push_back(i);
                nave.update_score(30);

            }   
        }
        for(int k=0;k<ast1.size();k++){
            asteroid.erase(asteroid.begin() + ast1[i]);
            for(int u = k+1;u<ast1.size();u++){
                ast1[u] -= 1;
            }
        }
        ast1.clear();
    }

    for(int i = 0; i < tir1.size(); i++) {
        tiros.erase(tiros.begin() + tir1[i]);
        for(int u = i+1;u<tir1.size();u++){
                tir1[u] -= 1;
        }
    }

}

void NaveController::set_rodando(bool valor){
    this->rodando=valor;
}