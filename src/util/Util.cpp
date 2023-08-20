#include "Util.hpp"

std::ostream& operator<<(std::ostream& os, const listen_t& ls)
{
	os << ls.host << " " << ls.port;
	return os;
}

bool listen_t::operator==(const listen_s& ls)
{
	return host == ls.host && port == ls.port;
}

bool NonDigit::operator()(char c)
{
	return !::isdigit(c);
}

std::vector<std::string> splitIP(const std::string& line, int delim_count, char delim) // tox lrvi
{
	std::stringstream ss(line);
	std::vector<std::string> ret;

	for (int i = 0; i < delim_count + 1; ++i)
	{
		std::string res;

		std::getline(ss, res, delim);

		ret.push_back(res);
	}

	return ret;
}
