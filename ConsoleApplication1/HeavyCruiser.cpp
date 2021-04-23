#include "HeavyCruiser.h"

void HeavyCruiser::print() const
{
	std::cout << name_;
}

int HeavyCruiser::get_size() const
{
	return size_;
}

int HeavyCruiser::get_damage_value() const
{
	return damage_;
}

std::string HeavyCruiser::get_name() const
{
	return name_;
}

int HeavyCruiser::get_default_durability() const
{
	return default_durability_;
}

void HeavyCruiser::print_commands() const
{
	std::cout << "-Shoot (3x3)\n" << std::endl;
}
