#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <endian.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <set>

auto main (int argc, char* argv[]) -> int {
	auto ip = argv[1];
	auto port = static_cast<uint16_t>(std::stoi(argv[2]));
	sockaddr_in addr;
	
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htobe16(port);
	inet_pton(addr.sin_family, ip, &addr.sin_addr);

	auto sock = socket(AF_INET, SOCK_STREAM, 0);
	if(bind(sock, reinterpret_cast<sockaddr*> (&addr), sizeof(addr)) == -1){
		perror("test");
		shutdown(sock, SHUT_RDWR);
		close(sock);
		return 1;
	}
	listen(sock, 0);
	auto clients = std::set<int> {};
	while(true) {
		{
			auto client = accept(sock, nullptr, nullptr);
			clients.insert(client);	
		}
		for(auto client : clients) {
			char buffer[1024];
			memset(&buffer, 0, sizeof(buffer));
			auto s = read(client, buffer, sizeof(buffer));
			if(s<=1) {
				shutdown(client, SHUT_RDWR);
				close(client);
				clients.erase(clients.find(client));
				break;
			}
			std::cout << buffer << "\n";		
		}
	}

	shutdown(sock, SHUT_RDWR);
	close(sock);

	return 0;
}
