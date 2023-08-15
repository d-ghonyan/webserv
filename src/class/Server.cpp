#include "Server.hpp"

Server::Server(): max_body_size(1), listen(), error_pages(), server_names(), locations() { }

void Server::pushListen(const std::string& l)
{
	listen.push_back(l);
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

void Server::printVectors(const std::vector<std::string>& vec)
{
	for (size_t i = 0; i < vec.size(); ++i)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << "\n";
}

Server::~Server() { }
