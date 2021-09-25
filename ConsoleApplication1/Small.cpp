#include "Small.h"


int Small::get_size() const {
	return 1;
}

int Small::get_damage_value() const {
	return 1 + rand() % 3;
}

int Small::get_default_durability() const {
	return 3;
}

void Small::print_commands() const {
	std::cout << "-Shoot\n-Move\n" << std::endl;
}

std::string Small::get_description() const {
	return "This small ship is small, which means it can move in other cells";
}
