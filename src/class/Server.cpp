#include "Server.hpp"

Server::Server(): max_body_size(1), listen(), error_pages(), server_names(), locations() { }

void Server::pushListen(const std::string& host, const std::string& port)
{
	if (std::find(listen.begin(), listen.end(), listen_t(host, port)) != listen.end())
		throw std::runtime_error("duplicate listen " + host + ":" + port);
	listen.push_back(listen_t(host, port));
}

size_t Server::getMaxBodySize() const
{
	return max_body_size;
}

void Server::setMaxBodySize(size_t	l)
{
	max_body_size = l;
}

void Server::pushServerName(const std::string& server_name)
{
	server_names.push_back(server_name);
}

void Server::pushErrorPage(ErrorCode error_code, const std::string& error_page)
{
	error_pages[error_code] = error_page;
}

void Server::print_everything()
{
	std::cout << "Server names: ";
	printVectors(server_names);
	std::cout << "Listen: ";
	printVectors(listen);
	std::cout << "Error pages: \n";

	for (std::map<int, std::string>::iterator it = error_pages.begin(); it != error_pages.end(); ++it)
		std::cout << "  " << it->first << " " << it->second << " \n";

	std::cout << "\n";
	std::cout << "Max body size: " << max_body_size << "\n";
	std::cout << "Locations: \n------\n";

	for (LocationMap::iterator it = locations.begin(); it != locations.end(); ++it)
	{
		it->second.printEverything("  ");
		std::cout << "++++++++++++++\n\n";
	}
	std::cout << "--------\n";
}

template <typename T>
void Server::printVectors(const std::vector<T>& vec)
{
	for (size_t i = 0; i < vec.size(); ++i)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << "\n";
}

Server::~Server() { }
