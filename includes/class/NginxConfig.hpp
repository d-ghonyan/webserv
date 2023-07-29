#ifndef CLASS_NGINX_CONFIG_HPP

# define CLASS_NGINX_CONFIG_HPP

# include <vector>
# include <string.h>
# include <errno.h>
# include <fstream>
# include <sstream>
# include <iostream>

# include "Server.hpp"

# define DEFAULT_FILE_PATH "conf.d/webserv.conf"

class NginxConfig
{
	private:
		const std::string path;
		std::vector<Server> servers;
	public:
	NginxConfig();
	NginxConfig(const std::string &file_path);

	void parse();

	~NginxConfig();
};

#endif // CLASS_NGINX_CONFIG_HPP