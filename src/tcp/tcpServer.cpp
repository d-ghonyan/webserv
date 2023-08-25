#include "tcpServer.hpp"

void init_sets(const int& sockfd, fd_set& master, fd_set& wrmaster)
{
	FD_ZERO(&master);
	FD_ZERO(&wrmaster);

	FD_SET(sockfd, &master);
}

void loop()
{
	int yes = 1;
	int fd = getSocketListener(NULL, "8080");

	fd_set readfd;
	fd_set writefd;

	std::map<int, std::string> writefds;

	fd_set master;
	fd_set wrmaster;

	init_sets(fd, master, wrmaster);

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
					std::cout << "i == fd\n";
					int new_fd = accept(fd, (struct sockaddr *)&accepted, &size);

					setsockopt(new_fd, SOL_SOCKET, SO_KEEPALIVE, &yes, sizeof yes);

					FD_SET(new_fd, &master);

					if (new_fd > max_fd)
						max_fd = new_fd;
				}
				else
				{
					std::cout << "i != fd\n";
					char buf[MAX_BUF + 1];

					ssize_t rec = recv(i, buf, MAX_BUF, 0);

					if (rec <= 0)
					{
						std::cout << "recv <=0\n";
						close(i);
						FD_CLR(i, &master);
						FD_CLR(i, &wrmaster);
						writefds.erase(i);
					}
					else
					{
						buf[rec] = 0;

						std::cout << buf << "\n";
						writefds[i] = buf;
						FD_SET(i, &wrmaster);
					}
				}
			}
			if (FD_ISSET(i, &writefd))
			{
				if(send(i, listDirectiory(writefds[i].c_str()).c_str(), listDirectiory(writefds[i].c_str()).size(), 0) < 0)
					perror("send");
				FD_CLR(i, &wrmaster);
			}

		}
	}
}
