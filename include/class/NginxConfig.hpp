#ifndef CLASS_NGINX_CONFIG_HPP

# define CLASS_NGINX_CONFIG_HPP

# include <map>
# include <cmath>
# include <stack>
# include <vector>
# include <fstream>
# include <sstream>
# include <iostream>
# include <algorithm>

# include <errno.h>
# include <string.h>

# include "Util.hpp"
# include "Server.hpp"

# define DEFAULT_FILE_PATH "conf.d/webserv.conf"

# define IS_OUTSIDE_LOCATION(token, prevToken) (strncmp(prevToken.c_str(), token.c_str(), prevToken.length()) != 0)

typedef	std::map<std::string, std::string> Hosts;

class NginxConfig
{
private:
	Hosts hosts;
	const std::string path;

private:
	static char const * const allowed_methods[];
	static char const * const array_value_directives_location[];
	static char const * const single_value_directives_location[];

	bool contains(char const * const allowed_tokens[], const std::string& token);

private:
	void	getHosts();
	void	generateTokens(const std::string &file);
	void	parseLocations(std::vector<std::string> &tokens);
	void	check_braces(const std::vector<std::string> tokens);
	bool	isInvalidValue(const std::string&);
	bool	containsSpecialChar(const std::string& token);
	bool	isValidErrorCode(const std::string& code);
	void	getHostValues(const std::string& line, std::string& key, std::string &value) const ;
	size_t	getActualBodySize(const std::string& token);

private:
	int		isValidIP(const std::string& host) const ;
	bool	isValidPort(const std::string& _port) const ;
	void	validationOfListen(std::string token, std::string& host, std::string& port) const ;
	std::string	storeIP(const std::string& _host, int count) const ;

private:
	void	listen(const std::vector<std::string>& tokens, size_t& server_index, size_t& location_level, size_t& i);
	void	errorPage(const std::vector<std::string>& tokens, size_t& server_index, size_t& location_level, size_t& i);
	void	serverName(const std::vector<std::string>& tokens, size_t& server_index, size_t& location_level, size_t& i);
	void	maxBodySize(const std::vector<std::string>& tokens, size_t& server_index, size_t& location_level, size_t& i);

	void	setter(Location& location, const std::string& name, const std::string& val);
	void	setVectors(Location& current_location, const std::vector<std::string>& tokens, size_t& i);
	void	setProperties(Location& current_location, const std::vector<std::string>& tokens, size_t& i);
	void	storeLocation(const std::vector<std::string>& tokens, std::vector<std::string>& current_location, size_t& location_level, const size_t& server_index, size_t& i);

public:
	NginxConfig();
	NginxConfig(const std::string &file_path);

	void	parse();

	~NginxConfig();

public:
	std::vector<Server> servers;
};

#endif // CLASS_NGINX_CONFIG_HPP