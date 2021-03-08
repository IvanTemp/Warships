#include <iostream>
#include <locale>
#include <vector>
#include <map>
#include "generator.h"

std::tuple <int, int> Field_Final[width_height][width_height] = { std::make_tuple(0, 0) }; //Поля, которое видит игрок и Терминатор
std::tuple <int, int> Field_ID[width_height][width_height] = { std::make_tuple(0, 0) }; //Поля с ID
std::tuple <bool, bool> Field_War[width_height][width_height] = { std::make_tuple(0, 0) }; //Поля с туманом войны

void Output_Field_Final(bool side) { //ДОДЕЛАТЬ
	std::map <int, char> OutputMap = { {0, '#' }, {1, ' '}, {2, '*'}, {3, 'U'}, {4, 'L'}, {5, 'R'}, {6, 'D'} };
	for (int y = 0; y < width_height; y++) {
		std::cout << "         |";
		for (int x = 0; x < width_height; x++) {
			if (side) {
				if (std::get<0>(Field_War[x][y]) && std::get<0>(Field_ID[x][y]) > 0) {
					std::cout << "          |";
				}
			}
			else {
				if (std::get<1>(Field_War[x][y]) && std::get<1>(Field_ID[x][y]) > 0) {
					std::cout << "          |";
				}
			}
		}
		std::cout << std::endl;
	}
}

void Output_Field_ID(bool side) {
	for (int y = 0; y < width_height; y++) {
		std::cout << "         |";
		for (int x = 0; x < width_height; x++) {
			side ? std::cout << std::get<1>(Field_ID[x][y]) << "|" : std::cout << std::get<0>(Field_ID[x][y]) << "|";
		}
		std::cout << std::endl;
	}
}

void Output_Field_War(bool side) {
	for (int y = 0; y < width_height; y++) {
		std::cout << "         |";
		for (int x = 0; x < width_height; x++) {
			side ? std::cout << std::get<1>(Field_War[x][y]) << "|" : std::cout << std::get<1>(Field_War[x][y]) << "|";
		}
		std::cout << std::endl;
	}
}


void Generate_ships_in_random_places(ship sheep, bool side) {
	srand(time(0));
	std::map <std::string, int> TypeToLength = { {"Aircraft Carrier", 4}, {"Heavy Cruiser", 3}, {"Tsundere", 2}, {"Small", 1} };
	bool stop = false, breaksIn = true, kostil = true;
	int x = 0, y = 0, rotation = 0, length = TypeToLength[sheep.GetType()], ID = sheep.GetID();
	//rotation: 0 - North, 1 - East, 2 - South - 3 - West
	while (!stop) {
		breaksIn = true;
		x = -1 + rand() % width_height + 1, y = -1 + rand() % width_height + 1, rotation = 2;
		std::cout << "x = " << x << " y = " << y << " rotation = " << rotation << " ID: " << ID << std::endl; //TEST
		switch (rotation) {
		case 2: //South
			if (y < width_height - length) {
				for (int h = 0; h < length; h++) {
					if (side) {
						if (std::get<1>(Field_ID[x][y + h]) != 0) breaksIn = false;
					}
					else {
						if (std::get<0>(Field_ID[x][y + h]) != 0) breaksIn = false;
					}
				}
				if (breaksIn) {
					if (y > 0) {
						if (side) {
							std::get<1>(Field_ID[x - 1][y - 1]) != 1 ? kostil = true : kostil = false;
						}
						else {
							std::get<0>(Field_ID[x - 1][y - 1]) != 1 ? kostil = true : kostil = false;
						}
						if (x > 0 && kostil) {
							side ? std::get<1>(Field_ID[x - 1][y - 1]) = 3 : std::get<0>(Field_ID[x - 1][y - 1]) = 3;
							side ? std::get<1>(Field_War[x - 1][y - 1]) = 1 : std::get<0>(Field_ID[x - 1][y - 1]) = 3;
						}
						side ? std::get<1>(Field_ID[x][y - 1]) = 3 : std::get<1>(Field_ID[x][y - 1]) = 3;
						side ? std::get<1>(Field_War[x][y - 1]) = 1 : std::get<0>(Field_War[x][y - 1]) = 1;
						if (side) {
							std::get<1>(Field_ID[x + 1][y - 1]) != 1 ? kostil = true : kostil = false;
						}
						else {
							std::get<0>(Field_ID[x + 1][y - 1]) != 1 ? kostil = true : kostil = false;
						}
						if (x < width_height - 1 && kostil) {
							side ? std::get<1>(Field_ID[x + 1][y - 1]) = 3 : std::get<0>(Field_ID[x + 1][y - 1]) = 3;
							side ? std::get<1>(Field_War[x + 1][y - 1]) = 1 : std::get<0>(Field_War[x + 1][y - 1]) = 1;
						}
					}
					for (int temp_int = 0; temp_int < length; temp_int++) {
						if (side) {
							std::get<1>(Field_ID[x - 1][y + temp_int]) != 1 ? kostil = true : kostil = false;
						}
						else {
							std::get<0>(Field_ID[x - 1][y + temp_int]) != 1 ? kostil = true : kostil = false;
						}
						if (x > 0 && kostil) {
							side ? std::get<1>(Field_ID[x - 1][y + temp_int]) = 4 : std::get<0>(Field_ID[x - 1][y + temp_int]) = 4;
							side ? std::get<1>(Field_War[x - 1][y + temp_int]) = 1 : std::get<0>(Field_War[x - 1][y + temp_int]) = 1;
						}
						side ? std::get<1>(Field_ID[x][y + temp_int]) = ID : std::get<0>(Field_ID[x][y + temp_int]) = ID;
						side ? std::get<1>(Field_War[x][y + temp_int]) = 1 : std::get<0>(Field_War[x][y + temp_int]) = 1;
						if (side) {
							std::get<1>(Field_ID[x + 1][y + temp_int]) != 1 ? kostil = true : kostil = false;
						}
						else {
							std::get<0>(Field_ID[x + 1][y + temp_int]) != 1 ? kostil = true : kostil = false;
						}
						if (x < width_height - 1 && kostil) {
							side ? std::get<1>(Field_ID[x + 1][y + temp_int]) = 5 : std::get<0>(Field_ID[x + 1][y + temp_int]) = 5;
							side ? std::get<1>(Field_War[x + 1][y + temp_int]) = 1 : std::get<0>(Field_War[x + 1][y + temp_int]) = 1;
						}
					}
					if (y < width_height - 1) {
						if (side) {
							std::get<1>(Field_ID[x - 1][y + length]) != 1 ? kostil = true : kostil = false;
						}
						else {
							std::get<0>(Field_ID[x - 1][y + length]) != 1 ? kostil = true : kostil = false;
						}
						if (x > 0 && kostil) {
							side ? std::get<1>(Field_ID[x - 1][y + length]) = 6 : std::get<0>(Field_ID[x - 1][y + length]) = 6;
							side ? std::get<1>(Field_War[x - 1][y + length]) = 1 : std::get<0>(Field_War[x - 1][y + length]);
						}
						side ? std::get<1>(Field_ID[x][y + length]) = 6 : std::get<0>(Field_ID[x][y + length]) = 6;
						side ? std::get<1>(Field_War[x][y + length]) = 1 : std::get<0>(Field_War[x][y + length]) = 1;
						if (side) {
							std::get<1>(Field_ID[x + 1][y + length]) != 1 ? kostil = true : kostil = false;
						}
						else {
							std::get<0>(Field_ID[x + 1][y + length]) != 1 ? kostil = true : kostil = false;
						}
						if (x < width_height - 1 && kostil) {
							side ? std::get<1>(Field_ID[x + 1][y + length]) = 6 : std::get<0>(Field_ID[x + 1][y + length]) = 6;
							side ? std::get<1>(Field_War[x + 1][y + length]) = 1 : std::get<0>(Field_War[x + 1][y + length]) = 1;
						}
					}
					stop++;
				}
				else continue;
			}
			else continue;
			break;
		}
	}
}