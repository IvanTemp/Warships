#include <iostream>
#include <locale>
#include <vector>
#include <map>
#include "generator.h"


std::pair <int, int> temp;
temp.first() = 0;
temp.second() = 0;
std::pair <int, int> Field_Final[width_height][width_height] = { temp }; //Поля с ID
std::pair <int, int> Field_ID[width_height][width_height] = { temp }; //Поля с ID
std::pair <int, int> Field_War[width_height][width_height] = { temp }; //Поля с туманом войны

void Output_Field() {

	std::map <int, char> OutputMap = { {0, '#' }, {1, ' '}, {2, '*'}, {3, 'U'}, {4, 'L'}, {5, 'R'}, {6, 'D'} };
	for (int y = 0; y < width_height; y++) {
		std::cout << "         |";
		for (int x = 0; x < width_height; x++) {
			std::cout << OutputMap[Field_ID[x][y]] << "|";
		}
		std::cout << std::endl;
	}
}


void Generate_ships_in_random_places(ship sheep) {
	srand(time(0));
	std::map <std::string, int> TypeToLength = { {"Aircraft Carrier", 4}, {"Heavy Cruiser", 3}, {"Tsundere", 2}, {"Small", 1} };
	std::map <std::string, int> TypeToDurability = { {"Aircraft Carrier", 4}, {"Heavy Cruiser", 3}, {"Tsundere", 2}, {"Small", 1} };
	bool stop = false, breaksIn = true;
	int x = 0, y = 0, rotation = 0, length = TypeToLength[sheep.GetType()];
	//rotation: 0 - North, 1 - East, 2 - South - 3 - West
	while (!stop) {
		breaksIn = true;
		x = -1 + rand() % width_height + 1, y = -1 + rand() % width_height + 1, rotation = 2;
		std::cout << "x = " << x << " y = " << y << " rotation = " << rotation << std::endl; //TEST
		switch (rotation) {
		case 2: //South
			if (y < width_height - length) {
				for (int h = 0; h < length; h++) {
					if (Field_ID[x][y + h] != 0) breaksIn = false;
				}
				if (breaksIn) {
					if (y > 0) {
						if (x > 0 && Field_ID[x - 1][y - 1] != 1) Field_ID[x - 1][y - 1] = 3;
						Field_ID[x][y - 1] = 3;
						if (x < width_height - 1 && Field_ID[x + 1][y - 1] != 1) Field_ID[x + 1][y - 1] = 3;
					}
					for (int temp_int = 0; temp_int < length; temp_int++) {
						if (x > 0 && Field_ID[x - 1][y + temp_int] != 1) Field_ID[x - 1][y + temp_int] = 4;
						Field_ID[x][y + temp_int] = 1;
						if (x < width_height - 1 && Field_ID[x + 1][y + temp_int] != 1) Field_ID[x + 1][y + temp_int] = 5;
					}
					if (y < width_height - 1) {
						if (x > 0 && Field_ID[x - 1][y + length] != 1) Field_ID[x - 1][y + length] = 6;
						Field_ID[x][y + length] = 6;
						if (x < width_height - 1 && Field_ID[x + 1][y + length] != 1) Field_ID[x + 1][y + length] = 6;
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