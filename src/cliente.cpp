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
#include "../src/json.hpp"
#include <fstream>
#include <boost/asio.hpp>
#include "Keyboard.h"
#include "ModelFinal.h"

using namespace std;
using nlohmann::json;
using boost::asio::ip::udp;
/*
class Receiver{
    public:
      Receiver(){}
      void receberJSON(json &j,ModelFinal &modelo,vector<Asteroid> &asteroidsJogo,udp::socket &socketClient,udp::endpoint &serverRemoto){
        char dados[50000];
        socketClient.receive_from(boost::asio::buffer(dados,50000),serverRemoto);
        j = nlohmann::json::parse(dados);
        vector<Nave> naves;
       // j.at("naves").get_to(naves);
       // modelo = ModelFinal(naves);
        j.at("asteroids").get_to(asteroidsJogo);
      }
};
*/


int main() { 
  json j;
  char v[3];
  Keyboard tecladoJogador = Keyboard();
  
  vector<Nave> navesJogo;
  vector<Asteroid> asteroids;


  Tiro tiro = Tiro(-10,-10,0,0,0);
  vector<Tiro> tiros;
  tiros.push_back(tiro);
 	Nave nave = Nave(1, 1, 0, 320, 120, 30, 0.1, tiros, 0);
 	Asteroid asteroid = Asteroid(0, 0, 10, 10, 0.1);
 	asteroids.push_back(asteroid);
 	navesJogo.push_back(nave);
  ModelFinal modelJogo = ModelFinal(navesJogo);
  char dadosJogo[50000];

  boost::asio::io_service io_service;

  udp::endpoint local_endpoint(udp::v4(), 0);
  udp::socket meu_socket(io_service, local_endpoint);

  // Encontrando IP remoto
  boost::asio::ip::address ip_remoto = boost::asio::ip::address::from_string("127.0.0.1");

  udp::endpoint remote_endpoint(ip_remoto, 9001);

  std::string msg("Ola");
  meu_socket.send_to(boost::asio::buffer(msg), remote_endpoint);
  meu_socket.receive_from(boost::asio::buffer(v,3), // Local do buffer
                      remote_endpoint);
  
  std::cout << "Mensagem recebida do servidor, identificador = " + v[0] << std::endl;
  int idJogador = v[0] - '0';

  meu_socket.receive_from(boost::asio::buffer(dadosJogo,50000), // Local do buffer
                      remote_endpoint);
 // j = parse(dadosJogo);
 // j.at("naves").get_to(navesJogo); 
  //modelJogo = ModelFinal(navesJogo);
 // Receiver r;
  // Laco principal do jogo
 // std::thread t1(&Receiver::receberJSON,&j,modelJogo,asteroids,&meu_socket,&remote_endpoint);
  View view = View(modelJogo,asteroids);
  while(true) {
    tecladoJogador.atualizarEstadoTeclado();
    j["teclado"] = tecladoJogador;
    meu_socket.send_to(boost::asio::buffer(j["teclado"].dump()),remote_endpoint);
    view.renderizar();
  }
 // t1.join();


  view.destruir();
  
  return 0;
}