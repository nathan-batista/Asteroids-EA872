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
#include <boost/asio.hpp>

using namespace std;
using nlohmann::json;
using boost::asio::ip::udp;

int main() { 
  //Tiro tiro = Tiro(-10,-10,0,0,0);
  vector<Tiro> tiros;
  vector<Asteroid> asteroids;
  json j;
  char v[10000];

  boost::asio::io_service io_service;

  udp::endpoint local_endpoint(udp::v4(), 0);
  udp::socket meu_socket(io_service, local_endpoint);
  // Encontrando IP remoto
  boost::asio::ip::address ip_remoto = boost::asio::ip::address::from_string("127.0.0.1");

  udp::endpoint remote_endpoint(ip_remoto, 9001);
  
  Nave nave = Nave(1, 1, 0, 320, 120, 30, 0.1, tiros, 1);
  Asteroid asteroid = Asteroid(0, 0, 10, 10, 0.1);
  //View view = View(nave, asteroids);
  AsteroidController asteroidcontroller = AsteroidController(asteroids);
  NaveController naveController = NaveController(nave, asteroids);
  TiroController tiroController = TiroController();

  // Laco principal do jogo
  while(naveController.get_rodando()) {
    naveController.polling();
    asteroidcontroller.update();
    tiroController.update(nave.getTiro());
    naveController.update();
    j["asteroides"] = asteroids;
    j["tiros"] = tiros;
    j["nave"] = nave;
    meu_socket.send_to(boost::asio::buffer(j.dump()), remote_endpoint);
    meu_socket.receive_from(boost::asio::buffer(v,10000), // Local do buffer
                      remote_endpoint);
    //view.renderizar();
    
  }

  /*
  ofstream f;
  f.open("teste.json");
  f << j;
  f.close();
  */
 
  //view.destruir();
  
  return 0;
}