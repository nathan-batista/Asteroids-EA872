#include "View.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;

View::View(Nave &nave, vector<Asteroid> &asteroid) : nave(nave), asteroid(asteroid) {

    // Inicializando o subnaveema de video do SDL
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

    //Carregando fonte
    
int TTF_Init();

    if(TTF_Init()==-1) {
        cerr << "Failed to initialize ttf library!\n";
        cerr << "SDL_TTF Error: " << TTF_GetError() << "\n";
    }

    this->fontSize = 24;
    this->fontpath = "../assets/PixelGameFont.ttf";
    this->font = TTF_OpenFont(fontpath.c_str(), fontSize);
    this->gameover = TTF_OpenFont(fontpath.c_str(), 80);

    carregarFonte("SCORE: " + to_string(0));


    // Carregando texturas

    // personagem
    this->texture = IMG_LoadTexture(this->renderer, "../assets/nave-espacial.png");  
    this->target.x = nave.get_x_atual();
    this->target.y = nave.get_y_atual();
    // fundo
    this->texture2 = IMG_LoadTexture(this->renderer, "../assets/space1.jpeg");      
    //Asteroid
    this->texture3 = IMG_LoadTexture(this->renderer,"../assets/meteor.png" );
    //Tiro
    this->texture4 = IMG_LoadTexture(this->renderer,"../assets/tiro.png" );
    this->target_tiro.x = 50;
    this->target_tiro.y = 50;
    

    SDL_QueryTexture(this->texture, nullptr, nullptr, &(this->target.w), &(this->target.h));
}

void View::renderizar(){

    if (!nave.get_colidiu()){

    // Desenhar a cena
    target.x = nave.get_x_atual();
    target.y = nave.get_y_atual();
    target.h = nave.height;
    target.w = nave.width;

    //Desenhar o score
    carregarFonte("SCORE: " + to_string(nave.get_score()) );
    target_score.x = 800;
    target_score.y = 560;
    target_score.h = this->t_height;
    target_score.w = this->t_width;

    SDL_RenderClear(this->renderer);
    SDL_RenderCopy(this->renderer, this->texture2, nullptr, nullptr);
    SDL_RenderCopy(this->renderer, this->score_texture, nullptr, &(this->target_score));

    vector<Tiro> tiros = nave.getTiro();
    if(!tiros.empty()){
        for(int i = 0; i < tiros.size(); i++) {
            target_tiro.x = tiros[i].get_x_atual();
            target_tiro.y = tiros[i].get_y_atual();    
            target_tiro.w = tiros[i].width;
            target_tiro.h = tiros[i].height;
            SDL_RenderCopy(this->renderer, this->texture4, nullptr, &(this->target_tiro));
        }
    }
    
    for(int i = 0; i < asteroid.size(); i++) {
        target_ast.x = asteroid[i].get_x_atual();
        target_ast.y = asteroid[i].get_y_atual();
        target_ast.h = asteroid[i].height;
        target_ast.w = asteroid[i].width;
        SDL_RenderCopy(this->renderer, this->texture3, nullptr, &(this->target_ast));    
    }

    if(!nave.destruir){
        SDL_RenderCopy(this->renderer, this->texture, nullptr, &(this->target));
    }

    SDL_Delay(1);

    }else{
        carregarGameOver("GAME OVER");
        target_score.x = 280;
        target_score.y = 280;
        target_score.h = this->t_height;
        target_score.w = this->t_width;

        SDL_RenderCopy(this->renderer, this->score_texture, nullptr, &(this->target_score));

        SDL_Delay(0);
    }

    SDL_RenderPresent(this->renderer);
    // Delay para diminuir o framerate
    
}

void View::destruir(){
    SDL_DestroyTexture(this->texture);
    SDL_DestroyTexture(this->texture2);
    SDL_DestroyTexture(this->texture3);
    SDL_DestroyTexture(this->texture4);
    SDL_DestroyTexture(this->score_texture);
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
    TTF_Quit();
}

void View::carregarFonte( string txt){
    this->text_color = {255,255, 255};
    this->t_height = this->t_width = 0;
    this->text = txt;
    this->score_texture = NULL; // our font-texture

    // check to see that the font was loaded correctly
    if (this->font == NULL) {
        cerr << "Failed the load the font!\n";
        cerr << "SDL_TTF Error: " << TTF_GetError() << "\n";
    }
    else {
        // now create a surface from the font
        this->text_surface = TTF_RenderText_Solid(this->font, text.c_str(), text_color);

        // render the text surface
        if (this->text_surface == NULL) {
            cerr << "Failed to render text surface!\n";
            cerr << "SDL_TTF Error: " << TTF_GetError() << "\n";
        }
        else {
            // create a texture from the surface
            score_texture = SDL_CreateTextureFromSurface(this->renderer, this->text_surface);

            if (score_texture == NULL) {
                cerr << "Unable to create texture from rendered text!\n";
            }
            else {
                t_width = text_surface->w; // assign the width of the texture
                t_height = text_surface->h; // assign the height of the texture

                // clean up after ourselves (destroy the surface)
                SDL_FreeSurface(text_surface);
            }
        }
    }
}

void View::carregarGameOver( string txt){
    this->text_color = {255,255, 255};
    this->t_height = this->t_width = 0;
    this->text = txt;
    this->score_texture = NULL; // our font-texture

    // check to see that the font was loaded correctly
    if (this->gameover == NULL) {
        cerr << "Failed the load the font!\n";
        cerr << "SDL_TTF Error: " << TTF_GetError() << "\n";
    }
    else {
        // now create a surface from the font
        this->text_surface = TTF_RenderText_Solid(this->gameover, text.c_str(), text_color);

        // render the text surface
        if (this->text_surface == NULL) {
            cerr << "Failed to render text surface!\n";
            cerr << "SDL_TTF Error: " << TTF_GetError() << "\n";
        }
        else {
            // create a texture from the surface
            score_texture = SDL_CreateTextureFromSurface(this->renderer, this->text_surface);

            if (score_texture == NULL) {
                cerr << "Unable to create texture from rendered text!\n";
            }
            else {
                t_width = text_surface->w; // assign the width of the texture
                t_height = text_surface->h; // assign the height of the texture

                // clean up after ourselves (destroy the surface)
                SDL_FreeSurface(text_surface);
            }
        }
    }
}

