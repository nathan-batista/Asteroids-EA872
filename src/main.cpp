#include "View.h"
#include "Controller.h"
#include "Model.h"
#include "Asteroid.h"
#include "AsteroidController.h"
#include "TiroController.h"
#include "Tiro.h"

int main() { 
  Tiro tiro = Tiro(0,0,0,0,0);
  Model model = Model(1, 1, 0, 320, 120, 30, 0.1,tiro);
  Asteroid asteroid = Asteroid(0, 0, 10, 10, 0.1);
  View view = View(model, asteroid,tiro);
  AsteroidController asteroidcontroller = AsteroidController(asteroid);
  Controller controller = Controller(model);
  TiroController tiroController = TiroController();


  // Laco principal do jogo
  while(controller.get_rodando()) {
    controller.polling();
    asteroidcontroller.update();
    tiroController.update(model.getTiro());
    view.renderizar();
  }

  view.destruir();
  
  return 0;
}