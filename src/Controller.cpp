#include "Controller.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



Controller::Controller(Model &model) : model(model){
        this->rodando = true;
        this->state = SDL_GetKeyboardState(nullptr);
        f=0;
        a=0;
}

void Controller::polling(){
        SDL_PumpEvents(); // atualiza estado do teclado
        if (state[SDL_SCANCODE_LEFT]){
            float x = model.get_x_atual();
            x -= 3;
            model.set_x_atual(x);
        } 
        if (state[SDL_SCANCODE_RIGHT]) {
            float x = model.get_x_atual();
            x += 3;
            model.set_x_atual(x);
        }
        if (state[SDL_SCANCODE_UP]){
            float y = model.get_y_atual();
            y -= 3;
            model.set_y_atual(y);
        }
        if (state[SDL_SCANCODE_DOWN]){
            float y = model.get_y_atual();
            y += 3;
            model.set_y_atual(y);
        }

      while (SDL_PollEvent(&(this->evento))) {
        if (this->evento.type == SDL_QUIT) {
          this->rodando = false;
        }
        // Exemplos de outros eventos.
        // Que outros eventos poderiamos ter e que sao uteis?
        // if (evento.type == SDL_KEYDOWN) {
        // }
        // else if (evento.type == SDL_KEYUP) {
        // }
        // else if (evento.type == SDL_KEYRIGHT) {
        //     float x = model.get_x_atual();
        //     x = x + 1;
        //     model.set_x_atual(x);
        // }
        // else if (evento.type == SDL_KEYLEFT) {
        // }

        //if (evento.type == SDL_MOUSEBUTTONDOWN) {
        //}
    }
}

bool Controller::get_rodando(){
      return this->rodando;
}

void Controller::calcular_forca(){
    f = -(model.get_x_atual()-320)*model.get_k() - model.get_b()*model.get_v_atual();
}
void Controller::estimar_aceleracao(){
    a = f/model.get_m();
}
void Controller::calcular_velocidade(){
    model.set_v_atual(model.get_v_atual() + a * model.get_dt());
}
void Controller::calcular_posicao(){  
    model.set_x_atual(model.get_x_atual() + model.get_v_atual() * model.get_dt());
}
void Controller::update(){
    // calcular_forca();
    // estimar_aceleracao();   
    // calcular_velocidade();
    // calcular_posicao();              
}