#ifndef UTIL_HPP
# define UTIL_HPP

# include <iostream>

struct NonDigit
{
	bool operator()(char c);
};

#endif // UTIL_HPP