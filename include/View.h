#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Model.h"


#ifndef _View_
#define _View_
class View{
    private:
        Model &model;
        SDL_Renderer* renderer;
        SDL_Window* window;
        SDL_Rect target;
        SDL_Texture *texture;
        SDL_Texture *texture2;
    public:
        View(Model &model);
        void renderizar();
        void destruir();
};

#endif