
#include "../src/json.hpp"
#ifndef _Asteroid_
#define _Asteroid_


class Asteroid{
    private:
        float dt;
        float x_atual;
        float y_atual;
        float vx_atual;
        float vy_atual;
        
    public:
        Asteroid(float x0, float y0, float vx, float vy, float dt);
        Asteroid(){}
    	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Asteroid,dt,x_atual,y_atual,vx_atual,vy_atual);
        float get_dt();
        float width;
        float height;
        float get_x_atual();
        float get_y_atual();
        float get_vx_atual();
        float get_vy_atual();

        void set_x_atual(float new_x);
        void set_y_atual(float new_y);
    
};

#endif
