#include "Nave.h"
#include "Tiro.h"
#include <iostream>
#include <vector>
using namespace std;

Nave::Nave(float m, float k, float b, float x0, float y0, float v0, float dt,int identificador){
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
      //this->destruir = false;
      this->width = 65;
      this->height = 65;
      this->score = 0;
      this->colidiu = false;
      this->id = identificador;
}
float Nave::get_m(){
    return this->m;
}
float Nave::get_k(){
    return this->k;
}
float Nave::get_b(){
    return this->b;
}
float Nave::get_dt(){
    return this->dt;
}
float Nave::get_x_atual(){
    return this->x_atual;
}
float Nave::get_y_atual(){
    return this->y_atual;
}
void Nave::set_x_atual(float new_x){
    this->x_atual = new_x;
}
void Nave::set_y_atual(float new_y){
    this->y_atual = new_y;
}
float Nave::get_v_atual(){
    return this->v_atual;
}

int Nave::get_id(){
    return this->id;
}

int Nave::get_score(){
    return this->score;
}

void Nave::set_v_atual(float new_v){
    this->v_atual = new_v;
}
void Nave::atirar(Tiro &tiro) {
    this->tiro.push_back(tiro);
}

void Nave::update_score(int i){
    this->score +=  30;
}

bool Nave::get_colidiu(){
    return this->colidiu;
}
void Nave::gameover(){
    this->colidiu = true;
}

vector<Tiro>& Nave::getTiro(){
    return (this->tiro);
}

vector<Tiro> Nave::verTiro(){
    return (this->tiro);
}