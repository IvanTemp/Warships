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

void Tsundere::print_commands() const
{
	std::cout << "-Shoot\n-Repair\n" << std::endl;
}

std::string Tsundere::get_description() const
{
	return "This ship have a tools for repairing, which means it can repair yourself!";
}
