#include "View.h"
#include "NaveController.h"
#include "Nave.h"
#include "Asteroid.h"
#include "AsteroidController.h"
#include "TiroController.h"
#include "Tiro.h"
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "json.hpp"
#include <fstream>

using namespace std;
using nlohmann::json;

int main() { 
  //Tiro tiro = Tiro(-10,-10,0,0,0);
  vector<Tiro> tiros;
  vector<Asteroid> asteroids;
  json j;

  Nave nave = Nave(1, 1, 0, 320, 120, 30, 0.1, tiros);
  Asteroid asteroid = Asteroid(0, 0, 10, 10, 0.1);
  View view = View(nave, asteroids);
  AsteroidController asteroidcontroller = AsteroidController(asteroids);
  NaveController naveController = NaveController(nave, asteroids);
  TiroController tiroController = TiroController();

  // Laco principal do jogo
  while(naveController.get_rodando()) {
    naveController.polling();
    asteroidcontroller.update();
    tiroController.update(nave.getTiro());
    naveController.update();
    view.renderizar();
    
  }

  j["asteroides"] = asteroids;
  j["tiros"] = tiros;
  j["nave"] = nave;
  ofstream f;
  f.open("teste.json");
  f << j;
  f.close();

 
  view.destruir();
  
  return 0;
}