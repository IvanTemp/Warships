#include "Heavy_Cruiser.h"

void Heavy_Cruiser::Print() const
{
	std::cout << name;
}

int Heavy_Cruiser::get_size() const
{
	return size;
}

std::string Heavy_Cruiser::get_name() const
{
	return name;
}

int Heavy_Cruiser::get_default_durability() const
{
	return default_durability;
}
