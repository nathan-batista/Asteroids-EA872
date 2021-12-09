#include "NaveController.h"
#include "Nave.h"
#include "Asteroid.h"
#include "AsteroidController.h"
#include "TiroController.h"
#include "Tiro.h"
#include "ModelFinal.h"
#include "ControllerGeral.h"
#include "Keyboard.h"
#include "View.h"
#include <vector>
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <boost/asio.hpp>
#include <chrono>
#include <thread>
        
using namespace std;
using nlohmann::json;
using boost::asio::ip::udp;

 boost::asio::io_service my_io_service; // Conecta com o SO
 udp::endpoint local_endpoint(udp::v4(), 9001); // endpoint: contem
 udp::socket my_socket(my_io_service, local_endpoint); // endpoint
 udp::endpoint remote_endpoint; // vai conter informacoes de quem conectar
 
    void sendJSON(vector<udp::endpoint> listaDeClientes, vector<Nave> listaNave,vector<Asteroid> ast, json j){
	    int num_players = listaDeClientes.size();
		j["naves"] = listaNave;
		j["asteroids"] = ast;
	    for(int i=0; i<num_players; i++){
	        my_socket.send_to(boost::asio::buffer(j.dump()), listaDeClientes[i]);
	    }
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }


	void receiveInput(vector<udp::endpoint> listaDeClientes, Keyboard *teclado){
	    json j;
	    char dados[50000];
	    my_socket.receive_from(boost::asio::buffer(dados,50000), remote_endpoint);
	    j = json::parse(dados);
		try{
		int tecladoPressionado[4];
		j["teclas"].get_to(tecladoPressionado); 
		//teclado->teclas = tecladoPressionado;
		j["atirou"].get_to(teclado->atirou);
		j["saiu"].get_to(teclado->saiu);
		j["id"].get_to(teclado->id);
		teclado->teclas[0] = tecladoPressionado[0];
		teclado->teclas[1] = tecladoPressionado[1];
		teclado->teclas[2] = tecladoPressionado[2];
		teclado->teclas[3] = tecladoPressionado[3];
		std::cout << "Teclas Recebidas : " << to_string(tecladoPressionado[0]) + " " << to_string(tecladoPressionado[1]) + " " << to_string(tecladoPressionado[2]) + " " << to_string(tecladoPressionado[3]) + " " <<std::endl;
		}
		catch(...) { std::cout<< "Cagou aqui" << std::endl;}
		//*teclado->atirou = j["atirou"];
		//*teclado->saiu = j["saiu"];
	}
	
	int main(){
	    char v[10000];
	    char resp;
	    json j;
	    vector<Nave> listaDeNaves;
	
	    
	    std::cout << "Server Conectado" << std::endl;
	    vector<udp::endpoint> listaDeClientes;
	    std::cout << "Aguardando conexoes de jogadores" << std::endl;
	    resp = '0';

	    while(resp != '1'){
	        my_socket.receive_from(boost::asio::buffer(v,10000), // Local do buffer
	                      remote_endpoint);
	        if(find(listaDeClientes.begin(),listaDeClientes.end(),remote_endpoint) == listaDeClientes.end()){
	            listaDeClientes.push_back(remote_endpoint);
	        }
			std::cout << "Um usuário se conectou" << std::endl;
	        std::cout << "Quando todos se conectarem, digite 1, digite 0 se ira aguardar uma nova conexao" << std::endl;
	        std::cin >> resp;
	    }

		std::cout << "Jogo Iniciado" << std::endl;
	
	    // Enviando ID pro cliente
	    int num_players = listaDeClientes.size();
	
	    for(int i=0; i<num_players; i++){
	        std::string msg(to_string(i));
	        my_socket.send_to(boost::asio::buffer(msg), listaDeClientes[i]);
	    }
	  
	    for(int i = 0; i<num_players;i++){
			Tiro tiro = Tiro(-10,-10,0,0,0);
	        vector<Tiro> tiros;
			//tiros.push_back(tiro);
	        Nave nave = Nave(1, 1, 0, 320, 120, 30, 0.1,i);
	        listaDeNaves.push_back(nave);
	    }
		
		
  	vector<Asteroid> asteroids;
	  /*
  	Tiro tiro = Tiro(-10,-10,0,0,0);
  	vector<Tiro> tiros;
  	tiros.push_back(tiro);
 	Nave nave = Nave(1, 1, 0, 320, 120, 30, 0.1, 0);
 	Asteroid asteroid = Asteroid(0, 0, 10, 10, 0.1);
 	asteroids.push_back(asteroid);
 	listaDeNaves.push_back(nave); */
	Asteroid asteroid = Asteroid(0, 0, 10, 10, 0.1);
 	asteroids.push_back(asteroid);
  	ModelFinal model = ModelFinal(listaDeNaves);
  	Keyboard keyboard = Keyboard();
  	ControllerGeral controller = ControllerGeral(model, asteroids);
	AsteroidController astController = AsteroidController(asteroids);
	TiroController tirController = TiroController();
  	//View view = View(model, asteroids);
	

	j["asteroids"] = asteroids;
	j["naves"] = listaDeNaves;
		
	std::thread t1(&receiveInput,listaDeClientes,&keyboard);
	std::thread t2(&sendJSON,listaDeClientes,listaDeNaves,asteroids,j);
	while(true){
	    //sendJSON(listaDeClientes, model, j);
	    //receiveInput(listaDeClientes, keyboard);
	    controller.polling(keyboard);
		controller.update();
		astController.update();
		for(int i=0; i<listaDeNaves.size();i++){
			tirController.update(listaDeNaves[i].getTiro());
		}
	} 
			
	return 0;
}