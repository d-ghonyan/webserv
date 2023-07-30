#ifndef CLASS_LOCATION_HPP
# define CLASS_LOCATION_HPP

#include <vector>
#include <iostream>

class Location
{
private:
public:
	Location();
	/// TODO: make private
	std::string name;
	std::vector<Location> locations;
	Location(const std::string& name);
	Location& getLastLocation();
	void pushLocation(Location l);
	~Location();
};

#endif // CLASS_LOCATION_HPP