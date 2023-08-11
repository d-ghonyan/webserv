#include "NginxConfig.hpp"

void NginxConfig::serverName(const std::vector<std::string>& tokens, size_t& server_index, size_t& location_level, size_t& i)
{
	if (location_level != 1)
		throw std::runtime_error(tokens[i] + " is not allowed here");

	size_t count = ++i;

	while (tokens[count] !=  ";" && tokens[count] != "{" && tokens[count] != "}")
	{
		servers[server_index].pushServerName(tokens[count]);
		++count;
	}

	if (count == i || tokens[count] != ";")
		throw std::runtime_error("invalid server_name directive");

	i = count;
}

void NginxConfig::listen(const std::vector<std::string>& tokens, size_t& server_index, size_t& location_level, size_t& i)
{
	if (location_level != 1)
		throw std::runtime_error(tokens[i] + " is not allowed here");

	size_t count = ++i;

	while (tokens[count] !=  ";" && tokens[count] != "{" && tokens[count] != "}")
	{
		servers[server_index].pushListen(tokens[count]);
		++count;
	}

	if (count == i || count - 1 != i || tokens[count] != ";")
		throw std::runtime_error("invalid listen directive");

	i = count;
}

void NginxConfig::errorPage(const std::vector<std::string>& tokens, size_t& server_index, size_t& location_level, size_t& i)
{
	if (location_level != 1)
		throw std::runtime_error(tokens[i] + " is not allowed here");

	size_t count = ++i;

	while (tokens[count] !=  ";" && tokens[count] != "{" && tokens[count] != "}")
	{
		servers[server_index].pushErrorPage(tokens[count]);
		++count;
	}

	if (count == i || count == i + 1 || tokens[count] != ";")
		throw std::runtime_error("invalid error_page directive");

	i = count;
}

void NginxConfig::maxBodySize(const std::vector<std::string>& tokens, size_t& server_index, size_t& location_level, size_t& i)
{
	if (location_level != 1)
		throw std::runtime_error(tokens[i] + " is not allowed here");

	size_t count = ++i;

	while (tokens[count] !=  ";" && tokens[count] != "{" && tokens[count] != "}")
	{
		servers[server_index].setMaxBodySize(tokens[count]);
		++count;
	}

	if (count == i || count - 1 != i || tokens[count] != ";")
		throw std::runtime_error("invalid client_max_body_size directive");

	i = count;
}
