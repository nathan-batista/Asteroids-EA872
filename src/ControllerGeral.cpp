#include "ControllerGeral.h"
#include "Nave.h"
#include "Tiro.h"
#include "Asteroid.h"
#include "ModelFinal.h"
#include <vector>
#include "Keyboard.h"
#include "NaveController.h"

using namespace std;

ControllerGeral::ControllerGeral(ModelFinal &m,vector<Asteroid> &a):model(m),asteroid(a){

};

void ControllerGeral::polling(Keyboard &teclado){
    int i=0;
    vector<Nave>& navesDoJogo = model.getNaves();
    int id = teclado.id;
    if(!navesDoJogo.empty()){
            if (teclado.verTecla(0)) navesDoJogo[id].set_x_atual(navesDoJogo[id].get_x_atual()-10);
            if (teclado.verTecla(1)) navesDoJogo[id].set_x_atual(navesDoJogo[id].get_x_atual() + 10);
            if (teclado.verTecla(2)) navesDoJogo[id].set_y_atual(navesDoJogo[id].get_y_atual() - 10);
            if (teclado.verTecla(3)) navesDoJogo[id].set_y_atual(navesDoJogo[id].get_y_atual() + 10);

            if(teclado.verEspaco()){
                float x = navesDoJogo[id].get_x_atual();
                float y = navesDoJogo[id].get_y_atual();
                float vy = -100;
                float dt = navesDoJogo[id].get_dt();

                Tiro tiroNave = Tiro(x, y, 0, vy, dt);
                navesDoJogo[id].atirar(tiroNave);            
            } 
    }

    if(asteroid.size() < 20) {
        float x_rand = rand() % 1000 + 1;
        float y_rand = -120;
        float vx_rand = rand() % 20 + (-10);
        float vy_rand = rand() % 10 + 1;

        Asteroid asteroids = Asteroid(x_rand, y_rand, vx_rand, vy_rand, 0.1);
        asteroid.push_back(asteroids);
    }
}

void ControllerGeral::update(){
    vector<Nave> &navesDoJogo = model.getNaves();
    if(!navesDoJogo.empty()){
        for(int i =0;i<navesDoJogo.size();i++){
            vector<int> ast1, tir1;
            vector<Tiro>&tiro = navesDoJogo[i].getTiro();
            int k= 0;
            if(navesDoJogo[i].id == -1){
                break;
            }
            if(navesDoJogo[i].get_colidiu()){
                continue;
            }


            for(k = 0; k < asteroid.size(); k++) {
                if(asteroid.empty()){
                    break;
                }
                if ((navesDoJogo[i].get_x_atual() < asteroid[k].get_x_atual() + asteroid[k].width &&
                navesDoJogo[i].get_x_atual() + navesDoJogo[i].width > asteroid[k].get_x_atual() &&
                navesDoJogo[i].get_y_atual() < asteroid[k].get_y_atual() + asteroid[k].height &&
                navesDoJogo[i].get_y_atual() + navesDoJogo[i].height > asteroid[k].get_y_atual())) {
                    navesDoJogo[i].gameover();
                }

                if((asteroid[k].get_x_atual() > 1200 || asteroid[k].get_x_atual() < -200) || (asteroid[k].get_y_atual() < -800)) {
                    ast1.push_back(i);   
                }
            }
            if(!ast1.empty()){
                for(k = ast1.size()-1; i>-1;i--){
                    asteroid.erase(asteroid.begin() + ast1[k]);
                    ast1.pop_back();
                }
            }
        
            for(k = 0; k < tiro.size(); k ++) {
                if(tiro[k].get_y_atual() < -200) {
                    tir1.push_back(k);
                }
            }

            if(!tir1.empty()){
                for(k = tir1.size()-1; k>-1;k--){
                    tiro.erase(tiro.begin() + tir1[k]);
                    tir1.pop_back();
                }
            }

            int j = 0;
            for(k = 0; k < tiro.size(); k++) {
                if(asteroid.empty() || tiro.empty()){
                    break;
                }
                for(j = 0; j < asteroid.size(); j ++) {
                    if (tiro[k].get_x_atual() < asteroid[j].get_x_atual() + asteroid[j].width &&
                    tiro[k].get_x_atual() + tiro[k].width > asteroid[j].get_x_atual() &&
                    tiro[k].get_y_atual() < asteroid[j].get_y_atual() + asteroid[j].height &&
                    tiro[k].get_y_atual() + tiro[k].height > asteroid[j].get_y_atual()) {
                        ast1.push_back(j);
                        if(find(tir1.begin(),tir1.end(),k) == tir1.end()){
                            tir1.push_back(k);
                        }
                        navesDoJogo[i].update_score(30);
                    }   
                }
                int h = 0;
                if(!ast1.empty()){
                    for(h=ast1.size()-1;h>-1;h--){
                        asteroid.erase(asteroid.begin() + ast1[h]);
                        ast1.pop_back();
                    }
                }
            }
            if(!tir1.empty()){
                for(k = tir1.size()-1; k > -1; k--) {
                    tiro.erase(tiro.begin() + tir1[k]);
                    tir1.pop_back();
                }
            }
        }
    }
}