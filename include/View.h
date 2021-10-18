#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Nave.h"
#include "Asteroid.h"
#include "Tiro.h"
#include <vector>
#include <iostream>
using namespace std;

#ifndef _View_
#define _View_
class View{
    private:
        Nave &nave;
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
        TTF_Font *font;
        int fontSize;
        SDL_Color text_color;
        string fontpath;
        string text;
        SDL_Surface* text_surface;
        int t_width;
        int t_height;
    public:
        View(Nave &nave, vector<Asteroid> &asteroid);
        void renderizar();
        void destruir();
        void carregarFonte(int score);
};

#endif
