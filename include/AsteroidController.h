#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Asteroid.h"
#include <vector>
using namespace std;

#ifndef _AsteroidController_
#define _AsteroidController_
class AsteroidController{
    private:
     
        // Variaveis para verificar eventos
        //SDL_Event evento; // eventos discretos
        //const Uint8* state;  // estado do teclado
        vector<Asteroid> &asteroid;
        //const Uint8* state;

    public:
        AsteroidController(vector<Asteroid> &asteroid);
        void calcular_posicao();
        void update();
};

#endif
