#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>

using namespace std;
#pragma once

class Keyboard{
    private:
        SDL_Event evento; // eventos discretos
        const Uint8* state;

    public:
        Keyboard();
        bool verificaTecla(string tecla);
        bool verificaSaida();
};



