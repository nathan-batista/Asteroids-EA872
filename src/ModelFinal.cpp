#include "Nave.h"
#include "Tiro.h"
#include "ModelFinal.h"
#include <vector>

ModelFinal::ModelFinal(vector<Nave> &n) : naves(n){

};

void ModelFinal::adicionar_nave(Nave &n){
    naves.push_back(n);
}

void ModelFinal::remover_nave(int id){
}

vector<Nave>& ModelFinal::getNaves(){
    return this->naves;
}

vector<Nave> ModelFinal::verNaves(){
    return this->naves;
}