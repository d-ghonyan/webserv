#include "Location.hpp"

Location::Location():
	_locaction_level(1), _cgi("/usr/bin/python3"), _root("www/"), _route(""), _autoindex("off"), _httpRedir(""),
	_upload_dir("/www/upload"), _indexes(1, "index.html"), _allowed_methods(1, "GET"), parent("barev")
{

}

Location::Location(const std::string& route, std::string p, int loc_l):
	_locaction_level(loc_l), _cgi("/usr/bin/python3"), _root("www/"), _route(route), _autoindex("off"), _httpRedir(""),
	_upload_dir("/www/upload"), _indexes(1, "index.html"), _allowed_methods(1, "GET"), parent(p)
{

}

Location::Location(const std::string& route):
	_locaction_level(1), _cgi(), _root(), _route(route), _autoindex("off"), 
	_httpRedir(), _upload_dir(), _indexes(), _allowed_methods(), parent()
{

}

Location::Location(const Location& other)
{
	_cgi = other._cgi;
	_root = other._root;
	_route = other._route;
	_indexes = other._indexes;
	_autoindex = other._autoindex;
	_httpRedir = other._httpRedir;
	_upload_dir = other._upload_dir;
	_allowed_methods = other._allowed_methods;
	_locaction_level = other._locaction_level + 1;
	parent = "copy constructor baby, no parent needed";
}

void Location::pushIndexes(const std::string& index)
{
	_indexes.push_back(index);
}

void Location::pushMethods(const std::string& method)
{
	_allowed_methods.push_back(method);
}

void Location::setCgi(const std::string& cgi)
{
	_cgi = cgi;
}

void Location::setRoot(const std::string& root)
{
	_root = root;
}

void Location::setAutoindex(const std::string& autoindex)
{
	_autoindex = autoindex;
}

void Location::setHttpRedir(const std::string& redir)
{
	_httpRedir = redir;
}

void Location::setUploadDir(const std::string& dir)
{
	_upload_dir = dir;
}

std::string Location::getroute() const
{
	return _route;
}

void Location::printEverything(const std::string& indent) const
{
	std::cout << indent << "Location_level: " << _locaction_level << "\n";
	std::cout << indent << "Route: " << _route << "\n";
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

std::string Location::getParent() const
{
	return parent != "" ? parent : "N/A";
}

bool Location::operator<(const Location& other) const
{
	return _route < other._route;
}

bool Location::operator==(const Location& rhs) const
{
	return ( _route == rhs._route &&
			_locaction_level == rhs._locaction_level &&
			parent == rhs.parent );
}


std::ostream& operator<<(std::ostream& s, const Location& l)
{
	s << l.getroute() << ", parent: " << l.getParent();
	return s;
}

Location::~Location()
{

}
