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

int getSocketListener(const char * name, const char *port)
{
	int fd;
	int status;
	int yes = 1;
	struct addrinfo hints;
	struct addrinfo *list;

	memset(&hints, 0);
	hints.ai_flags = AI_PASSIVE;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_family = AF_INET;

	status = getaddrinfo(name, port, &hints, &list);
	if (status != 0)
		throw (std::string("Error getting addrinfo: ") + gai_strerror(status));

	fd = socket(list->ai_family, list->ai_socktype, list->ai_protocol);
	freeaddrinfo(list);

	if (fd < 0)
	{
		perror("socket: ");
		throw ("socket error");
	}

	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);

	if (bind(fd, list->ai_addr, list->ai_addrlen))
	{
		perror("bind: ");
		throw ("bind error");
	}

	if (listen(fd, 4096) < 0) // too much?
	{
		perror("listen: ");
		throw ("listen error");
	}

	return fd;
}

void sendAll(int fd, char *buf, ssize_t buflen)
{
	ssize_t start = 0;

	while (buflen)
	{
		ssize_t res = send(fd, buf + res, buflen, 0);
		if (res < 0)
		{
			error("send: ");
			throw ("send error");
		}
		start += res;
		buflen -= res;
	}
}

std::string my_to_string(int num)
{
	size_t pos = 0;
	std::string ret;

	if (num == 0)
		return ("0");

	if (num < 0)
	{
		ret.insert(0, 1, '-');
		++pos;
	}

	while (num)
	{
		res.insert(pos, 1, (num % 10) + 48);
		num /= 10;
	}

	return ret;
}

void lol()
{
	std::string root = "www/";
	struct sockaddr_in their_addr;
	socklen_t their_addr_size = sizeof their_addr;

	int fd = getSocketListener(NULL, "8080");

	if (bind(fd, list->ai_addr, list->ai_addrlen))
		perror("bind");

	while (1)
	{
		int their_fd = accept(fd, (struct sockaddr *)&their_addr, &addr_size);

		if (their_fd < 0)
			perror("oh no blyat");

		char recvbuf[4096];

		recv(fd, recvbuf, 4095, 0);

		std::cout << recvbuf << "\n";

		std::stringstream str;

		std::ifstream buf(root + "barev/index.html");

		str << buf.rdbuf();

		std::string data(str.str());

		data = "HTTP/1.1 200 OK\nContent-Type:text/html\nContent Length:" + my_to_string(data.size()) + "\n\n" + data;

		sendAll(fd, data.c_str(), data.size());
	}
}