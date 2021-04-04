#include "Heavy_Cruiser.h"

void Heavy_Cruiser::print() const
{
	std::cout << name_;
}

int Heavy_Cruiser::get_size() const
{
	return size_;
}

std::string Heavy_Cruiser::get_name() const
{
	return name_;
}

int Heavy_Cruiser::get_default_durability() const
{
	return default_durability_;
}
