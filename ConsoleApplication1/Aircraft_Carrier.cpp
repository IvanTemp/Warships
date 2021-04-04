#include "Aircraft_Carrier.h"
#include <iostream>

void Aircraft_Carrier::print() const
{
	std::cout << name_;
}

int Aircraft_Carrier::get_size() const
{
	return size_;
}

std::string Aircraft_Carrier::get_name() const
{
	return name_;
}

int Aircraft_Carrier::get_default_durability() const
{
	return default_durability_;
}

