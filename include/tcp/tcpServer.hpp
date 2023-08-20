#ifndef TCP_SERVER_HPP
# define TCP_SERVER_HPP

# include <netdb.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <dirent.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <sys/select.h>

# include <map>
# include <vector>
# include <sstream>
# include <fstream>
# include <cstring>
# include <iostream>
# include <algorithm>

# define MAX_BUF 4096

typedef struct recv
{
	int sockfd;
	bool finished;
	char buf[MAX_BUF];
	ssize_t offset;
	std::string sendbuf;

	bool operator>(const struct recv& lhs) const { return sockfd > lhs.sockfd; }
	bool operator<(const struct recv& lhs) const { return sockfd < lhs.sockfd; }
	bool operator==(const struct recv& lhs) const { return finished == lhs.finished; }

	recv() : finished(false), offset(0) { }
} recv_t;

std::string my_to_string(int num);
std::string getUrl(const char *buf);
std::string openFile(const char recvbuf[MAX_BUF + 1], const std::string& root);
std::string listDirectiory(const char recvbuf[MAX_BUF + 1]);

int getSocketListener(const char * name, const char *port);
void sendFile(recv_t& rc);
void sendAll(int fd, const char *buf, ssize_t buflen);
void acceptSocket(int sockfd, std::vector<recv_t>& fds);

#endif // TCP_SERVER_HPP