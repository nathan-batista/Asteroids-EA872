#include "View.h"
#include "Controller.h"
#include "Model.h"
#include "Asteroid.h"
#include "AsteroidController.h"

int main() { 
  Model model = Model(1, 1, 0, 320, 120, 30, 0.1);
  Asteroid asteroid = Asteroid(0, 0, 10, 10, 0.1);
  View view = View(model, asteroid);
  AsteroidController asteroidcontroller = AsteroidController(asteroid);
  Controller controller = Controller(model);


  // Laco principal do jogo
  while(controller.get_rodando()) {
    controller.polling();
    asteroidcontroller.update();
    view.renderizar();
  }

  view.destruir();
  
  return 0;
}