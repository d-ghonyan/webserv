#include "Token.hpp"

Token::Token(): type(DIRECTIVE), name()
{

}

std::ostream& operator<<(std::ostream& s, const Token& t)
{
	s << t.name;
	return s;
}

bool Token::operator==(const std::string& rhs) const
{
	return name == rhs;
}


Token::Token(const std::string& n): type(DIRECTIVE), name(n)
{

}
