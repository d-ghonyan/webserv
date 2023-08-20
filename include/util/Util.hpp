#ifndef UTIL_HPP
# define UTIL_HPP

# include <vector>
# include <iostream>
# include <sstream>

typedef struct listen_s
{
	std::string host;
	std::string port;

	listen_s(): host(NULL), port("8080") {};
	listen_s(const std::string& hst, const std::string& prt): host(hst), port(prt) {};
	bool operator==(const listen_s& ls);

} listen_t ;

std::ostream& operator<<(std::ostream& os, const listen_t& ls);

std::vector<std::string> splitIP(const std::string& line, int delim_count, char delim); // tox lrvi

struct NonDigit
{
	bool operator()(char c);
};

#endif // UTIL_HPP