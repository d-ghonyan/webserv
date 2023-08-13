#ifndef CLASS_NGINX_CONFIG_HPP

# define CLASS_NGINX_CONFIG_HPP

# include <vector>
# include <fstream>
# include <sstream>
# include <iostream>
# include <algorithm>

# include <errno.h>
# include <string.h>

# include "Token.hpp"
# include "Server.hpp"

# define DEFAULT_FILE_PATH "conf.d/webserv.conf"

class NginxConfig
{
private:
	const std::string path;
	std::vector<Server> servers;

private:
	static char const * const allowed_tokens[];
	static char const * const allowed_names_server[];
	static char const * const allowed_names_location[];
	static char const * const array_value_directives_location[];
	static char const * const single_value_directives_location[];

	bool contains(char const * const allowed_tokens[], const std::string& token);

private:
	void	generateTokens(const std::string &file);
	void	parseLocations(std::vector<std::string> &tokens);
	void	check_braces(const std::vector<std::string> tokens);
	bool	alreadyExistsLocation(std::string	token, size_t server_index);
	bool	isNotContinueOfPrevious(std::string token, std::string prevToken);


private: // utils
	void listen(const std::vector<std::string>& tokens, size_t& server_index, size_t& location_level, size_t& i);
	void errorPage(const std::vector<std::string>& tokens, size_t& server_index, size_t& location_level, size_t& i);
	void serverName(const std::vector<std::string>& tokens, size_t& server_index, size_t& location_level, size_t& i);
	void maxBodySize(const std::vector<std::string>& tokens, size_t& server_index, size_t& location_level, size_t& i);

	void setter(Location& location, const std::string& name, const std::string& val);
	void setVectors(Location& current_location, const std::vector<std::string>& tokens, size_t& i);
	void setProperties(Location& current_location, const std::vector<std::string>& tokens, size_t& i);

public:
	NginxConfig();
	NginxConfig(const std::string &file_path);

	void parse();
	void print() const;

	~NginxConfig();
};

#endif // CLASS_NGINX_CONFIG_HPP