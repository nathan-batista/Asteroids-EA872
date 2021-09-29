#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Model.h"

#ifndef _Controller_
#define _Controller_
class Controller{
    private:
        float a, f;
        bool rodando;
        // Variaveis para verificar eventos
        SDL_Event evento; // eventos discretos
        //const Uint8* state;  // estado do teclado
        Model &model;
        const Uint8* state;

    public:
        Controller(Model &model);
        void polling();
        bool get_rodando();
        void calcular_forca();
        void estimar_aceleracao();
        void calcular_velocidade();
        void calcular_posicao();
        void update();
};

#endif
