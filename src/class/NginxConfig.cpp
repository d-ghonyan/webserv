#include "NginxConfig.hpp"

NginxConfig::NginxConfig(): path(DEFAULT_FILE_PATH), servers(std::vector<Server>())
{

}

NginxConfig::NginxConfig(const std::string &file_path): path(file_path), servers(std::vector<Server>())
{

}

void NginxConfig::parse()
{
	std::ifstream conf(path.c_str());
	std::stringstream sstream;

	if (conf.fail())
		throw std::runtime_error(strerror(errno));

	sstream << conf.rdbuf();

	std::string file(sstream.str());

	generateTokens(file);
}

void NginxConfig::generateTokens(const std::string& file)
{
	std::vector<Token> tokens;

	std::cout << "\n";
	for (size_t i = 0; i < file.size(); ++i)
	{
		Token temp;

		while (file[i] && std::isspace(file[i])) { ++i; }

		while (file[i] && !std::isspace(file[i]) && file[i] != ';' && file[i] != '{' && file[i] != '}')
		{
			temp.name.push_back(file[i]);
			++i;
		}

		temp.type = (temp.name == "location" || temp.name == "server" ? BLOCK : DIRECTIVE);

		if (temp.name.size())
			tokens.push_back(temp);

		if (file[i] == ';' || file[i] == '{' || file[i] == '}')
			tokens.push_back(Token(std::string(1, file[i])));

	}
	print(tokens, 0, "");
	std::cout << "\n";
}
void NginxConfig::print(std::vector<Token>& tokens, size_t i, std::string indent)
{
	if (i == tokens.size())
		return ;
	std::cout << tokens[i].name << " ";
	
	if (tokens[i].name == "{")
		indent += "  ";
	else if (tokens[i].name == "}" && indent[0])
		indent.erase(indent.end() - 2, indent.end());
	
	if (tokens[i].name == ";" || tokens[i].name == "{" || tokens[i].name == "}")
		std::cout << "\n\n" << indent;
	
	print(tokens, ++i, indent);
}

NginxConfig::~NginxConfig()
{

}
