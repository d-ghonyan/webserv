#include "Server.hpp"

Server::Server(): name(), locations()
{

}

Server::Server(const std::string& name): name(name), locations()
{

}

void Server::pushLocation(Location l)
{
	(void)l;
	// locations.push_back(l);
}

Location& Server::getLastLocation()
{
	// return locations[locations.size() - 1];
}

Server::~Server()
{

}
