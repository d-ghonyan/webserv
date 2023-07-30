#ifndef CLASS_SERVER_HPP
# define CLASS_SERVER_HPP

# include <vector>
# include <iostream>

# include "Location.hpp"

# define DEFAULT_PORT 80
# define DEFAULT_ROOT "www/"
# define DEFAULT_AUTOINDEX 0
# define DEFAULT_SERVER_NAME ""
# define DEFAULT_MAX_BODY_SIZE 1024

class Server
{
private:
public:
	Server();
	/// TODO: make private
	std::string name;
	std::string serverName;
	std::vector<Location> locations;
	Server(const std::string& name);
	void pushLocation(Location l);
	Location& getLastLocation();
	~Server();
};

#endif // CLASS_SERVER_HPP