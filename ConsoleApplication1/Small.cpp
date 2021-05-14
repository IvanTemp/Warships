#include "Small.h"

void Small::print() const
{
	std::cout << "Small";
}

int Small::get_size() const
{
	return 1;
}

int Small::get_damage_value() const
{
	return 2;
}

std::string Small::get_name() const
{
	return "Small";
}

int Small::get_default_durability() const
{
	return 3;
}

void Small::print_commands() const
{
	std::cout << "-Shoot\n-Move\n" << std::endl;
}

std::string Small::get_description() const
{
	return "This small ship is small, which means it can move in other cells";
}
