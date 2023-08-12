#ifndef CLASS_SERVER_HPP
# define CLASS_SERVER_HPP

# include <map>
# include <vector>
# include <iostream>

# include "Location.hpp"

# define DEFAULT_PORT 80
# define DEFAULT_SERVER_NAME ""
# define DEFAULT_MAX_BODY_SIZE 1024

class Server
{
private:
	std::string max_body_size;
	std::vector<std::string> listen;
	std::map<std::string, std::string> error_pages;
	std::vector<std::string> server_names;

public:
	Server();
	~Server();

public:
	void pushListen(const std::string& l);
	void setMaxBodySize(const std::string& l);
	void pushServerName(const std::string& server_name);
	void pushErrorPage(const std::string& error_code, const std::string& error_page);

public:
	std::string getMaxBodySize() const ;

public:
	void print_everything();
	void printVectors(const std::vector<std::string>& vec);

public:
	std::map<std::string, Location> locations;
};

#endif // CLASS_SERVER_HPP