#ifndef CLASS_LOCATION_HPP
# define CLASS_LOCATION_HPP

#include <vector>
#include <iostream>

class Location
{
private:
	std::vector<Location> locations;
public:
	Location();
	~Location();
};

#endif // CLASS_LOCATION_HPP