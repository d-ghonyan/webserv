#include "tcpServer.hpp"

std::string my_to_string(int num)
{
	size_t pos = 0;
	std::string ret;

	if (num == 0)
		return ("0");

	if (num < 0)
	{
		ret.insert(0, 1, '-');
		++pos;
	}

	while (num)
	{
		ret.insert(pos, 1, (num % 10) + 48);
		num /= 10;
	}

	return ret;
}

std::string getUrl(const char *buf)
{
	size_t i = 0;
	std::string filename;

	while (buf[i] != '/')
		++i;
	while (!std::isspace(buf[i]))
	{
		filename.push_back(buf[i]);
		++i;
	}
	return filename;
}

