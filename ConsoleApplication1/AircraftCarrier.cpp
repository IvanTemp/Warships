#include "AircraftCarrier.h"
#include <iostream>

void AircraftCarrier::print() const
{
	std::cout << name_;
}

int AircraftCarrier::get_size() const
{
	return size_;
}

int AircraftCarrier::get_damage_value() const
{
	return damage_;
}

std::string AircraftCarrier::get_name() const
{
	return name_;
}

int AircraftCarrier::get_default_durability() const
{
	return default_durability_;
}

void AircraftCarrier::print_commands() const
{
	std::cout << "-1x3 (Vert)\n-3x1 (Horiz)\n" << std::endl;
}
