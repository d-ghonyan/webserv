#include <cstring>
#include <netdb.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include <string>

void lol()
{
	int status;
	struct addrinfo hints;
	struct addrinfo *list;

	struct sockaddr_storage their_addr;
	socklen_t addr_size = sizeof their_addr;

	memset(&hints, 0, sizeof hints);

	hints.ai_family = AF_INET;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_socktype = SOCK_STREAM;

	if ((status = getaddrinfo(NULL, "8080", &hints, &list)) < 0)
		std::cout << gai_strerror(status) << "\n";

	int fd = socket(list->ai_family, list->ai_socktype, list->ai_protocol);

	if (fd < 0)
		perror("BAREV");

	if (bind(fd, list->ai_addr, list->ai_addrlen))
		perror("bind");

	listen(fd, 10);

	int their_fd = accept(fd, (struct sockaddr *)&their_addr, &addr_size);
	if (their_fd < 0)
		perror("oh no blyat");

	std::stringstream str;

	std::ifstream buf("www/barev/index.html");

	str << buf.rdbuf();

	std::string data(str.str());

	data = "HTTP/1.1 200 OK\nContent-Type:text/html\nContent Length: 120\n\n" + data;

	if (send(their_fd, data.c_str(), data.size(), 0) < 0)
		perror("suka");
}