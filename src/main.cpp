#include "View.h"
#include "Controller.h"
#include "Model.h"

int main() { 
  Model model = Model(1, 1, 0, 320, 30, 0.1);
  View view = View(model);
  Controller controller = Controller(model);


  // Laco principal do jogo
  while(controller.get_rodando()) {
    controller.polling();
    controller.update();
    view.renderizar();
  }

  view.destruir();
  
  return 0;
}