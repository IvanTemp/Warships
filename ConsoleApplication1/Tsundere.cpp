#include "Tsundere.h"

void Tsundere::print() const
{
	std::cout << name_;
}

int Tsundere::get_size() const
{
	return size_;
}

std::string Tsundere::get_name() const
{
	return name_;
}

int Tsundere::get_default_durability() const
{
	return default_durability_;
}
