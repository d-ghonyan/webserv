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
	fd_set wrmaster;

	FD_ZERO(&master);
	FD_ZERO(&wrmaster);
	FD_ZERO(&readfd);
	FD_ZERO(&writefd);

	FD_SET(fd, &master);
	FD_SET(fd, &readfd);

	int max_fd = fd;

	while (1)
	{
		readfd = master;
		writefd = wrmaster;

		struct sockaddr_in accepted;
		socklen_t size = sizeof accepted;

		int sel = select(max_fd + 1, &readfd, &writefd, NULL, NULL);

		if (sel == 0)
			continue ;
		if (sel < 0)
		{
			perror("select");
			continue ;  
		}

		for (int i = 3; i <= max_fd; ++i)
		{

			if (FD_ISSET(i, &readfd))
			{
				if (i == fd)
				{
					int new_fd = accept(fd, (struct sockaddr *)&accepted, &size);

					FD_SET(new_fd, &master);

					if (new_fd > max_fd)
						max_fd = new_fd;
				}
				else
				{
					char buf[MAX_BUF + 1];

					ssize_t rec = recv(i, buf, MAX_BUF, 0);

					if (rec <= 0)
					{
						// perror("recv")
						FD_CLR(i, &master);
						break ;
					}

					buf[rec] = 0;

					std::cout << buf << "\n";

					send(i, listDirectiory(buf).c_str(), listDirectiory(buf).size(), 0);

					close(i);

					FD_CLR(i, &master);
				}
			}

		}
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
		// 	close(it->sockfd);
		// }

		// writefds.erase(start, writefds.end());

		// for (size_t i = 0; i < writefds.size(); ++i)
		// {
		// 	std::cout << writefds[i].sockfd << " hello\n";
		// }
	}
}
