#ifndef CLASS_LOCATION_HPP
# define CLASS_LOCATION_HPP

#include <vector>
#include <iostream>

class Location
{
private:
	std::string name;
	// std::vector<Location> locations;
public:
	Location();

	Location(const std::string& name);

	std::string getName() const ;
	// Location& getLastLocation();
	// void pushLocation(Location l);
	~Location();
};

std::ostream& operator<<(std::ostream& s, const Location& l);

#endif // CLASS_LOCATION_HPP