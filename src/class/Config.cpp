#include "Config.hpp"

Config::Config(): ConfigParser(DEFAULT_FILE_PATH), defaultLocation()
{
	defaultLocation.pushIndexes("index.html");
	defaultLocation.pushMethods("GET");
	defaultLocation.pushMethods("POST");
}

Config::Config(const std::string& filename): ConfigParser(filename), defaultLocation()
{
	defaultLocation.pushIndexes("index.html");
	defaultLocation.pushMethods("GET");
	defaultLocation.pushMethods("POST");
}

const std::vector<Server>& Config::getServers() const { return servers; }

const Location& Config::getLocationData(const std::string& host, const std::string& port, const std::string& serverName, const std::string& route)
{
	size_t count = std::count(servers.begin(), servers.end(), listen_t(host, port));

	ConfigParser::const_iterator it = std::find(servers.begin(), servers.end(), listen_t(host, port));

	if (count == 1)
	{
		ConfigParser::const_location_iterator l_it = it->locations.find(route);

		defaultLocation.setRoot(it->getRoot());

		return l_it == it->locations.end() ? defaultLocation : l_it->second;
	}

	if (count > 1)
	{
		ConfigParser::const_iterator s_it = std::find(servers.begin(), servers.end(), serverName);

		if (s_it == servers.end())
			s_it = servers.begin();

		defaultLocation.setRoot(s_it->getRoot());

		ConfigParser::const_location_iterator l_it = s_it->locations.find(route);

		return l_it == s_it->locations.end() ? defaultLocation : l_it->second;
	}

	if (count == 0)
	{
		ConfigParser::const_iterator it = std::find(servers.begin(), servers.end(), listen_t("", port));

		if (it == servers.end())
			return defaultLocation; // this shouldn't happen

		defaultLocation.setRoot(it->getRoot());

		ConfigParser::const_location_iterator l_it = it->locations.find(route);

		return l_it == it->locations.end() ? defaultLocation : l_it->second;
	}

	return defaultLocation; // and this too
}

Config::~Config() { }
