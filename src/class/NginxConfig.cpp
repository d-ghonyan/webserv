#include "NginxConfig.hpp"
#include <exception>


NginxConfig::NginxConfig() : path(DEFAULT_FILE_PATH), servers(std::vector<Server>()) {}

NginxConfig::NginxConfig(const std::string &file_path) : path(file_path), servers(std::vector<Server>()) {}

char const *const NginxConfig::allowed_tokens[] = {
	"server",
	"server_name",
	"listen",
	"max_client_body_size",
	"error_page",
	"{",
	"}",
	";",
	"location",
	"autoindex",
	"index",
	"root",
	"allowed_methods",
	"return",
	"cgi",
	"upload_dir",
};

char const *const NginxConfig::allowed_names_server[] = {
	"server_name",
	"listen",
	"max_client_body_size",
	"error_page"};

char const *const NginxConfig::allowed_names_location[] = {
	"location",
	"autoindex",
	"index",
	"root",
	"allowed_methods",
	"return",
	"cgi",
	"upload_dir",
};

bool is_allowed(const std::string &token)
{
	(void) token;
	return (1);
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



void NginxConfig::generateTokens(const std::string &file)
{
	std::vector<std::string> tokens;

	std::cout << "\n";
	for (size_t i = 0; i < file.size(); ++i)
	{
		std::string temp;

		while (file[i] && std::isspace(file[i]))
		{
			++i;
		}

		while (file[i] && !std::isspace(file[i]) && file[i] != ';' && file[i] != '{' && file[i] != '}')
		{
			temp.push_back(file[i]);
			++i;
		}

		if (temp.size())
			tokens.push_back(temp);

		if (file[i] == ';' || file[i] == '{' || file[i] == '}')
			tokens.push_back(std::string(1, file[i]));
	}
	for (size_t i = 0; i < tokens.size(); i++)
	{
		std::cout << "\'" << tokens[i] << "\'";
	}
	SeparateServerBlocksFromFile(tokens);

	// parseLocations(tokens);
	std::cout << "\n";
}

void	NginxConfig::SeparateServerBlocksFromFile(Tokens tokens)
{
	if (tokens.size() == 0)
		throw std::runtime_error("Empty file\n");
	if (tokens[0] == "server" && tokens[1] == "{")
	{
		//start stack and fill server blocks with tokens of seperated servers
		//need to fix it and make it more beautifull and  readable
	}
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

void NginxConfig::parseLocations(std::vector<std::string> &tokens)
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

				l.push_back(Location(tokens[++i]));

				servers[server_index].locations.push_back(l);

				++i;
				++location_level;
			}
			else
			{
				servers[server_index].locations[location_index].push_back(Location(tokens[++i]));
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
		}
	}
	print();
}

NginxConfig::~NginxConfig()
{
}
