#include "Asteroid.h"

Asteroid::Asteroid(float x, float y, float vx, float vy, float dt){
      //setando variaveis iniciais
      this->x_atual = x;   
      this->y_atual = y;
      this->vx_atual= vx;
      this->vy_atual= vy;
      this->dt = dt;
};

float Asteroid::get_dt(){
    return this->dt;
}
float Asteroid::get_x_atual(){
    return this->x_atual;
}
float Asteroid::get_y_atual(){
    return this->y_atual;
}
float Asteroid::get_vx_atual(){
    return this->vx_atual;
}
float Asteroid::get_vy_atual(){
    return this->vy_atual;
}

void Asteroid::set_x_atual(float new_x){
    this->x_atual = new_x;
}
void Asteroid::set_y_atual(float new_y){
    this->y_atual = new_y;
}
