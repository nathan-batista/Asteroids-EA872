#include "Tiro.h"

Tiro::Tiro(float x, float y, float vx, float vy, float dt){
      //setando variaveis iniciais
      this->x_atual = x;   
      this->y_atual = y;
      this->vx_atual= vx;
      this->vy_atual= vy;
      this->dt = dt;
      this->flag = false;
};

float Tiro::get_dt(){
    return this->dt;
}
float Tiro::get_x_atual(){
    return this->x_atual;
}
float Tiro::get_y_atual(){
    return this->y_atual;
}
float Tiro::get_vx_atual(){
    return this->vx_atual;
}
float Tiro::get_vy_atual(){
    return this->vy_atual;
}

void Tiro::set_x_atual(float new_x){
    this->x_atual = new_x;
}
void Tiro::set_y_atual(float new_y){
    this->y_atual = new_y;
}