#include "Tsundere.h"

void Tsundere::Print() const
{
	std::cout << name;
}

int Tsundere::get_size() const
{
	return size;
}

std::string Tsundere::get_name() const
{
	return name;
}

int Tsundere::get_default_durability() const
{
	return default_durability;
}
