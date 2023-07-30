#ifndef UTIL_TOKEN_HPP
# define UTIL_TOKEN_HPP

# include <iostream>

typedef enum 
{
	SERVER,
	LOCATION,
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
	bool operator==(const std::string& rhs) const ;
};

std::ostream& operator<<(std::ostream& s, const Token& t);

#endif // UTIL_TOKEN_HPP