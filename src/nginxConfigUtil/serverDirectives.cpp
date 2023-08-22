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
		std::string	host("");
		std::string	port("8080");

		validationOfListen(tokens[count], host, port);
	
		servers[server_index].pushListen(host, port);

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

	size_t		count = ++i;
	std::string	error_page;

	while (tokens[count] !=  ";" && tokens[count] != "{" && tokens[count] != "}")
	{
		++count;
	}

	error_page = tokens[count - 1];
	if (containsSpecialChar(error_page))
	{
		throw std::runtime_error("invalid path in error_page directive");
	}

	if (count == i || count == i + 1 || tokens[count] != ";")
		throw std::runtime_error("invalid error_page directive");

	count = i;

	while (tokens[count] != error_page)
	{
		if (!isValidErrorCode(tokens[count]))
			throw std::runtime_error("invalid error_code in error_page directive");

		servers[server_index].pushErrorPage(my_stoi(tokens[count]), error_page);
		++count;
	}

	i = count + 1;
}

void NginxConfig::maxBodySize(const std::vector<std::string>& tokens, size_t& server_index, size_t& location_level, size_t& i)
{
	if (location_level != 1)
		throw std::runtime_error(tokens[i] + " is not allowed here");

	size_t count = ++i;

	if (std::count(tokens.begin(), tokens.end(), "client_max_body_size") != 1)
		throw std::runtime_error("duplicate client_max_body_size directive");

	while (tokens[count] !=  ";" && tokens[count] != "{" && tokens[count] != "}")
	{
		if (isInvalidValue(tokens[count]))
			throw std::runtime_error("Invalid value of client_max_body_size directive");

		servers[server_index].setMaxBodySize(getActualBodySize(tokens[count]));
		++count;
	}

	if (count == i || count - 1 != i || tokens[count] != ";")
		throw std::runtime_error("invalid client_max_body_size directive");

	i = count;
}

bool NginxConfig::isInvalidValue(const std::string& token)
{
	std::string::const_iterator start	= token.begin();
	std::string::const_iterator end		= token.end();
	std::string::const_iterator it		= std::find_if(start, end, NonDigit());

	if (it == end)
		return false;

	if (it != (end - 1))
		return true;
	
	char unit = std::tolower(token[token.size() - 1]);
	
	return unit != 'k' && unit != 'm' && unit != 'g';
}

bool NginxConfig::isValidErrorCode(const std::string& code)
{
	if (std::find_if(code.begin(), code.end(), NonDigit()) != code.end())
		return false;

	int	err_code = my_stoi(code);

	return !(err_code < 300 || err_code >= 600);
}

bool NginxConfig::containsSpecialChar(const std::string& token)
{
	const std::string specChars("*?:;\"\'<>|&%#$@+-=");

	for (std::string::const_iterator it = token.begin(); it != token.end(); ++it)
	{
		std::string::const_iterator found = std::find(specChars.begin(), specChars.end(), *it);
		if (found != specChars.end())
			return true;
	}
	return false;
}

// k: Kilobytes	-> 10^3
// m: Megabytes	-> 10^6
// g: Gigabytes	-> 10^9
size_t NginxConfig::getActualBodySize(const std::string& token)
{
	char unit = std::tolower(token[token.size() - 1]);
	std::string val = token.substr(0, token.length() - 1);

	int to_int = my_stoi(val);

	if (to_int < 0)
		throw std::runtime_error("invalid max_body_size value");

	if (!std::isdigit(unit))
	{
		size_t power = 1;

		if (unit == 'k')
			power = std::pow(10, 3);
		else if (unit == 'm')
			power = std::pow(10, 6);
		else if (unit == 'g')
			power = std::pow(10, 9);

		if ((unit == 'm' && to_int > std::pow(10, 5)) || (unit == 'g' && to_int > std::pow(10, 3)))
			throw std::runtime_error("invalid max_body_size value");

		return static_cast<size_t>(to_int) * power;
	}

	return static_cast<size_t>(to_int);
}