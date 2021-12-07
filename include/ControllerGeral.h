#include "Nave.h"
#include "Tiro.h"
#include "Asteroid.h"
#include "ModelFinal.h"
#include <vector>
#include "Keyboard.h"

using namespace std;

#pragma once

class ControllerGeral{
    private:
        bool rodando;
        ModelFinal &model;
        Keyboard teclado;
        vector<Asteroid> &asteroid;

    public:
        ControllerGeral(ModelFinal &m,vector<Asteroid> &a);
        void polling(Keyboard &teclado);
        void update();
};