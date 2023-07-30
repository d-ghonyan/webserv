#include "Location.hpp"

Location::Location(): name(), locations()
{

}

Location::Location(const std::string& name): name(name), locations()
{

}

void Location::pushLocation(Location l)
{
	locations.push_back(l);
}


Location& Location::getLastLocation()
{
	return locations[locations.size() - 1];
}


Location::~Location()
{

}
