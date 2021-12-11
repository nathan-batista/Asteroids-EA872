#include "View.h"
#include "NaveController.h"
#include "Nave.h"
#include "Asteroid.h"
#include "AsteroidController.h"
#include "TiroController.h"
#include "Tiro.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "json.hpp"
#include "../src/json.hpp"
#include <fstream>
#include <boost/asio.hpp>
#include "Keyboard.h"
#include "ModelFinal.h"
#include <thread>
#include <chrono>

using namespace std;
using nlohmann::json;
using boost::asio::ip::udp;

boost::asio::io_service io_service;
udp::endpoint local_endpoint(udp::v4(), 0);
udp::socket meu_socket(io_service, local_endpoint);
boost::asio::ip::address ip_remoto = boost::asio::ip::address::from_string("25.69.91.133");
udp::endpoint remote_endpoint(ip_remoto, 9001);

      void receberJSON(vector<Nave> *navesGame,vector<Asteroid> *asteroidsJogo){
        // boost::asio::io_service io_service;
        // udp::endpoint local_endpoint(udp::v4(), 0);
        // udp::socket socketClient(io_service, local_endpoint);
        // boost::asio::ip::address ip_remoto = boost::asio::ip::address::from_string("25.65.162.21");
        // udp::endpoint remote_endpoint(ip_remoto, 9001);
        json j1;
        while (true){
          char dados[200000];
          dados[0] = '\0';
         // std::string message;
          //cout << "Tentando Receber JSON" << endl;
          meu_socket.receive_from(boost::asio::buffer(dados,200000),remote_endpoint);
          j1.clear();
          j1 = json::parse(dados);
          vector<Nave> navesTotais = j1["naves"];
          //json j1 = json::parse(message);
          // vector<Nave> navesTotais(8);
          // j1.at("naves").get_to(navesTotais);
          *navesGame = navesTotais;
          //int dado = j1["batata"];
          //cout << "Recebi o dado : " << to_string(dado) << endl;
          // vector<Asteroid> asteroidsTotais(20);
          // j1.at("asteroids").get_to(asteroidsTotais);
          //j1.at("asteroids").get_to(asteroidsTotais);
          vector<Asteroid> asteroidsTotais = j1["asteroids"];
          *asteroidsJogo = asteroidsTotais;
          //cout << "Recebendo vetor de asteroids de tamanho " << to_string(asteroidsTotais.size()) << endl;
        }
      }

      void sendJSON(Keyboard *tecladoJogador){
        // boost::asio::io_service io_service;
        // udp::endpoint local_endpoint(udp::v4(), 0);
        // udp::socket meu_socket(io_service, local_endpoint);
        // boost::asio::ip::address ip_remoto = boost::asio::ip::address::from_string("25.65.162.21");
        // udp::endpoint remote_endpoint(ip_remoto, 9001);
        while(true){
          json j2;
          j2["teclas"] = tecladoJogador->teclas;
          j2["saiu"] = tecladoJogador->saiu;
          j2["atirou"] = tecladoJogador->atirou;
          j2["id"] = tecladoJogador->id;
          meu_socket.send_to(boost::asio::buffer(j2.dump()), remote_endpoint);
          std::this_thread::sleep_for(std::chrono::milliseconds(20));
          //tecladoJogador->atirou = 0;
          //int teclas[4] = {0,0,0,0}; 
          /*tecladoJogador->teclas[0] = 0;
          tecladoJogador->teclas[1] = 0;
          tecladoJogador->teclas[2] = 0;
          tecladoJogador->teclas[3] = 0;*/
          
        }
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

  // boost::asio::io_service io_service;

  // udp::endpoint local_endpoint(udp::v4(), 0);
  // udp::socket meu_socket(io_service, local_endpoint);

  // Encontrando IP remoto
  // boost::asio::ip::address ip_remoto = boost::asio::ip::address::from_string("25.65.162.21");

  // udp::endpoint remote_endpoint(ip_remoto, 9001);

  std::string msg("Ola");
  meu_socket.send_to(boost::asio::buffer(msg), remote_endpoint);
  meu_socket.receive_from(boost::asio::buffer(v,2), // Local do buffer
                      remote_endpoint);
  
  std::cout << "Mensagem recebida do servidor, identificador = " << v[0] << std::endl;
  int idJogador = v[0] - '0';
  //std::cout << to_string(idJogador) << endl;
  tecladoJogador.id = idJogador;

  meu_socket.receive_from(boost::asio::buffer(dadosJogo,50000), // Local do buffer
                      remote_endpoint);
  j = json::parse(dadosJogo);
  vector<Nave> naves = j["naves"];
  navesJogo = naves;


  // Laco principal do jogo
  View view = View(modelJogo,asteroids);
  std::thread t1(&receberJSON,&navesJogo,&asteroids);
  std::thread t2(&sendJSON,&tecladoJogador);
  //std::thread t3(&View::renderizar,&view);
  while(true) {
    tecladoJogador.atirou = 0;
    tecladoJogador.teclas[0] = 0;
    tecladoJogador.teclas[1] = 0;
    tecladoJogador.teclas[2] = 0;
    tecladoJogador.teclas[3] = 0;
    tecladoJogador.atualizarEstadoTeclado();
    tecladoJogador.verificaTecla();
    tecladoJogador.atualizaEvento();
    view.renderizar(idJogador);
    //meu_socket.send_to(boost::asio::buffer(j.dump()),remote_endpoint);
  }
  t1.join();
  t2.join();


  view.destruir();
  
  return 0;
}