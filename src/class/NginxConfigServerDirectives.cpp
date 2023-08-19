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
		std::cout << "----> " << tokens[count] << "<-------\n";
		validationOfListen(tokens[count], host, port);

		servers[server_index].pushListen(tokens[count]);
		++count;
	}

	if (count == i || count - 1 != i || tokens[count] != ";")
		throw std::runtime_error("invalid listen directive");

	i = count;
}

void	NginxConfig::validationOfListen(std::string token, std::string& host, std::string& port) const
{
	std::string	_host;
	std::string	_port;
	if (token.find(':') != std::string::npos)
	{
		if (token.find(':') != token.rfind(':'))
			throw std::runtime_error("Invalid count of colons in listen directive");
		std::stringstream	ss(token);
		std::getline(ss, _host, ':');
		std::getline(ss, _port);
		std::cout << "HOST -> |" << _host << "|" << std::endl;
		std::cout << "PORT -> |" << _port << "|" << std::endl;
		if (!isValidHost(_host))
			throw std::runtime_error("Invalid host in listen directive");
		if (!isValidPort(_port))
			throw std::runtime_error("Invalid port in listen directive");


	}
	else
	{
		if (isValidPort(token))
		{
			
		}
		else if (is)
		// else if (hosts.find(token) == hosts.end())
		// 	throw std::runtime_error("Host " + token + " not found");

		// std::string::const_iterator start	= token.begin();
		// std::string::const_iterator end		= token.end();
		// std::string::const_iterator it		= std::find_if(start, end, NonDigit());
		
		// if (it == end)
		// {
		// 	size_t	p = 0;
		// 	std::stringstream ss(token);
		// 	ss >> p;
		// 	if (p > 65535)
		// 		throw std::runtime_error("Invalid port number | " + token);			
		// }
	}
}

bool	NginxConfig::isValidHost(const std::string& host)
{
	std::vector<std::string>	ip_vector(4, "0");
	size_t	count = 0;
	
	for (size_t i = 1; i < host.length(); i++)
	{
		
	}
	

	for (int i = 0; (i = s.find('.', i)) != std::string::npos; i++) 
	{
		count++;
    }
	


}

bool	NginxConfig::isValidPort(const std::string& _port)
{
	std::string::const_iterator start	= port.begin();
	std::string::const_iterator end		= port.end();
	std::string::const_iterator it		= std::find_if(start, end, NonDigit());
	
	if (it != end)
		return false;

	size_t	p = 0;
	std::stringstream ss(port);
	ss >> p;
	if (p > 65535)
		return false;			
	return true;
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
	if (!isValidErrorPage(error_page))
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
		std::stringstream	ss(tokens[count]);
		int err_code;
		ss >> err_code;

		servers[server_index].pushErrorPage(err_code, error_page);
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

		servers[server_index].setMaxBodySize(get_actual_value_cmbs(tokens[count]));
		++count;
	}

	if (count == i || count - 1 != i || tokens[count] != ";")
		throw std::runtime_error("invalid client_max_body_size directive");

	i = count;
}


bool	NginxConfig::isInvalidValue(const std::string& token)
{
	std::string::const_iterator start	= token.begin();
	std::string::const_iterator end		= token.end();
	std::string::const_iterator it		= std::find_if(start, end, NonDigit());
	
	if (it == end)
		return false;
	if (it != (end - 1))
		return true;
	
	char unit = std::tolower(token[token.size() - 1]);
	
	return unit != 'k' && unit != 'm' && unit != 'g' && unit != 't' && unit != 'p' && unit != 'e';
}

bool	NginxConfig::isValidErrorPage(const std::string& err_page)
{
	return (!containsSpecialChar(err_page) ? true : false);
}

bool	NginxConfig::isValidErrorCode(const std::string& code)
{
	std::string::const_iterator	it = std::find_if(code.begin(), code.end(), NonDigit());

	if (it != code.end())
	{
		std::cout << "----->" << *it << " <----------\n";
		return false;
	}

	int	err_code = 0;

	std::stringstream	ss(code);

	ss >> err_code;

	return !(err_code < 300 || err_code >= 600);
}

bool	NginxConfig::containsSpecialChar(const std::string& token)
{
	const std::string specChars("*?:;\"\'<>|&%#$@+-=");

	for (std::string::const_iterator it = token.begin(); it !=  token.end(); ++it)
	{
		std::string::const_iterator found = std::find(specChars.begin(), specChars.end(), *it);
		if (found != specChars.end())
			return (true);
	}
	return (false);
}

// k: Kilobytes	-> 10^3
// m: Megabytes	-> 10^6
// g: Gigabytes	-> 10^9
// t: Terabytes	-> 10^12
// p: Petabytes	-> 10^15
// e: Exabytes	-> 10^18
size_t	NginxConfig::get_actual_value_cmbs(const std::string&	token)
{
	size_t act_value = 1;
	char unit = std::tolower(token[token.size() - 1]);

	if (!std::isdigit(unit))
	{
		size_t	power = 1;
		std::string val = token.substr(0, token.length() - 1);

		if (unit == 'k')
			power = std::pow(10, 3);
		else if (unit == 'm')
			power = std::pow(10, 6);
		else if (unit == 'g')
			power = std::pow(10, 9);
		else if (unit == 't')
			power = std::pow(10, 12);
		else if (unit == 'p')
			power = std::pow(10, 15);
		else if (unit == 'e')
			power = std::pow(10, 18);
		
		std::stringstream	ss(val);
		
		ss >> act_value;
		act_value *= power;

		return act_value;
	}
	else
	{
		std::stringstream	ss(token);
		
		ss >> act_value;
		
		return (act_value);
	}
}