#include "tcpServer.hpp"

void init_sets(const int& sockfd, const std::vector<recv_t>& writefds, fd_set& readfd, fd_set& writefd)
{
	FD_ZERO(&readfd);
	FD_ZERO(&writefd);

	FD_SET(sockfd, &readfd);
	for (size_t i = 0; i < writefds.size(); ++i)
	{
		FD_SET(writefds[i].sockfd, &writefd);
	}
}

void loop()
{
	int fd = getSocketListener(NULL, "8080");

	fd_set readfd;
	fd_set writefd;

	std::vector<recv_t> writefds;

	while (1)
	{
		int max_fd = writefds.size() == 0 ? fd : std::max(std::max_element(writefds.begin(), writefds.end())->sockfd, fd);

		init_sets(fd, writefds, readfd, writefd);

		int ready_count = select(max_fd + 1, &readfd, &writefd, NULL, NULL);

		std::cout << "SELECT RETURNED...\n";

		if (ready_count < 0)
		{
			perror("select");
			throw std::runtime_error("select error");
		}

		if (FD_ISSET(fd, &readfd))
		{
			acceptSocket(fd, writefds);
		}
		for (size_t i = 0; i < writefds.size(); ++i)
		{
			if (FD_ISSET(writefds[i].sockfd, &writefd))
			{
				// std::cout << "sending file \n";
				sendFile(writefds[i]);
				// std::cout << "file sent\n";
			}
		}
		recv_t temp;

		temp.finished = true;

		std::vector<recv_t>::iterator start = std::remove(writefds.begin(), writefds.end(), temp);

		for (std::vector<recv_t>::iterator it = start; it != writefds.end(); ++it)
			close(it->sockfd);

		writefds.erase(start, writefds.end());

		for (size_t i = 0; i < writefds.size(); ++i)
		{
			std::cout << writefds[i].sockfd << " hello\n";
		}
	}
}
