#include "tcpServer.hpp"

void init_sets(const std::vector<socket_t>& listeners, fd_set& master, fd_set& wrmaster)
{
	FD_ZERO(&master);
	FD_ZERO(&wrmaster);

	for (size_t i = 0; i < listeners.size(); ++i)
	{
		FD_SET(listeners[i].fd, &master);
	}
}

void getSockets(const std::vector<Server>& servers, std::vector<socket_t>& listeners)
{
	for (size_t i = 0; i < servers.size(); ++i)
	{
		Server::listen_type listens = servers[i].getListens();

		for (size_t j = 0; j < listens.size(); ++j)
		{
			if (std::find(listeners.begin(), listeners.end(), listens[j]) == listeners.end())
			{
				std::string host = listens[j].host;
				std::string port = listens[j].port;

				listeners.push_back(socket_t(getSocketListener(host == "" ? NULL : host.c_str(), port.c_str()), host, port));
			}
		}
	}
}

void parseRequest(const std::string& req)
{

}

void loop(Config& conf)
{
	int yes = 1;

	fd_set readfd;
	fd_set writefd;

	std::vector<socket_t> listeners;
	std::map<int, recv_t> writefds;

	getSockets(conf.getServers(), listeners);

	int fd = listeners.back().fd;	

	fd_set master;
	fd_set wrmaster;

	init_sets(listeners, master, wrmaster);

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
				std::vector<socket_t>::iterator it = std::find(listeners.begin(), listeners.end(), i);
		
				if (it != listeners.end())
				{
					std::cout << "i == fd\n";
					int new_fd = accept(it->fd, (struct sockaddr *)&accepted, &size);

					FD_SET(new_fd, &master);

					if (new_fd > max_fd)
						max_fd = new_fd;

					writefds[new_fd].listener_fd = it->fd;
				}
				else
				{
					std::cout << "i != fd\n";

					ssize_t rec = recv(i, writefds[i].buf, MAX_BUF, 0);

					if (rec <= 0)
					{
						if (rec < 0)
							perror("recv");
						std::cout << "recv <=0\n";

						close(i);
						FD_CLR(i, &master);
						FD_CLR(i, &wrmaster);
						writefds.erase(i);
					}
					else
					{
						writefds[i].buf[rec] = 0;

						std::cout << writefds[i].buf << "\n";

						FD_SET(i, &wrmaster);
					}
				}
			}
			if (FD_ISSET(i, &writefd))
			{
				std::vector<socket_t>::iterator listener = std::find(listeners.begin(), listeners.end(), writefds[i].listener_fd);

				std::string url = getUrl(writefds[i].buf);

				std::string file = openFile(writefds[i].buf, conf.getLocationData(listener->host, listener->port, "", url));

				if(send(i, file.c_str(), file.size(), 0) < 0)
					perror("send");

				close(i);
				FD_CLR(i, &master);
				FD_CLR(i, &wrmaster);
				writefds.erase(i);
			}

		}
	}
}
