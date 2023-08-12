#include "NginxConfig.hpp"

void NginxConfig::setter(Location& location, const std::string& name, const std::string& val)
{
	if (name == "autoindex")
		location.setAutoindex(val);
	else if (name == "root")
		location.setRoot(val);
	else if (name == "return")
		location.setHttpRedir(val);
	else if (name == "cgi")
		location.setCgi(val);
	else if (name == "upload_dir")
		location.setUploadDir(val);
	else if (name == "index")
		location.pushIndexes(val);
	else if (name == "allow_methods")
		location.pushMethods(val);
}

void NginxConfig::setProperties(Location& current_location, const std::vector<std::string>& tokens, size_t& location_level, size_t& i)
{
	if (location_level <= 1)
		throw std::runtime_error(tokens[i] + " is not allowed here");

	std::string directive_name = tokens[i];

	size_t count = ++i;

	while (tokens[count] !=  ";" && tokens[count] != "{" && tokens[count] != "}")
	{
		setter(current_location, directive_name, tokens[count]);
		++count;
	}

	if (count == i || count - 1 != i || tokens[count] != ";")
		throw std::runtime_error("invalid" + directive_name + "directive");

	i = count;
}

void NginxConfig::setVectors(Location& current_location, const std::vector<std::string>& tokens, size_t& location_level, size_t& i)
{
	if (location_level <= 1)
		throw std::runtime_error(tokens[i] + " is not allowed here");

	std::string directive_name = tokens[i];

	size_t count = ++i;

	while (tokens[count] !=  ";" && tokens[count] != "{" && tokens[count] != "}")
	{
		setter(current_location, directive_name, tokens[count]);
		++count;
	}

	if (count == i || tokens[count] != ";")
		throw std::runtime_error("invalid " + directive_name + " directive");

	i = count;
}
