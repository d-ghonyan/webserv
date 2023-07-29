#ifndef CLASS_NGINX_CONFIG_HPP

# define CLASS_NGINX_CONFIG_HPP

# include <vector>
# include <iostream>

# include "Server.hpp"

# define DEFAULT_FILE_PATH "config/webserv.conf"

class NginxConfig
{
	private:
		std::string path;
		std::vector<Server> servers;
	public:
		NginxConfig();
		NginxConfig(std::string file_path);
		~NginxConfig();
};

#endif // CLASS_NGINX_CONFIG_HPP