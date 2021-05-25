﻿#include "Leviathan.h"
#include <iostream>


int Leviathan::get_size() const {
	return 5;
}

int Leviathan::get_damage_value() const {
	return 999;
}

int Leviathan::get_default_durability() const {
	return 666;
}

void Leviathan::print_commands() const {
	std::cout << "⣼⣿⣿⡇⢔\n-⢕⢕⢽⢸⢟⢟⢖⢖⢤⣶⡟⢻⣿⡿⠻⣿⣿⡟⢀⣿⣦⢤⢤⢔⢞⢿⢿⣿⠁⢕\n-⢕⢕⠅⣐⢕⢕⢕⢕⢕⣿⣿⡄⠛⢀⣦⠈⠛⢁⣼⣿⢗⢕⢕⢕⢕⢕⢕⡏⣘⢕\n-⢕⢕⠅⢓⣕⣕⣕⣕⣵⣿⣿⣿⣾⣿⣿⣿⣿⣿⣿⣿⣷⣕⢕⢕⢕⢕⡵⢀⢕⢕\n-⢑⢕⠃⡈⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢃⢕⢕⢕" << std::endl << std::endl;
}

std::string Leviathan::get_description() const {
	return "?????????????????????????????????????????????????";
}