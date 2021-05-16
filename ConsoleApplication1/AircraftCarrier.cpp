#include "AircraftCarrier.h"
#include <iostream>


int AircraftCarrier::get_size() const {
	return 4;
}

int AircraftCarrier::get_damage_value() const {
	return 4;
}

int AircraftCarrier::get_default_durability() const {
	return 5;
}

void AircraftCarrier::print_commands() const {
	std::cout << "-1x3 (Vert)\n-3x1 (Horiz)\n" << std::endl;
}

std::string AircraftCarrier::get_description() const {
	return "This big ship have bombardier-planes, which means it can bombard 3 cells in a row!";
}
