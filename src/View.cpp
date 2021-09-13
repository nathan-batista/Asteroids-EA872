#include "View.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;

View::View(Model &model) : model(model){

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
    this->texture = IMG_LoadTexture(this->renderer, "../assets/capi.png");
    // fundo
    this->texture2 = IMG_LoadTexture(this->renderer, "../assets/park.jpeg");
    
    this->target.x = model.get_x_atual();
    this->target.y = 120;
    SDL_QueryTexture(this->texture, nullptr, nullptr, &(this->target.w), &(this->target.h));

}

void View::renderizar(){
    // Desenhar a cena
    target.x = model.get_x_atual();
    SDL_RenderClear(this->renderer);
    SDL_RenderCopy(this->renderer, this->texture2, nullptr, nullptr);
    SDL_RenderCopy(this->renderer, this->texture, nullptr, &(this->target));
    SDL_RenderPresent(this->renderer);
    // Delay para diminuir o framerate
    SDL_Delay(10);
}

void View::destruir(){
    SDL_DestroyTexture(this->texture);
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}
