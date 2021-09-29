#include "View.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;

View::View(Model &model, Asteroid &asteroid,Tiro &tiro) : model(model), asteroid(asteroid), tiro(tiro) {


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
    

    SDL_QueryTexture(this->texture, nullptr, nullptr, &(this->target.w), &(this->target.h));

}

void View::renderizar(){
    // Desenhar a cena
    target.x = model.get_x_atual();
    target.y = model.get_y_atual();
    target.h = 65;
    target.w = 65;

    target_ast.x = asteroid.get_x_atual();
    target_ast.y = asteroid.get_y_atual();
    target_ast.h = 65;
    target_ast.w = 65;
    SDL_RenderClear(this->renderer);
    if(this->tiro.flag == true){
        cout << "Renderrr" << endl;
        target_tiro.x = tiro.get_x_atual();
        target_tiro.y = tiro.get_y_atual();
        target_tiro.w = 5;
        target_tiro.h = 10;
        SDL_RenderCopy(this->renderer, this->texture4, nullptr, &(this->target_tiro));
        cout << "Renderizei" << endl;
    }
    SDL_RenderCopy(this->renderer, this->texture2, nullptr, nullptr);
    SDL_RenderCopy(this->renderer, this->texture, nullptr, &(this->target));
    SDL_RenderCopy(this->renderer, this->texture3, nullptr, &(this->target_ast));
    
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


