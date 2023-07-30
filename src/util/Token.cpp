#include "Token.hpp"

Token::Token(): type(DIRECTIVE), name()
{

}

Token::Token(const std::string& n): type(DIRECTIVE), name(n)
{

}
