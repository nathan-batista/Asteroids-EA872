#include "View.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;

View::View(Model &model, Asteroid &asteroid) : model(model), asteroid(asteroid) {

    // Inicializando o submodelema de video do SDL
    if ( SDL_Init (SDL_INIT_VIDEO) < 0 ) {
        cout << SDL_GetError();
    }
    // Criando uma janela
    this->window = nullptr;
    this->window = SDL_CreateWindow("Demonstracao do SDL2",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (this->window==nullptr) { // Em caso de erro...
        cout << SDL_GetError();
        SDL_Quit();
    }

        // Inicializando o renderizador
    this->renderer = SDL_CreateRenderer(
        this->window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (this->renderer==nullptr) { // Em caso de erro...
        SDL_DestroyWindow(this->window);
        cout << SDL_GetError();
        SDL_Quit();
    }
    // Carregando texturas
    // personagem
    this->texture = IMG_LoadTexture(this->renderer, "../assets/nave-espacial.png");  
    this->target.x = model.get_x_atual();
    this->target.y = model.get_y_atual();
    // fundo
    this->texture2 = IMG_LoadTexture(this->renderer, "../assets/space1.jpeg");      
    //Asteroid
    this->texture3 = IMG_LoadTexture(this->renderer,"../assets/capi.png" );
    this->target_ast.x = asteroid.get_x_atual();
    this->target_ast.y = asteroid.get_y_atual();

    this->texture4 = IMG_LoadTexture(this->renderer,"../assets/tiro.png" );
    this->target_tiro.x = 50;
    this->target_tiro.y = 50;
    

    SDL_QueryTexture(this->texture, nullptr, nullptr, &(this->target.w), &(this->target.h));

}

void View::renderizar(){
    // Desenhar a cena
    target.x = model.get_x_atual();
    target.y = model.get_y_atual();
    target.h = model.height;
    target.w = model.width;

    target_ast.x = asteroid.get_x_atual();
    target_ast.y = asteroid.get_y_atual();
    target_ast.h = asteroid.height;
    target_ast.w = asteroid.width;
    SDL_RenderClear(this->renderer);
    SDL_RenderCopy(this->renderer, this->texture2, nullptr, nullptr);


    
    vector<Tiro> tiros = model.getTiro();
    for(int i = 0; i < tiros.size(); i++) {
        target_tiro.x = tiros[i].get_x_atual();
        target_tiro.y = tiros[i].get_y_atual();    
        target_tiro.w = tiros[i].width;
        target_tiro.h = tiros[i].height;
        SDL_RenderCopy(this->renderer, this->texture4, nullptr, &(this->target_tiro));
    }

    if(!model.destruir){
        SDL_RenderCopy(this->renderer, this->texture, nullptr, &(this->target));
    }
    if(!asteroid.destruir){
        cout<<"Asteroideeee" << endl;
        SDL_RenderCopy(this->renderer, this->texture3, nullptr, &(this->target_ast));
    }

    SDL_RenderPresent(this->renderer);
    // Delay para diminuir o framerate
    SDL_Delay(1);
    
}

void View::destruir(){
    SDL_DestroyTexture(this->texture);
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}


