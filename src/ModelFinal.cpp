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
    /*
    unsigned int num_naves = naves.size();
    int remover = -1;
    for(int i=0; i<num_naves;i++){
        if(naves[i].get_id() == id){
            remover = i;
            break;
        }
    }
    if(remover != -1){
        naves.erase(naves.begin() + remover);
    }
    */
}

vector<Nave>& ModelFinal::getNaves(){
    return this->naves;
}