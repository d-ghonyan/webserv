#include "tcpServer.hpp"

void init_sets(const int& sockfd, const std::vector<recv_t>& writefds, fd_set& readfd, fd_set& writefd)
{
	FD_ZERO(&readfd);
	FD_ZERO(&writefd);

	FD_SET(sockfd, &readfd);
	// for (size_t i = 0; i < writefds.size(); ++i)
	// {
	// 	FD_SET(writefds[i].sockfd, &writefd);
	// }
}

void loop()
{
	int fd = getSocketListener(NULL, "8080");

	fd_set readfd;
	fd_set writefd;

	std::vector<recv_t> writefds;

	fd_set master;

	FD_ZERO(&master);
	FD_SET(fd, &master);

	while (1)
	{
		struct sockaddr_in accepted;
		socklen_t size = sizeof accepted;

		int new_fd = accept(fd, (struct sockaddr *)&accepted, &size);

		char buf[1000];

		ssize_t rec = recv(new_fd, buf, 999, 0);

		if (rec < 0)
		{
			// perror("recv");
			close(new_fd);
			continue ;
		}

		buf[rec] = 0;

		std::cout << buf << "\n";

		send(new_fd, "HTTP/1.1 200 OK\nContent-Type:text/html\nContent Length:18\n\n<h1>Not found</h1>", strlen("HTTP/1.1 200 OK\nContent-Type:text/html\nContent Length:18\n\n<h1>Not found</h1>"), 0);

		close(new_fd);
		// int max_fd = writefds.size() == 0 ? fd : std::max(std::max_element(writefds.begin(), writefds.end())->sockfd, fd);

		// readfd = master;
		// // init_sets(fd, writefds, readfd, writefd);

		// int ready_count = select(max_fd + 1, &readfd, &writefd, NULL, NULL);

		// std::cout << "SELECT RETURNED...\n";

		// if (ready_count < 0)
		// {
		// 	perror("select");
		// 	throw std::runtime_error("select error");
		// }

		// if (ready_count == 0)
		// 	continue ;

		// if (FD_ISSET(fd, &readfd))
		// {
		// 	std::cout << "someone is talking to me\n";
		// 	acceptSocket(fd, writefds);
		// }

		// for (size_t i = 0; i < writefds.size(); ++i)
		// {
		// 	if (FD_ISSET(writefds[i].sockfd, &writefd))
		// 	{
		// 		std::cout << "sending file \n";
		// 		sendFile(writefds[i]);
		// 		std::cout << "file sent\n";
		// 	}
		// }
		// recv_t temp;

		// temp.finished = true;

		// std::vector<recv_t>::iterator start = std::remove(writefds.begin(), writefds.end(), temp);

		// for (std::vector<recv_t>::iterator it = start; it != writefds.end(); ++it)
		// {
		// 	std::cout << "closing socket naxuy\n";
		// 	close(it->sockfd);
		// }

		// writefds.erase(start, writefds.end());

		// for (size_t i = 0; i < writefds.size(); ++i)
		// {
		// 	std::cout << writefds[i].sockfd << " hello\n";
		// }
	}
}
