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