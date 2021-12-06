#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Nave.h"
#include "Asteroid.h"
#include "ModelFinal.h"
#include "Tiro.h"
#include <vector>
#include <iostream>
using namespace std;

#pragma once
class View{
    private:
        ModelFinal &model;
        vector<Asteroid> &asteroid;
        SDL_Renderer* renderer;
        SDL_Window* window;
        SDL_Rect target;
        SDL_Rect target_ast;
        SDL_Rect target_tiro;
        SDL_Rect target_score;
        SDL_Texture *texture;
        SDL_Texture *texture2;
        SDL_Texture *texture3;
        SDL_Texture *texture4;
        SDL_Texture *score_texture;
        SDL_Texture *gameover_texture;
        TTF_Font *font;
        TTF_Font *gameover;
        int fontSize;
        SDL_Color text_color;
        string fontpath;
        string text;
        SDL_Surface* text_surface;
        int t_width;
        int t_height;
    public:
        View(ModelFinal &model, vector<Asteroid> &asteroid);
        void renderizar();
        void destruir();
        void carregarFonte(string txt);
        void carregarGameOver(string txt);

};


