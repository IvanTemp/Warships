#include "Small.h"

void Small::print() const
{
	std::cout << name_;
}

int Small::get_size() const
{
	return size_;
}

int Small::get_damage_value() const
{
	return damage_;
}

std::string Small::get_name() const
{
	return name_;
}

int Small::get_default_durability() const
{
	return default_durability_;
}

void Small::print_commands() const
{
	std::cout << "-Shoot\n-Move\n" << std::endl;
}
