#ifndef CLASS_NGINX_CONFIG_HPP

# define CLASS_NGINX_CONFIG_HPP

# include <vector>
# include <string.h>
# include <errno.h>
# include <fstream>
# include <sstream>
# include <iostream>

# include "Server.hpp"
# include "Token.hpp"

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
		void print() const ;

		void generateTokens(const std::string& file);
		template<typename T>
		void parseTokens(const std::vector<Token>& tokens, size_t i, e_type type, T& block);
		void a(std::vector<Token>& tokens);
		~NginxConfig();
};

#endif // CLASS_NGINX_CONFIG_HPP