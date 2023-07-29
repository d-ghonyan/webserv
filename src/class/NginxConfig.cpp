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

	for (size_t i = 0; i < file.size(); ++i)
	{
		std::cout << file[i];
	}
	std::cout << "\n";
}

NginxConfig::~NginxConfig()
{

}
