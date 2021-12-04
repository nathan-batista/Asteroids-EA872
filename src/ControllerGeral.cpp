#include "Nave.h"
#include "Tiro.h"
#include "Asteroid.h"
#include "ModelFinal.h"
#include <vector>
#include "Keyboard.h"
#include "ControllerGeral.h"
#include "NaveController.h"

using namespace std;

ControllerGeral::ControllerGeral(ModelFinal &m,vector<Asteroid> &a):model(m),asteroid(a);

void ControllerGeral::polling(){
    teclado.atualizarEstadoTeclado();
    if (teclado.verificaTecla("LEFT")) nave.set_x_atual(nave.get_x_atual()-10);
    if (teclado.verificaTecla("RIGHT")) nave.set_x_atual(nave.get_x_atual() + 10);
    if (teclado.verificaTecla("UP")) nave.set_y_atual(nave.get_y_atual() - 10);
    if (teclado.verificaTecla("DOWN")) nave.set_y_atual(nave.get_y_atual() + 10);

    while (teclado.atualizaEvento()) {
        if (teclado.eventoDeSaida()) {
          this->rodando = false;
        }

        else if(teclado.eventoEspaco()){
            float x = nave.get_x_atual();
            float y = nave.get_y_atual();
            float vy = -100;
            float dt = nave.get_dt();

            Tiro tiroNave = Tiro(x, y, 0, vy, dt);
            nave.atirar(tiroNave);            
        }
    }

    if(asteroid.size() < 20) {
        int x_rand = rand() % 1000 + 1;
        int y_rand = -120;
        int vx_rand = rand() % 20 + (-10);
        int vy_rand = rand() % 10 + 1;

        Asteroid asteroids = Asteroid(x_rand, y_rand, vx_rand, vy_rand, 0.1);
        asteroid.push_back(asteroids);
    }
}

void ControllerGeral::update(){

}