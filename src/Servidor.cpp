#include "NaveController.h"
#include "Nave.h"
#include "Asteroid.h"
#include "AsteroidController.h"
#include "TiroController.h"
#include "Tiro.h"
#include <vector>
#include "json.hpp"
#include <fstream>
#include <boost/asio.hpp>

using namespace std;
using nlohmann::json;
using boost::asio::ip::udp;

int main(){
    char v[10000];
    char resp;
    json j;
    vector<Nave> listaDeNaves;

    boost::asio::io_service my_io_service; // Conecta com o SO

    udp::endpoint local_endpoint(udp::v4(), 9001); // endpoint: contem
                                                // conf. da conexao (ip/port)

    udp::socket my_socket(my_io_service, // io service
                        local_endpoint); // endpoint

    udp::endpoint remote_endpoint; // vai conter informacoes de quem conectar
    
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
        std::cout << "Quando todos se conectarem, digite 1" << std::endl;
        std::cin >> resp;
    }

    // Enviando ID pro cliente
    int num_players = listaDeClientes.size();

    for(int i=0; i<num_players; i++){
        std::string msg(str(i));
        my_socket.send_to(boost::asio::buffer(msg), listaDeClientes[i]);
    }
  
    for(int i = 0; i<num_players;i++){
        vector<Tiro> tiros;
        Nave nave = Nave(1, 1, 0, 320, 120, 30, 0.1, tiros, i);
        listaDeNaves.push_back(nave);
    }

    ModelFinal model = ModelFinal(listaDeNaves);
    ControllerGeral controller = ControllerGeral(model);

    return 0;
}