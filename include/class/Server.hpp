#ifndef CLASS_SERVER_HPP
# define CLASS_SERVER_HPP

# include <list>
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
		std::string name;
		std::string serverName;
	public:
		Server();
		Server(const std::string& name);
		void pushLocation(Location l);
		Location& getLastLocation();
		~Server();
	public:
		std::vector< std::list<Location> > locations;
};

#endif // CLASS_SERVER_HPP