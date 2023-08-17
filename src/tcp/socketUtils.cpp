#include "tcpServer.hpp"

int getSocketListener(const char * name, const char *port)
{
	int fd;
	int status;
	int yes = 1;
	struct addrinfo hints;
	struct addrinfo *list;

	memset(&hints, 0, sizeof hints);
	hints.ai_flags = AI_PASSIVE;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_family = AF_INET;

	status = getaddrinfo(name, port, &hints, &list);
	if (status != 0)
		throw (std::string("Error getting addrinfo") + gai_strerror(status));

	fd = socket(list->ai_family, list->ai_socktype, list->ai_protocol);

	if (fd < 0)
	{
		perror("socket");
		throw ("socket error");
	}

	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);

	if (bind(fd, list->ai_addr, list->ai_addrlen))
	{
		perror("bind");
		throw ("bind error");
	}

	if (listen(fd, 4096) < 0) // too much?
	{
		perror("listen");
		throw ("listen error");
	}

	freeaddrinfo(list);

	return fd;
}

void sendFile(int sockfd)
{
	std::string root = "www/";

	struct sockaddr_in their_addr;
	socklen_t their_addr_size = sizeof their_addr;

	int their_fd = accept(sockfd, (struct sockaddr *)&their_addr, &their_addr_size);

	if (their_fd < 0)
		perror("oh no blyat");

	char recvbuf[4096];

	ssize_t received;

	if ((received = recv(their_fd, recvbuf, 4096, 0)) < 0)
		perror ("recv");

	recvbuf[received] = 0;

	std::cout << recvbuf << " recvbuf \n";

	std::stringstream str;

	std::cout << getUrl(recvbuf) << " geturl \n";

	std::ifstream buf((root + getUrl(recvbuf) + "/index.html").c_str());

	if (buf.fail())
		perror("failed to open file");

	str << buf.rdbuf();

	std::string data(str.str());

	data = "HTTP/1.1 200 OK\nContent-Type:text/html\nContent Length:" + my_to_string(data.size()) + "\n\n" + data;

	sendAll(their_fd, data.c_str(), data.size());
	close(their_fd);
}

void sendAll(int fd, const char *buf, ssize_t buflen)
{
	ssize_t start = 0;

	while (buflen)
	{
		ssize_t res = send(fd, buf + start, buflen, 0);

		if (res < 0)
		{
			perror("send");
			throw ("send error");
		}

		start += res;

		if (buflen - res < 0)
			res = buflen;

		buflen -= res;
	}
}
