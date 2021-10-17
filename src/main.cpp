#include "View.h"
#include "Controller.h"
#include "Model.h"
#include "Asteroid.h"
#include "AsteroidController.h"
#include "TiroController.h"
#include "Tiro.h"
#include <vector>

using namespace std;

int main() { 
  //Tiro tiro = Tiro(-10,-10,0,0,0);
  vector<Tiro> tiros;
  vector<Asteroid> asteroids;

  Model model = Model(1, 1, 0, 320, 120, 30, 0.1, tiros);
  Asteroid asteroid = Asteroid(0, 0, 10, 10, 0.1);
  View view = View(model, asteroids);
  AsteroidController asteroidcontroller = AsteroidController(asteroids);
  Controller controller = Controller(model, asteroids);
  TiroController tiroController = TiroController();

  // Laco principal do jogo
  while(controller.get_rodando()) {
    controller.polling();
    asteroidcontroller.update();
    tiroController.update(model.getTiro());
    controller.update();
    view.renderizar();
    
  }

  view.destruir();
  
  return 0;
}