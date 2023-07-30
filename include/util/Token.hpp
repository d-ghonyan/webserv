#ifndef UTIL_TOKEN_HPP
# define UTIL_TOKEN_HPP

# include <iostream>

typedef enum 
{
	DIRECTIVE,
	BLOCK,
	// SEMICOLON,
	// BRACE,
} e_type;

struct Token
{
	e_type type;
	std::string name;

	Token();
	Token(const std::string& name);
};

#endif // UTIL_TOKEN_HPP