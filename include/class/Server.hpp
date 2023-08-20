#ifndef CLASS_SERVER_HPP
# define CLASS_SERVER_HPP

# include <map>
# include <vector>
# include <iostream>

# include "Util.hpp"
# include "Location.hpp"

# define DEFAULT_SERVER_NAME ""
# define DEFAULT_MAX_BODY_SIZE 1

typedef int			ErrorCode;
typedef std::string	Route;
typedef std::string	ErrorPagePath;

class Server
{
private:
	size_t								max_body_size;
	std::vector<listen_t>				listen;
	std::map<ErrorCode, ErrorPagePath>	error_pages;
	std::vector<std::string> 			server_names;

public:
	Server();
	~Server();

public:
	void pushListen(const std::string& host, const std::string& port);
	void setMaxBodySize(size_t l);
	void pushServerName(const std::string& server_name);
	void pushErrorPage(ErrorCode error_code, const std::string& error_page);

public:
	size_t getMaxBodySize() const ;

public:
	void print_everything();
	template <typename T>
	void printVectors(const std::vector<T>& vec);

public:
	std::map<Route, Location> locations;
};

#endif // CLASS_SERVER_HPP