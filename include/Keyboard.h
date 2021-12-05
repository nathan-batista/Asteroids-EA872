#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>
#include "../src/json.hpp"

using namespace std;
#pragma once

class Keyboard{
    private:
        SDL_Event evento; // eventos discretos
        const Uint8* state;

    public:
        Keyboard();
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Keyboard,state);
        bool verificaTecla(string tecla);
        bool atualizaEvento();
        bool eventoDeSaida();
        bool eventoEspaco();
        void atualizarEstadoTeclado();
};



