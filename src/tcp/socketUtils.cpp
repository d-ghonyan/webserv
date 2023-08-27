#include "tcpServer.hpp"

int getSocketListener(const char *name, const char *port)
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

	if (status != 0 || list == NULL)
		throw std::runtime_error(std::string("Error getting addrinfo: ") + gai_strerror(status));

	fd = socket(list->ai_family, list->ai_socktype, list->ai_protocol);

	if (fd < 0)
	{
		perror("socket");
		throw std::runtime_error("socket error");
	}

	fcntl(fd, F_SETFL, O_NONBLOCK);
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);

	if (bind(fd, list->ai_addr, list->ai_addrlen))
	{
		perror("bind");
		throw std::runtime_error("bind error");
	}

	if (listen(fd, 10) < 0) // too little?
	{
		perror("listen");
		throw std::runtime_error("listen error");
	}

	freeaddrinfo(list);

	return fd;
}

void sendFile(recv_t& rc)
{
	ssize_t ret = send(rc.sockfd, rc.sendbuf.c_str() + rc.offset, rc.sendbuf.size() - rc.offset, 0);

	if (ret < 0)
	{
		perror("send");
		throw std::runtime_error("send");
	}

	rc.offset += ret;
	if (static_cast<size_t>(ret) == rc.sendbuf.size()) // no more goddamn data to send
		rc.finished = true;
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
			throw std::runtime_error("send error");
		}

		start += res;

		if (buflen - res < 0)
			res = buflen;

		buflen -= res;
	}
}
