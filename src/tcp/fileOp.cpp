#include "tcpServer.hpp"

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

std::string listDirectiory(const char recvbuf[MAX_BUF + 1])
{
	DIR *dir;

	std::string ret = "<ul>";
	std::string name = "www/" + getUrl(recvbuf);

	if ((dir = opendir(name.c_str())) == NULL)
	{
		perror("oh no opendir");
		return "HTTP/1.1 200 OK\nContent-Type:text/html\nContent Length:18\n\n<h1>Not found</h1>";
	}

	struct dirent *entry = readdir(dir);

	while (entry)
	{
		std::cout << entry->d_name << "\n";
		ret += "<li>";//<a href='http://" + host + ":" + port + url + filename;
		ret += entry->d_name;
		ret += "</li>";//<a href='";
		entry = readdir(dir);
	}

	ret += "</ul>";

	return "HTTP/1.1 200 OK\nContent-Type:text/html\nContent Length:" + my_to_string(ret.size()) + "\n\n" + ret;
}
