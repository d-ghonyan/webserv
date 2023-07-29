#include "NginxConfig.hpp"
#include "Server.hpp"

NginxConfig::NginxConfig(): path(DEFAULT_FILE_PATH)
{
	std::cout << path << "\n";
}

NginxConfig::NginxConfig(std::string file_path): path(file_path)
{
	std::cout << path << "\n";
}

NginxConfig::~NginxConfig()
{

}
