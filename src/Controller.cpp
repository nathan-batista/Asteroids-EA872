#include "Controller.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Tiro.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

Controller::Controller(Model &model,vector<Asteroid> &asteroid) : model(model), asteroid(asteroid){
        this->rodando = true;
        this->state = SDL_GetKeyboardState(nullptr);
}

void Controller::polling(){
      SDL_PumpEvents(); // atualiza estado do teclado
      if (state[SDL_SCANCODE_LEFT]) model.set_x_atual(model.get_x_atual()-10);
      if (state[SDL_SCANCODE_RIGHT]) model.set_x_atual(model.get_x_atual() + 10);
      if (state[SDL_SCANCODE_UP]) model.set_y_atual(model.get_y_atual() - 10);
      if (state[SDL_SCANCODE_DOWN]) model.set_y_atual(model.get_y_atual() + 10);

      while (SDL_PollEvent(&(this->evento))) {
        if (this->evento.type == SDL_QUIT) {
          this->rodando = false;
        }

        else if(this->evento.type == SDL_KEYDOWN){
            if(state[SDL_SCANCODE_SPACE]){
                float x = model.get_x_atual();
                float y = model.get_y_atual();
                float vy = -100;
                float dt = model.get_dt();

                Tiro tiroNave = Tiro(x, y, 0, vy, dt);
                model.atirar(tiroNave);            
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

bool Controller::get_rodando(){
      return this->rodando;
}

void Controller::calcular_velocidade(){
    model.set_v_atual(model.get_v_atual() + a * model.get_dt());
}

void Controller::calcular_posicao(){
    model.set_x_atual(model.get_x_atual() + model.get_v_atual() * model.get_dt());
}

void Controller::update(){
    vector<int> ast1, tir1;
    vector <Tiro> tiros; 

    for(int i = 0; i < asteroid.size(); i++) {
        if (model.get_x_atual() < asteroid[i].get_x_atual() + asteroid[i].width &&
        model.get_x_atual() + model.width > asteroid[i].get_x_atual() &&
        model.get_y_atual() < asteroid[i].get_y_atual() + asteroid[i].height &&
        model.get_y_atual() + model.height > asteroid[i].get_y_atual() && !asteroid[i].destruir) {
       
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
    tiros = model.getTiro();
    for(int i = 0; i < tiros.size(); i ++) {
        if(tiros[i].get_y_atual() < -200) {
            tir1.push_back(i);
        }
    }
    
    for(int i = 0; i<tir1.size();i++){
        tiros.erase(tiros.begin() + tir1[i]);
        for(int k = i+1;k<tir1.size();k++){
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

void Controller::set_rodando(bool valor){
    this->rodando=valor;
}