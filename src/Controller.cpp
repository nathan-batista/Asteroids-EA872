#include "Controller.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Tiro.h"
#include <iostream>
#include <vector>
using namespace std;

Controller::Controller(Model &model,Asteroid &asteroid) : model(model), asteroid(asteroid){
        this->rodando = true;
        this->state = SDL_GetKeyboardState(nullptr);
        f=0;
        a=0;
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

                cout << "Cheguei no negocio" << endl;
            }
        }
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
    if (model.get_x_atual() < asteroid.get_x_atual() + asteroid.width &&
        model.get_x_atual() + model.width > asteroid.get_x_atual() &&
        model.get_y_atual() < asteroid.get_y_atual() + asteroid.height &&
        model.get_y_atual() + model.height > asteroid.get_y_atual() && !asteroid.destruir) {
       
        set_rodando(false);
        model.destruir=true;
        asteroid.destruir=true;
    }
   /* if(tiro.flag){
        if (tiro.get_x_atual() < asteroid.get_x_atual() + asteroid.width &&
        tiro.get_x_atual() + tiro.width > asteroid.get_x_atual() &&
        tiro.get_y_atual() < asteroid.get_y_atual() + asteroid.height &&
        tiro.get_y_atual() + tiro.height > asteroid.get_y_atual() && !asteroid.destruir) {
             
            tiro.destruir = true;
            asteroid.destruir = true;
        }     
    }*/
}

void Controller::set_rodando(bool valor){
    this->rodando=valor;
}
                      
