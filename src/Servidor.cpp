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
        
using namespace std;
using nlohmann::json;
using boost::asio::ip::udp;

 boost::asio::io_service my_io_service; // Conecta com o SO
 udp::endpoint local_endpoint(udp::v4(), 9001); // endpoint: contem
 udp::socket my_socket(my_io_service, local_endpoint); // endpoint
 udp::endpoint remote_endpoint; // vai conter informacoes de quem conectar
 
    void sendJSON(vector<udp::endpoint> listaDeClientes, ModelFinal model, json j){
	    int num_players = listaDeClientes.size();
	
	    for(int i=0; i<num_players; i++){
	        std::string msg(j);
	        my_socket.send_to(boost::asio::buffer(msg), listaDeClientes[i]);
	    }
    }


	void receiveInput(vector<udp::endpoint> listaDeClientes, Keyboard teclado){
	    json j;
	    char dados[50000];
	    my_socket.receive_from(boost::asio::buffer(dados,50000), listaDeClientes[0]);
	    j = json::parse(dados);
	    j.at("teclado").get_to(teclado);
	
	}
	
	int main(){
	    char v[10000];
	    char resp;
	    json j;
	    vector<Nave> listaDeNaves;
	
	    
	    std::cout << "Server Conectado" << std::endl;
	    vector<udp::endpoint> listaDeClientes;
	    std::cout << "Quando todos se conectarem, digite 1" << std::endl;
	    std::cin >> resp;

	    while(resp != '1'){
	        my_socket.receive_from(boost::asio::buffer(v,10000), // Local do buffer
	                      remote_endpoint);
	        if(find(listaDeClientes.begin(),listaDeClientes.end(),remote_endpoint) == listaDeClientes.end()){
	            listaDeClientes.push_back(remote_endpoint);
	        }
			std::cout << "Um usuário se conectou" << std::endl;
	        std::cout << "Quando todos se conectarem, digite 1" << std::endl;
	        std::cin >> resp;
	    }
	
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
  	Tiro tiro = Tiro(-10,-10,0,0,0);
  	vector<Tiro> tiros;
  	tiros.push_back(tiro);
 	Nave nave = Nave(1, 1, 0, 320, 120, 30, 0.1, 0);
 	Asteroid asteroid = Asteroid(0, 0, 10, 10, 0.1);
 	asteroids.push_back(asteroid);
 	listaDeNaves.push_back(nave);
  	ModelFinal model = ModelFinal(listaDeNaves);
  	Keyboard keyboard = Keyboard();
  	ControllerGeral controller = ControllerGeral(model, asteroids);
  	View view = View(model, asteroids);
	

	j["asteroids"] = asteroids;
	j["naves"] = model.getNaves();
		

	    while(true){
	        sendJSON(listaDeClientes, model, j);
	        receiveInput(listaDeClientes, keyboard);
	        controller.polling(keyboard);
	    } 
			
		return 0;
	}