#include "Location.hpp"

Location::Location():
	_location_level(1), _cgi(DEFAULT_CGI), _root(DEFAULT_ROOT), _autoindex(DEFAULT_AUTOINDEX), _httpRedir(HTTP_REDIRECTION),
	_upload_dir(UPLOAD_DIRECTORY), _indexes(), _allowed_methods()
{
	// _allowed_methods.push_back("POST");
	// _allowed_methods.push_back("DELETE");
}

Location::Location(int loc_l):
	_location_level(loc_l), _cgi(DEFAULT_CGI), _root(DEFAULT_ROOT), _autoindex(DEFAULT_AUTOINDEX), _httpRedir(HTTP_REDIRECTION),
	_upload_dir(UPLOAD_DIRECTORY), _indexes(), _allowed_methods()
{
	// _allowed_methods.push_back("POST");
	// _allowed_methods.push_back("DELETE");
}

Location::Location(const Location& other)
{
	_cgi = other._cgi;
	_root = other._root;
	_indexes = other._indexes;
	_autoindex = other._autoindex;
	_httpRedir = other._httpRedir;
	_upload_dir = other._upload_dir;
	_allowed_methods = other._allowed_methods;
}

void Location::pushIndexes(const std::string& index) { _indexes.push_back(index); }

void Location::pushMethods(const std::string& method) { _allowed_methods.push_back(method); }

void Location::setCgi(const std::string& cgi) { _cgi = cgi; }

void Location::setRoot(const std::string& root) { _root = root; }

void Location::setAutoindex(const std::string& autoindex) { _autoindex = autoindex; }

void Location::setHttpRedir(const std::string& redir) { _httpRedir = redir; }

void Location::setUploadDir(const std::string& dir) { _upload_dir = dir; }

void Location::setLevel(const int& level) { _location_level = level; }

// return values of directives or root by default
const std::string& Location::getValueOf(const std::string& directiveName)
{
	if (directiveName == "autoindex")
		return _autoindex;
	else if (directiveName == "root")
		return _root;
	else if (directiveName == "return")
		return _httpRedir;
	else if (directiveName == "cgi")
		return _cgi;
	else if (directiveName == "upload_dir")
		return _upload_dir;
	return _root;
}

// return the array indexes (default) or allowed methods
const std::vector<std::string>& Location::getArrayOf(const std::string& directiveName)
{
	if (directiveName == "index")
		return _indexes;
	else if (directiveName == "allow_methods")
		return _allowed_methods;
	return _indexes;
}

void Location::printEverything(const std::string& indent) const
{
	std::cout << indent << "Location_level: " << _location_level << "\n";
	std::cout << indent << "Cgi: " << _cgi << "\n";
	std::cout << indent << "Root: " << _root << "\n";
	std::cout << indent << "Autoindex: " << _autoindex << "\n";
	std::cout << indent << "Http Redirection: " << _httpRedir << "\n";
	std::cout << indent << "Upload Dir: " << _upload_dir << "\n";
	std::cout << indent << "Indexes: \n";
	printVectors(_indexes, indent + "\t");
	std::cout << indent << "Allowed_methods: \n";
	printVectors(_allowed_methods, indent + "\t");
}

void Location::printVectors(const std::vector<std::string>& vec, const std::string& indent) const
{
	for (size_t i = 0; i < vec.size(); ++i)
	{
		std::cout << indent << vec[i] << " ";
	}
	std::cout << "\n";
}

bool Location::operator<(const Location& other) const
{
	return _location_level < other._location_level;
}

bool Location::operator==(const Location& rhs) const
{
	return _location_level == rhs._location_level;
}

Location::~Location()
{

}
