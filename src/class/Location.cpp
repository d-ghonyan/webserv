#include "Location.hpp"

Location::Location(): name()//, locations()
{

}

Location::Location(const std::string& name): name(name)//, locations()
{

}

std::string Location::getName() const
{
	return name;
}


std::ostream& operator<<(std::ostream& s, const Location& l)
{
	s << l.getName();
	return s;
}

// void Location::pushLocation(Location l)
// {
// 	locations.push_back(l);
// }


// Location& Location::getLastLocation()
// {
// 	return locations[locations.size() - 1];
// }


Location::~Location()
{

}
