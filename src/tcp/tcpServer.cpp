#include "tcpServer.hpp"

void init_sets(const int& sockfd, fd_set& readfd, fd_set& writefd)
{
	FD_ZERO(&readfd);
	FD_SET(sockfd, &readfd);

	FD_ZERO(&writefd);
	FD_SET(sockfd, &writefd);
}

void loop()
{
	std::string root = "www/";

	int fd = getSocketListener(NULL, "8080");

	fd_set readfd;
	fd_set writefd;

	while (1)
	{
		init_sets(fd, readfd, writefd);

		std::cout << "WAITING...\n";

		int ready_count = select(fd + 1, &readfd, &writefd, NULL, NULL);

		std::cout << "SELECT RETURNED...\n";

		if (ready_count < 0)
		{
			perror("select");
			throw ("select error");
		}
		if (FD_ISSET(fd, &readfd))
		{
			std::cout << "I'm here nahooi\n";
			sendFile(fd);
		}
	}
}
