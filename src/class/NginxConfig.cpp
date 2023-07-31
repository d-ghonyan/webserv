#include "NginxConfig.hpp"

NginxConfig::NginxConfig(): path(DEFAULT_FILE_PATH), servers(std::vector<Server>()) { }

NginxConfig::NginxConfig(const std::string &file_path): path(file_path), servers(std::vector<Server>()) { }

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

		// temp.type = (temp == "location" || temp == "server" ? BLOCK : DIRECTIVE);

		if (temp.name.size())
			tokens.push_back(temp);

		if (file[i] == ';' || file[i] == '{' || file[i] == '}')
			tokens.push_back(Token(std::string(1, file[i])));
	}
	// print(tokens, 0, "");
	std::cout << "\n";

	// servers.push_back(Server("first"));

	a(tokens);
	// parseTokens(tokens, 0, SERVER, servers[0]);
}

void NginxConfig::print() const
{
	for (size_t j = 0; j < servers.size(); ++j)
	{
		for (size_t i = 0; i < servers[j].locations.size(); ++i)
		{
			std::list<Location>::const_iterator it = servers[j].locations[i].begin();
			for (; it != servers[j].locations[i].end(); ++it)
			{
				std::cout << *(it) << "\n";
			}
			std::cout << "---------\n";
		}
		std::cout << "+++++++++++++++++++++++++++++++++++++++++\n";
	}
}

void NginxConfig::a(std::vector<Token>& tokens)
{
	size_t server_index = 0;
	size_t location_level = 0;
	size_t location_index = 0;

	for (size_t i = 0; i < tokens.size(); ++i)
	{
		if (tokens[i] == "server")
		{
			servers.push_back(Server("server"));
			++location_level;
			++i;
		}
		if (tokens[i] == "location")
		{
			if (location_level == 1)
			{
				std::list<Location> l;

				l.push_back(Location(tokens[++i].name));

				servers[server_index].locations.push_back(l);

				++i;
				++location_level;
			}
			else
			{
				servers[server_index].locations[location_index].push_back(Location(tokens[++i].name));
				++i;
				++location_level;
			}
		}
		if (tokens[i] == "}" && location_level != 0)
		{
			--location_level;

			if (location_level == 1)
				++location_index;
		}
		if (tokens[i] == "}" && location_level == 0)
		{
			++server_index;
			location_index = 0;
			location_level = 0;
		}
	}
	print();
}

NginxConfig::~NginxConfig()
{

}

template<typename T>
void NginxConfig::parseTokens(const std::vector<Token>& tokens, size_t i, e_type type, T& block)
{

}
