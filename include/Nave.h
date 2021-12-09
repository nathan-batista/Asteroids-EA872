#include "Tiro.h"
#include <vector>
#include "../src/json.hpp"
using namespace std;

#pragma once

class Nave{
    private:
        float m;
        float k;
        float b;
        float x0;
        float y0;
        float v0;
        float dt;
        float x_atual;
        float y_atual;
        float v_atual;
        bool colidiu;
        int score;
        char *imagem_principal;
        char *imagem_fundo;
        vector<Tiro> tiro;
        int id;
    public:
        Nave(float m, float k, float b, float x0, float y0, float v0, float dt,int identificador);
        Nave(){}
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Nave,m,k,b,x0,y0,v0,dt,x_atual,y_atual,v_atual,score,tiro,width,height,destruir,id);
        float get_m();
        float width;
        float height;
        bool destruir;
        float get_k();
        float get_b();
        float get_dt();
        float get_x_atual();
        float get_y_atual();
        int get_id();
        int get_score();
        bool get_colidiu();
        void gameover();
        void set_x_atual(float new_x);
        void set_y_atual(float new_y);
        float get_v_atual();
        void set_v_atual(float new_v);
        void atirar(Tiro &tiro);
        void update_score(int i);
        void apagar_tiro(int i);
        vector<Tiro>& getTiro();
        vector<Tiro> verTiro();
};
