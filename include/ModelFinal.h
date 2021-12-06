#include "Tiro.h"
#include "Nave.h"
#include "../src/json.hpp"
#include <vector>
using namespace std;
#pragma once

class ModelFinal{
    private:
        vector<Nave> &naves;
        
    public:
        ModelFinal(vector<Nave> &n);
        void adicionar_nave(Nave &n);
        void remover_nave(int id);
        vector<Nave> &getNaves();
};