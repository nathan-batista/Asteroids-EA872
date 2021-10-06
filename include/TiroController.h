#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Tiro.h"

class TiroController{
    private:
        // Variaveis para verificar eventos
        //SDL_Event evento; // eventos discretos
        //const Uint8* state;  // estado do teclado
        //const Uint8* state;

    public:
        TiroController();
        void calcular_posicao(Tiro &tiro);
        void update(Tiro &tiro);
};
