#ifndef CLASS_SERVER_HPP
# define CLASS_SERVER_HPP

# include <map>
# include <vector>
# include <iostream>

# include "Location.hpp"

# define DEFAULT_PORT 80
# define DEFAULT_SERVER_NAME ""
# define DEFAULT_MAX_BODY_SIZE 1

typedef std::string	Route;
typedef std::string	ErrorPagePath;
typedef int			ErrorCode;

class Server
{
private:
	size_t								max_body_size;
	std::vector<std::string>			listen;
	std::map<ErrorCode, ErrorPagePath>	error_pages;
	std::vector<std::string> 			server_names;

public:
	Server();
	~Server();

public:
	void pushListen(const std::string& l);
	void setMaxBodySize(size_t l);
	void pushServerName(const std::string& server_name);
	void pushErrorPage(ErrorCode error_code, const std::string& error_page);

public:
	size_t getMaxBodySize() const ;

public:
	void print_everything();
	void printVectors(const std::vector<std::string>& vec);

public:
	std::map<Route, Location> locations;
};

#endif // CLASS_SERVER_HPP