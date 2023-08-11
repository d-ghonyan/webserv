#include "NginxConfig.hpp"
#include <exception>
#include <stack>

NginxConfig::NginxConfig() : path(DEFAULT_FILE_PATH), servers(std::vector<Server>()) {}

NginxConfig::NginxConfig(const std::string &file_path) : path(file_path), servers(std::vector<Server>()) {}

char const * const NginxConfig::single_value_directives_location[] = {
	"autoindex",
	"root",
	"return",
	"cgi",
	"upload_dir",
	NULL,
};

char const * const NginxConfig::array_value_directives_location[] = {
	"index",
	"allow_methods",
	NULL,
};

bool NginxConfig::contains(char const * const allowed[], const std::string &token)
{
	for (size_t i = 0; allowed[i]; ++i)
	{
		if (token == allowed[i])
			return true;
	}

	return (false);
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

	check_braces(tokens);

	parseLocations(tokens);
	std::cout << "\n";
}

void NginxConfig::check_braces(const std::vector<std::string> tokens)
{
	std::stack<int> br;

	for (size_t i = 0; i < tokens.size(); ++i)
	{
		if (tokens[i] == "{")
			br.push(0);
		else if (tokens[i] == "}")
		{
			if (br.size() == 0)
				throw std::runtime_error("wrong braces");
			br.pop();
		}
	}
	if (br.size() != 0) throw std::runtime_error("wrong braces");
}

void NginxConfig::parseLocations(std::vector<std::string> &tokens)
{
	size_t server_index = 0;
	size_t location_level = 0;
	size_t location_index = 0;

	std::vector<std::string> current_location;

	for (size_t i = 0; i < tokens.size(); ++i)
	{
		if (location_level == 0 && tokens[i] != "server")
		{
			throw std::runtime_error("expected server block, found " + tokens[i]);
		}
		if (tokens[i] == "server")
		{
			servers.push_back(Server());
			++location_level;

			++i;

			if (i == tokens.size() || tokens[i] != "{")
				throw std::runtime_error("invalid file");

			++i;
		}
		if (tokens[i] == "server_name")
			serverName(tokens, server_index, location_level, i);
		else if (tokens[i] == "listen")
			listen(tokens, server_index, location_level, i);
		else if (tokens[i] == "client_max_body_size")
			maxBodySize(tokens, server_index, location_level, i);
		else if (tokens[i] == "error_page")
			errorPage(tokens, server_index, location_level, i);
		else if (contains(single_value_directives_location, tokens[i]))
			setProperties(const_cast<Location&>(servers[server_index].locations[location_index]
				.find(current_location.back())->first),
				tokens,location_level, i);
		else if (contains(array_value_directives_location, tokens[i]))
			setVectors(const_cast<Location&>(servers[server_index].locations[location_index]
				.find(current_location.back())->first),
				tokens,location_level, i);
		if (tokens[i] == "location")
		{
			if (location_level == 1)
			{
				LocationMap m;

				++i;
				current_location.push_back(tokens[i]);

				m.insert(std::make_pair(Location(tokens[i]), tokens[i]));

				servers[server_index].locations.push_back(m);

				++i;
				++location_level;
			}
			else
			{
				++i;
				servers[server_index].locations[location_index]
					.insert(std::make_pair(Location(tokens[i], current_location.back()), tokens[i]));
				current_location.push_back(tokens[i]);
				++i;
				++location_level;
			}
		}
		if (tokens[i] == "}" && location_level != 0)
		{
			--location_level;

			if (current_location.size()) current_location.pop_back();
			if (location_level == 1)
				++location_index;
		}
		if (tokens[i] == "}" && location_level == 0)
		{
			++server_index;
			location_index = 0;
		}
	}

	for (size_t i = 0; i < servers.size(); ++i)
	{
		servers[i].print_everything();
		std::cout << "===================\n";
	}

	print();
}

NginxConfig::~NginxConfig() { }

void NginxConfig::print() const
{
	for (size_t j = 0; j < servers.size(); ++j)
	{
		for (size_t i = 0; i < servers[j].locations.size(); ++i)
		{
			LocationMap::const_iterator it = servers[j].locations[i].begin();
			for (; it != servers[j].locations[i].end(); ++it)
			{
				std::cout << it->first << "\n";
			}
			std::cout << "---------\n";
		}
		std::cout << "+++++++++++++++++++++++++++++++++++++++++\n";
	}
}

// char const * const NginxConfig::allowed_tokens[] = {
// 	"server",
// 	"server_name",
// 	"listen",
// 	"max_client_body_size",
// 	"error_page",
// 	"{", "}", ";",
// 	"location",
// 	"autoindex",
// 	"index",
// 	"root",
// 	"allowed_methods",
// 	"return",
// 	"cgi",
// 	"upload_dir",
// 	NULL,
// };

// char const * const NginxConfig::allowed_names_server[] = {
// 	"server_name",
// 	"listen",
// 	"client_max_body_size",
// 	"error_page",
// 	NULL,
// };

// char const * const NginxConfig::allowed_names_location[] = {
// 	"location",
// 	"autoindex",
// 	"index",
// 	"root",
// 	"allowed_methods",
// 	"return",
// 	"cgi",
// 	"upload_dir",
// 	NULL,
// };

// void	NginxConfig::validateTokens(const std::vector<std::string> &tokens)
// {
// 	int in_file = 1;
// 	int in_server = 0;
// 	int in_location = 0;

// 	for (size_t i = 0; i < tokens.size(); ++i)
// 	{
// 		if (in_file && tokens[i] != "server")
// 			throw std::runtime_error("invalid directive");
// 		if (tokens[i] == "server")
// 		{
// 			in_file = 0;
// 			in_server = 1;
// 			++i;

// 			if (i == tokens.size() || tokens[i] != "{")
// 				throw std::runtime_error("invalid file");
			
// 			++i;

// 			if (tokens[i] == "server_name")
// 			{
				
// 			}
// 			else if (tokens[i] == "listen")
// 			{

// 			}
// 			else if (tokens[i] == "max_client_body_size")
// 			{

// 			}
// 			else if (tokens[i] == "error_page")
// 			{

// 			}
// 			else if (tokens[i] == "location")
// 			{

// 			}
// 			/*
// 				"server_name",
// 				"listen",	
// 				"max_client_body_size",
// 				"error_page",*/
// 		}
// 	}
// }
