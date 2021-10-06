#include "Model.h"
#include "Tiro.h"
#include <iostream>
using namespace std;

Model::Model(float m, float k, float b, float x0, float y0, float v0, float dt,Tiro &tiro) : tiro(tiro){
      //setando variaveis iniciais
      this->m = m;
      this->k = k;
      this->b = b;
      this->x0 = x0;
      this->v0 = v0;
      this->dt = dt;
      this->x_atual = x0;
      this->y_atual = y0;
      this->v_atual = v0;
      this->destruir = false;
      this->width = 65;
      this->height = 65;
}
float Model::get_m(){
    return this->m;
}
float Model::get_k(){
    return this->k;
}
float Model::get_b(){
    return this->b;
}
float Model::get_dt(){
    return this->dt;
}
float Model::get_x_atual(){
    return this->x_atual;
}
float Model::get_y_atual(){
    return this->y_atual;
}
void Model::set_x_atual(float new_x){
    this->x_atual = new_x;
}
void Model::set_y_atual(float new_y){
    this->y_atual = new_y;
}
float Model::get_v_atual(){
    return this->v_atual;
}
void Model::set_v_atual(float new_v){
    this->v_atual = new_v;
}

Tiro& Model::getTiro(){
    return (this->tiro);
}