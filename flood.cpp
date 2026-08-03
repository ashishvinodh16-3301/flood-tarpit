#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <thread>
#include <chrono>
#include <cerrno>
#define DEFAULT_PORT 9999
#define BUFFER_SIZE 1024

//each attacjer connection
void flood_client(int client_socket, std::string client_ip) {std::cout <<"ATTACKER DETECTED....."<<"\n connection established" << client_ip << std::endl;
	//payload
	char junk_data[BUFFER_SIZE];
	std::memset(junk_data, 'A', BUFFER_SIZE - 1);
	junk_data[BUFFER_SIZE -1] = '\n';
//loop
        while (true) {
	    ssize_t byte_sent = send(client_socket, junk_data, BUFFER_SIZE, 0);
	   if (byte_sent <=0) {
	       std::cout << "attacker disconnected...." << client_ip << std::endl;
		break;
	       
	}
	std::cout << "flooding..." << client_ip << "with" << BUFFER_SIZE << "bytes." << std::endl;
//delay
       std::this_thread::sleep_for(std::chrono::milliseconds(100));
       }
       close(client_socket);
}

int main() {
std::cout << R"(
 ███████╗██╗      ██████╗  ██████╗ ██████╗ 
 ██╔════╝██║     ██╔═══██╗██╔═══██╗██╔══██╗
 █████╗  ██║     ██║   ██║██║   ██║██║  ██║
 ██╔══╝  ██║     ██║   ██║██║   ██║██║  ██║
 ██║     ███████╗╚██████╔╝╚██████╔╝██████╔╝
 ╚═╝     ╚══════╝ ╚═════╝  ╚═════╝ ╚═════╝ 
)" << std::endl;
	int server_fd, client_socket;
	struct sockaddr_in address;
	int opt = 1;
	socklen_t addrlen = sizeof(address);
int PORT;
std::cout << "Enter port to listen on (default " << DEFAULT_PORT << "): ";
std::string port_input;
std::getline(std::cin, port_input);

if (port_input.empty()) {
    PORT = DEFAULT_PORT;
} else {
    try {
        PORT = std::stoi(port_input);
        if (PORT < 1 || PORT > 65535) {
            std::cerr << "Invalid port range. Using default " << DEFAULT_PORT << std::endl;
            PORT = DEFAULT_PORT;
        }
    } catch (...) {
        std::cerr << "Invalid input. Using default " << DEFAULT_PORT << std::endl;
        PORT = DEFAULT_PORT;
    }
}

	//Tcp server socket
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
           std::cerr <<"SOCKET CREATION FAILED...!" << std::endl;
	  return 1;
	}

//rebinding
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
	    std::cerr << "SETSOCKOPT FAILED.." << std::endl;
	  return 1;
	}
//HONEYPOT
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);
  if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
  std::cerr << "BIND FAILED..." << PORT << "already in use?" << std::endl;
 return 1;
 }
if (listen(server_fd, 10) < 0) {
 std::cerr << "LISTEN FAILED..." << std::endl;
 return 1;
 } 
 std::cout << "Flooder active on port" << PORT << "...." << std::endl;
 std::cout <<"waiting for an attack" << std::endl;
//main loop
  while (true) {
     if ((client_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) < 0) {
     std::cerr << "❌ Accept failed: " << strerror(errno) << std::endl;
     continue;
}

//Binary ip to readable
std::string client_ip = inet_ntoa(address.sin_addr);
std::thread client_thread(flood_client, client_socket, client_ip);
client_thread.detach();
}

close(server_fd);
return 0;
}
