#ifndef CLASS_SERVER_HPP
# define CLASS_SERVER_HPP

# include <vector>
# include <iostream>

# include "Location.hpp"

# define DEFAULt_PORT 80
# define DEFAULT_ROOT "www/"
# define DEFAULT_AUTOINDEX 0
# define DEFAULT_SERVER_NAME ""
# define DEFAULT_MAX_BODY_SIZE 1024

class Server
{
private:
	std::string serverName;
	std::vector<Location> locations;
public:
	Server();
	~Server();
};

#endif // CLASS_SERVER_HPP