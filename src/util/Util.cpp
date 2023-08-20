#include "Util.hpp"

bool NonDigit::operator()(char c)
{
	return !::isdigit(c);
}
