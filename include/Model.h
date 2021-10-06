#include "Tiro.h"

#ifndef _Model_
#define _Model_

class Model{
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
        char *imagem_principal;
        char *imagem_fundo;
        Tiro &tiro;
    public:
        Model(float m, float k, float b, float x0, float y0, float v0, float dt,Tiro &tiro);
        float get_m();
        float get_k();
        float get_b();
        float get_dt();
        float get_x_atual();
        float get_y_atual();
        void set_x_atual(float new_x);
        void set_y_atual(float new_y);
        float get_v_atual();
        void set_v_atual(float new_v);
        Tiro& getTiro();
};

#endif
