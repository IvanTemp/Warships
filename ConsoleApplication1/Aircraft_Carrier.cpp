#include "Aircraft_Carrier.h"
#include <iostream>

void Aircraft_Carrier::Print() const
{
	std::cout << name;
}

int Aircraft_Carrier::get_size() const
{
	return size;
}

std::string Aircraft_Carrier::get_name() const
{
	return name;
}

int Aircraft_Carrier::get_default_durability() const
{
	return default_durability;
}

