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

std::string openFile(const char recvbuf[MAX_BUF + 1], const std::string& root)
{
	std::stringstream str;

	std::ifstream buf((root + getUrl(recvbuf) + "/index.html").c_str());

	if (buf.fail())
		perror("failed to open file");

	str << buf.rdbuf();

	std::string data(str.str());

	return "HTTP/1.1 200 OK\nContent-Type:text/html\nContent Length:" + my_to_string(data.size()) + "\n\n" + data;
}

void acceptSocket(int sockfd, std::vector<recv_t>& fds)
{
	recv_t rc;

	struct sockaddr_in their_addr;
	socklen_t their_addr_size = sizeof their_addr;

	int their_fd = accept(sockfd, (struct sockaddr *)&their_addr, &their_addr_size);

	if (their_fd < 0)
		perror("oh no i had to change the error message");

	rc.sockfd = their_fd;

	ssize_t received;

	if ((received = recv(their_fd, rc.buf, MAX_BUF, 0)) < 0)
	{
		perror ("recv");
		throw std::runtime_error("recv");
	}

	rc.buf[received] = 0;
	rc.sendbuf = openFile(rc.buf, "www/");

	fds.push_back(rc);
}

void loop()
{
	std::string root = "www/";

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
				sendFile(writefds[i], writefds);
			}
		}
		recv_t temp;

		temp.finished = true;

		std::vector<recv_t>::iterator start = std::remove(writefds.begin(), writefds.end(), temp);

		for (std::vector<recv_t>::iterator it = start; it != writefds.end(); ++it)
			close(it->sockfd);

		writefds.erase(start, writefds.end());
	}
}
