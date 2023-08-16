#include "tcpServer.hpp"

void loop()
{
	std::string root = "www/";
	struct sockaddr_in their_addr;
	socklen_t their_addr_size = sizeof their_addr;

	int fd = getSocketListener(NULL, "8080");

	while (1)
	{
		int their_fd = accept(fd, (struct sockaddr *)&their_addr, &their_addr_size);

		if (their_fd < 0)
			perror("oh no blyat");

		char recvbuf[4096];

		if (recv(their_fd, recvbuf, 4095, 0) < 0)
			perror ("recv");

		recvbuf[4095] = 0;

        std::cout << recvbuf << "\n";

		std::stringstream str;

		std::cout << getUrl(recvbuf) << "\n";

		std::ifstream buf((root + getUrl(recvbuf) + "/index.html").c_str());

		if (buf.fail())
			perror("failed to open file");

		str << buf.rdbuf();

		std::string data(str.str());

		data = "HTTP/1.1 200 OK\nContent-Type:text/html\nContent Length:" + my_to_string(data.size()) + "\n\n" + data;

		sendAll(their_fd, data.c_str(), data.size());
		close(their_fd);
	}
}
