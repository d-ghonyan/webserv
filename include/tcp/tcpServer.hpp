#ifndef TCP_SERVER_HPP
# define TCP_SERVER_HPP

#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>

#include <sstream>
#include <fstream>
#include <cstring>
#include <iostream>

std::string my_to_string(int num);
std::string getUrl(const char *buf);

void sendFile(int sockfd);
void sendAll(int fd, const char *buf, ssize_t buflen);

int getSocketListener(const char * name, const char *port);

#endif // TCP_SERVER_HPP