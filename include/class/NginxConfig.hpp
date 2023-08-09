#ifndef CLASS_NGINX_CONFIG_HPP

#define CLASS_NGINX_CONFIG_HPP

#include <vector>
#include <string.h>
#include <errno.h>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Server.hpp"
#include "Token.hpp"

#define DEFAULT_FILE_PATH "conf.d/webserv.conf"

template<typename T>
T	next(T it, typename std::iterator_traits<T>::difference_type n = 1) 
{
    std::advance(it, n);
    return it;
}

template<typename T>
T	prev(T it, typename std::iterator_traits<T>::difference_type n = -1) 
{
    std::advance(it, n);
    return it;
}

typedef std::vector<std::string> Tokens;
typedef std::vector<Tokens> BlocksOfServerTokens;

class NginxConfig
{
  public: //Edgar
	void					SeparateServerBlocksFromFile(const Tokens &tokens);
	void 					ValidateTokens(const Tokens &tokens);
	bool					isNotBalancedBraces(const Tokens &tokens);
	Tokens::const_iterator	getClosingBraceIterator(Tokens::const_iterator startIt);


  private: //Edgar
	BlocksOfServerTokens ServerBlocks;

  private:
	const std::string path;
	std::vector<Server> servers;
	static char const *const allowed_tokens[];
	static char const *const allowed_names_server[];
	static char const *const allowed_names_location[];

  public:
	NginxConfig();
	NginxConfig(const std::string &file_path);

	void parse();
	void print() const;

	void generateTokens(const std::string &file);
	template <typename T>
	void parseTokens(const std::vector<Token> &tokens, size_t i, e_type type, T &block);
	void parseLocations(std::vector<std::string> &tokens);
	~NginxConfig();
};

#endif // CLASS_NGINX_CONFIG_HPP