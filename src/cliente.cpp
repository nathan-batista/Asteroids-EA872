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

      void receberJSON(vector<Nave> *navesGame,vector<Asteroid> *asteroidsJogo){
        char dados[50000];
        boost::asio::io_service io_service;
        udp::endpoint local_endpoint(udp::v4(), 0);
        udp::socket socketClient(io_service, local_endpoint);
        boost::asio::ip::address ip_remoto = boost::asio::ip::address::from_string("25.65.162.21");
        udp::endpoint remote_endpoint(ip_remoto, 9001);
        socketClient.receive_from(boost::asio::buffer(dados,50000),remote_endpoint);
        json j1 = json::parse(dados);
       // j.at("naves").get_to(naves);
       // modelo = ModelFinal(naves);
        vector<Nave> navesTotais = j1["nave"];
        *navesGame = navesTotais;
        vector<Asteroid> asteroidsTotais = j1["asteroid"];
        *asteroidsJogo = asteroidsTotais;
      }



int main() { 
  json j;
  char v[2];
  Keyboard tecladoJogador = Keyboard();
  
  vector<Nave> navesJogo;
  vector<Asteroid> asteroids;


  /*Tiro tiro = Tiro(-10,-10,0,0,0);
  vector<Tiro> tiros;
  tiros.push_back(tiro);
  */
 	Nave nave = Nave(1, 1, 0, 320, 120, 30, 0.1,0);
 	Asteroid asteroid = Asteroid(0, 0, 10, 10, 0.1);
 	asteroids.push_back(asteroid);
 	navesJogo.push_back(nave);
  ModelFinal modelJogo = ModelFinal(navesJogo);
  char dadosJogo[50000];

  boost::asio::io_service io_service;

  udp::endpoint local_endpoint(udp::v4(), 0);
  udp::socket meu_socket(io_service, local_endpoint);

  // Encontrando IP remoto
  boost::asio::ip::address ip_remoto = boost::asio::ip::address::from_string("25.65.162.21");

  udp::endpoint remote_endpoint(ip_remoto, 9001);

  std::string msg("Ola");
  meu_socket.send_to(boost::asio::buffer(msg), remote_endpoint);
  meu_socket.receive_from(boost::asio::buffer(v,2), // Local do buffer
                      remote_endpoint);
  
  std::cout << "Mensagem recebida do servidor, identificador = " << v[0] << std::endl;
  int idJogador = v[0] - '0';
  std::cout << to_string(idJogador) << endl;
  tecladoJogador.id = idJogador;

  meu_socket.receive_from(boost::asio::buffer(dadosJogo,50000), // Local do buffer
                      remote_endpoint);
  j = json::parse(dadosJogo);
  vector<Nave> naves = j["naves"];
  navesJogo = naves;


  // Laco principal do jogo
  std::thread t1(&receberJSON,&navesJogo,&asteroids);
  View view = View(modelJogo,asteroids);
  while(true) {
    tecladoJogador.atualizarEstadoTeclado();
    tecladoJogador.verificaTecla();
    tecladoJogador.atualizaEvento();
    j["teclas"] = tecladoJogador.teclas;
    j["saiu"] = tecladoJogador.saiu;
    j["atirou"] = tecladoJogador.atirou;
    view.renderizar();
    meu_socket.send_to(boost::asio::buffer(j["teclado"].dump()),remote_endpoint);
  }
  t1.join();


  view.destruir();
  
  return 0;
}