#include "NginxConfig.hpp"

void NginxConfig::validationOfListen(std::string token, std::string& host, std::string& port) const
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
		// else if (is)
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

bool NginxConfig::isValidHost(const std::string& host) const
{
	std::vector<std::string>	ip_vector(4, "0");
	size_t	count = 0;
	
	// for (size_t i = 1; i < host.length(); i++)
	// {
		
	// }

	// for (int i = 0; (i = s.find('.', i)) != std::string::npos; i++) 
	// {
	// 	count++;
    // }
}

bool NginxConfig::isValidPort(const std::string& _port) const
{
	std::string::const_iterator start	= _port.begin();
	std::string::const_iterator end		= _port.end();
	std::string::const_iterator it		= std::find_if(start, end, NonDigit());
	
	if (it != end)
		return false;

	size_t	p = 0;
	std::stringstream ss(_port);
	ss >> p;
	if (p > 65535)
		return false;			
	return true;
}
