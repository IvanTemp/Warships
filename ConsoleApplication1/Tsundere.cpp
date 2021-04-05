#include "Tsundere.h"

void Tsundere::print() const
{
	std::cout << name_;
}

int Tsundere::get_size() const
{
	return size_;
}

int Tsundere::get_damage_value() const
{
	return damage_;
}

std::string Tsundere::get_name() const
{
	return name_;
}

int Tsundere::get_default_durability() const
{
	return default_durability_;
}

void Tsundere::special_action() {
}
