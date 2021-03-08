#include <iostream>
#include <locale>
#include <vector>
#include <map>
#include "generator.h"

int Field[width_height][width_height] = { 0 }; //Поле

void Output_Field() {

	std::map <int, char> OutputMap = { {2, '*'}, {1, ' '}, {0, '#' } };
	for (int y = 0; y < width_height; y++) {
		std::cout << "         |";
		for (int x = 0; x < width_height; x++) {
			std::cout << OutputMap[Field[x][y]] << "|";
		}
		std::cout << std::endl;
	}
}


void Generate_ships_in_random_places(ship sheep) {
	srand(time(0));
	bool stop = false, breaksIn = true;
	int x = 0, y = 0, rotation = 0, length = 0;
	if (sheep.GetType() == "Aircraft Carrier") {
		length = 4;
	}
	//rotation: 0 - North, 1 - East, 2 - South - 3 - West
	while (!stop) {
		breaksIn = true;
		x = -1 + rand() % width_height + 1, y = -1 + rand() % width_height + 1, rotation = 2;
		std::cout << "x = " << x << " y = " << y << " rotation = " << rotation << std::endl; //TEST
		switch (rotation) {
		case 2: //South
			if (y < width_height - length) {
				for (int h = 0; h < length; h++) {
					if (Field[x][y + h] != 0) breaksIn = false;
				}
				if (breaksIn) {
					if (y > 0) {
						if (x > 0 && Field[x - 1][y - 1] != 1) Field[x - 1][y - 1] = 2;
						Field[x][y - 1] = 2;
						if (x < width_height - 1 && Field[x + 1][y - 1] != 1) Field[x + 1][y - 1] = 2;
					}
					for (int temp_int = 0; temp_int < length; temp_int++) {
						if (x > 0 && Field[x - 1][y + temp_int] != 1) Field[x - 1][y + temp_int] = 2;
						Field[x][y + temp_int] = 1;
						if (x < width_height - 1 && Field[x + 1][y + temp_int] != 1) Field[x + 1][y + temp_int] = 2;
					}
					if (y < width_height - 1) {
						if (x > 0 && Field[x - 1][y + length] != 1) Field[x - 1][y + length] = 2;
						Field[x][y + length] = 2;
						if (x < width_height - 1 && Field[x + 1][y + length] != 1) Field[x + 1][y + length] = 2;
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