#include "tcpServer.hpp"

// <meta http-equiv="Refresh" content="0; url='https://www.w3docs.com'" />

bool isDir(const std::string& name)
{
	DIR *dir = opendir(name.c_str());

	if (!dir)
		return false;
	
	closedir(dir);

	return true;
}

std::string openFile(const char recvbuf[MAX_BUF + 1], const Location& loc)
{
	std::stringstream str;

	std::vector<std::string> indexes = loc.getArrayOf("index");

	std::string url = getUrl(recvbuf);
	std::string root = loc.getValueOf("root");

	std::string data;

	if (isDir(root + url))
	{
		std::cout << "dir\n";
		for (size_t i = 0; i < indexes.size(); ++i)
		{
			std::ifstream buf((root + url + "/" + indexes[i]).c_str());

			if (!buf.fail())
			{
				str << buf.rdbuf();

				data = str.str();

				return "HTTP/1.1 200 OK\nContent-Type:text/html\nContent Length:" + my_to_string(data.size()) + "\n\n" + data;
			}
		}
		std::cout << "forbidden\n";

		data = "<center>403 Forbidden</center>";

		return "HTTP/1.1 403 Forbidden\nContent-Type:text/html\nContent Length:" + my_to_string(data.size()) + "\n\n" + data;
	}

	if (errno == EACCES)
	{
		data ="<center>403 Forbidden</center>";

		return "HTTP/1.1 403 Forbidden\nContent-Type:text/html\nContent Length:" + my_to_string(data.size()) + "\n\n" + data;
	}

	std::ifstream buf((root + url).c_str());

	if (buf.fail())
	{
		data = errno == EACCES ? "<center>403 Forbidden</center>" : "<center>404 Not found</center>";

		return "HTTP/1.1 404 Not found\nContent-Type:text/html\nContent Length:" + my_to_string(data.size()) + "\n\n" + data;
	}

	str << buf.rdbuf();

	data = str.str();

	return "HTTP/1.1 200 OK\nContent-Type:text/html\nContent Length:" + my_to_string(data.size()) + "\n\n" + data;
}

std::string listDirectiory(const char recvbuf[MAX_BUF + 1])
{
	DIR *dir;

	std::string ret = "<ul>";
	std::string name = "www/" + getUrl(recvbuf);

	if ((dir = opendir(name.c_str())) == NULL)
	{
		perror(("oh no opendir: " + std::string(name)).c_str());
		return "HTTP/1.1 200 OK\nContent-Type:text/html\nContent Length:18\n\n<h1>Not found</h1>";
	}

	struct dirent *entry = readdir(dir);

	while (entry)
	{
		std::cout << "./" << entry->d_name << "\n";
		ret += "<li>";//<a href='http://" + host + ":" + port + url + filename;
		ret += entry->d_name;
		ret += "</li>";//<a href='";
		entry = readdir(dir);
	}

	ret += "</ul>";

	closedir(dir);
	
	return "HTTP/1.1 200 OK\nContent-Type:text/html\nContent Length:" + my_to_string(ret.size()) + "\n\n" + ret;
}
