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
        int teclas[4] = {0,0,0,0};
        int atirou=0;
        int saiu = 0;

    public:
        Keyboard();
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Keyboard,teclas,atirou);
        void verificaTecla();
        bool atualizaEvento();
        int eventoDeSaida();
        void eventoEspaco();
        void atualizarEstadoTeclado();
        int verTecla(int numTecla);
        int verEspaco();
        int verSaiu();
};



