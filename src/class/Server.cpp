#include "Server.hpp"

Server::Server(): max_body_size(), listen(), error_pages(), server_names(), locations()
{

}

void Server::pushListen(const std::string& l)
{
	listen.push_back(l);
}

void Server::setMaxBodySize(const std::string& l)
{
	max_body_size = l;
}

void Server::pushServerName(const std::string& server_name)
{
	server_names.push_back(server_name);
}

void Server::pushErrorPage(const std::string& server_name)
{
	error_pages.push_back(server_name);
}

void Server::print_everything()
{
	std::cout << "Server names: ";
	printVectors(server_names);
	std::cout << "Listen: ";
	printVectors(listen);
	std::cout << "Error pages: ";
	printVectors(error_pages);
	std::cout << "Max body size: " << max_body_size << "\n";
	std::cout << "Locations: \n------\n";

	for (size_t i = 0; i < locations.size(); ++i)
	{

		for (LocationMap::iterator it = locations[i].begin(); it != locations[i].end(); ++it)
		{
			std::string indent = "";
			for (size_t j = 0; j < i; ++j)
			{
				indent += "\t";
			}
			
			it->first.printEverything(indent);
			std::cout << "++++++++++++++\n\n";
		}
		/* code */
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

// Location& Server::getLastLocation()
// {
// 	// return Location("barev");
// 	// return locations[locations.size() - 1];
// }

Server::~Server()
{

}
