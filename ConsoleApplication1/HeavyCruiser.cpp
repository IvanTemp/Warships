#include "HeavyCruiser.h"

int HeavyCruiser::get_size() const {
	return 3;
}

int HeavyCruiser::get_damage_value() const {
	return 1;
}

int HeavyCruiser::get_default_durability() const {
	return 6;
}

void HeavyCruiser::print_commands() const {
	std::cout << "-Shoot (3x3)\n" << std::endl;
}

std::string HeavyCruiser::get_description() const {
	return "This ship have 3 installations of 3 low-callibre cannons, which mean it can shoot 9 cells square";
}
