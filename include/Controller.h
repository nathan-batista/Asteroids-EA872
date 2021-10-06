#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Model.h"
#include "Asteroid.h"
#include "Tiro.h"
#include <vector>
using namespace std;


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

        Asteroid &asteroid;
        const Uint8* state;

    public:
        Controller(Model &model, Asteroid &asteroid);
        void polling();
        bool get_rodando();
        void calcular_forca();
        void estimar_aceleracao();
        void calcular_velocidade();
        void calcular_posicao();
        void update();
        void set_rodando(bool valor);
};

#endif
