#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Nave.h"
#include "Asteroid.h"
#include "Tiro.h"
#include <vector>
using namespace std;


#ifndef _NaveController_
#define _NaveController_
class NaveController{
    private:
        float a, f;
        bool rodando;
        // Variaveis para verificar eventos
        SDL_Event evento; // eventos discretos
        //const Uint8* state;  // estado do teclado
        Nave &nave;

        vector<Asteroid> &asteroid;
        const Uint8* state;

    public:
        NaveController(Nave &nave, vector<Asteroid> &asteroid);
        void polling();
        bool get_rodando();
        void calcular_velocidade();
        void calcular_posicao();
        void update();
        void set_rodando(bool valor);
};

#endif
