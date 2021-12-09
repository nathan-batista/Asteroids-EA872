#include "../src/json.hpp"
#pragma once

class Tiro{
    private:
        float dt;
        float x_atual;
        float y_atual;
        float vx_atual;
        float vy_atual;
    
    public:
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Tiro,dt,x_atual,y_atual,vx_atual,vy_atual);
        Tiro(){}
        Tiro(float x0, float y0, float vx, float vy, float dt);
        bool flag;
        bool destruir;
        float width;
        float height;
        float get_dt();
        float get_x_atual();
        float get_y_atual();
        float get_vx_atual();
        float get_vy_atual();
        
	void set_vy(float new_vy);
        void set_x_atual(float new_x);
        void set_y_atual(float new_y);
        bool getFlag();
        void set_dt(float new_dt);
};
