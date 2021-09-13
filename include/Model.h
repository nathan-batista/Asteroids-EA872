#ifndef _Model_
#define _Model_

class Model{
    private:
        float m;
        float k;
        float b;
        float x0;
        float v0;
        float dt;
        float x_atual;
        float v_atual;
        char *imagem_principal;
        char *imagem_fundo;
    public:
        Model(float m, float k, float b, float x0, float v0, float dt);
        float get_m();
        float get_k();
        float get_b();
        float get_dt();
        float get_x_atual();
        void set_x_atual(float new_x);
        float get_v_atual();
        void set_v_atual(float new_v);
};

#endif