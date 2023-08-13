#ifndef CLASS_LOCATION_HPP
# define CLASS_LOCATION_HPP

# include <map>
# include <list>
# include <vector>
# include <iostream>

# define DEFAULT_CGI ""
# define INDEX "index.html"
# define DEFAULT_ROOT "www/"
# define HTTP_REDIRECTION ""
# define DEFAULT_AUTOINDEX "off"
# define UPLOAD_DIRECTORY "upload/"
# define ALLOWED_METHODS "GET POST HEAD"

class Location
{
private:
	int 						_locaction_level;
	std::string					_cgi;
	std::string					_root;
	std::string					_route;
	std::string					_autoindex;
	std::string					_httpRedir;
	std::string					_upload_dir;
	std::vector<std::string>	_indexes;
	std::vector<std::string>	_allowed_methods;

	std::string parent;

public:
	void setCgi(const std::string&);
	void setRoot(const std::string&);
	void pushIndexes(const std::string&);
	void pushMethods(const std::string&);
	void setAutoindex(const std::string&);
	void setHttpRedir(const std::string&);
	void setUploadDir(const std::string&);

	void printEverything(const std::string& indent) const ;
	void printVectors(const std::vector<std::string>& vec, const std::string& indent) const ;

public:
	Location();
	Location(const std::string& route);
	Location(const std::string& route, std::string p, int loc_l);

	std::string getroute() const ;
	std::string getParent() const ;
	
	bool operator<(const Location& other) const ;
	bool operator==(const Location& rhs) const;

	~Location();
};

std::ostream& operator<<(std::ostream& s, const Location& l);

typedef std::map<std::string, Location> LocationMap;

#endif // CLASS_LOCATION_HPP