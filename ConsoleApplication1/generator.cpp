#include <iostream>
#include <locale>
#include <vector>
#include <map>
#include <string>
#include "generator.h"



std::map <std::string, std::string> design = { {"Unknown", "#"}, {"Clear", " "} };

std::string Field_Final[2][width_height][width_height] = { design["Unknown"], design["Unknown"], design["Unknown"] }; //Поля, которое видит игрок и Терминатор
std::pair<unsigned int, unsigned int> Field_ID[2][width_height][width_height] = { std::make_pair(0, 0) }; //Поля с ID
bool Field_War[2][width_height][width_height] = { 0, 0, 0 }; //Поля с туманом войны
unsigned int Field_Durability[2][width_height][width_height] = { 0, 0, 0 }; //Поля с прочностью

void Initialize_Field_Final(bool side) {
	for (unsigned int y = 0; y < width_height; y++) {
		for (unsigned int x = 0; x < width_height; x++) {
			if (!side || DEBUG_MODE) {
				if (Field_ID[side][x][y].first > 1) {
					Field_Final[side][x][y] = std::to_string(Field_Durability[side][x][y]);
				}
				else {
					Field_Final[side][x][y] = design["Clear"];
				}
			}
			else {
				Field_Final[side][x][y] = design["Unknown"];
			}
		}
	}
}

void Output_Field_Final(bool side) {
	std::cout << "Final[" << side << "] \n\n";
	for (unsigned int y = 0; y < width_height; y++) {
		std::cout << "         |";
		for (unsigned int x = 0; x < width_height; x++) {
			std::cout << Field_Final[side][x][y] << "|";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Output_Field_ID_Indexes(bool side) {
	if (DEBUG_MODE) {
		std::cout << "ID[" << side << "](NOT FOR USER): \n\n";
		for (unsigned int y = 0; y < width_height; y++) {
			std::cout << "         |";
			for (unsigned int x = 0; x < width_height; x++) {
				std::cout << Field_ID[side][x][y].first << "|";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl << std::endl << std::endl;
		std::cout << "Indexes[" << side << "](NOT FOR USER): \n\n";
		for (unsigned int y = 0; y < width_height; y++) {
			std::cout << "         |";
			for (unsigned int x = 0; x < width_height; x++) {
				std::cout << Field_ID[side][x][y].second << "|";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

void Output_Field_War(bool side) {
	if (DEBUG_MODE) {
		std::cout << "War[" << side << "](NOT FOR USER): \n\n";
		for (unsigned int y = 0; y < width_height; y++) {
			std::cout << "         |";
			for (unsigned int x = 0; x < width_height; x++) {
				std::cout << Field_War[side][x][y] << "|";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

void Output_Field_Durability(bool side) {
	if (DEBUG_MODE) {
		std::cout << "Durability[" << side << "](NOT FOR USER): \n\n";
		for (unsigned int y = 0; y < width_height; y++) {
			std::cout << "         |";
			for (unsigned int x = 0; x < width_height; x++) {
				std::cout << Field_Durability[side][x][y] << "|";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

void Field_Refresh(ship shop, bool side) {
	for (unsigned int y = 0; y < width_height; y++) {
		for (unsigned int x = 0; x < width_height; x++) {
			if (Field_ID[side][x][y].first > 1) { Field_Durability[side][x][y] = shop.GetDurability()[Field_ID[side][x][y].second]; }
		}
	}
	Initialize_Field_Final(side);
}

void Generate_ship(ship sheep, bool side) {
	srand(time(0));
	std::map <std::string, int> TypeToLength = { {"Aircraft Carrier", 4}, {"Heavy Cruiser", 3}, {"Tsundere", 2}, {"Small", 1} };
	bool stop = false, breaksIn = true, kostil = true;
	int x = 0, y = 0, rotation = 0, length = TypeToLength[sheep.GetType()], ID = sheep.GetID();
	unsigned int durability = sheep.GetDurability()[0];
	//rotation: 0 - North, 1 - East, 2 - South - 3 - West
	while (!stop) {
		x = -1 + rand() % width_height + 1; y = -1 + rand() % width_height + 1, rotation = - 1 + rand() % 4 + 1;
		
		//TEST YOUR OUTPUT
		//x = 9;
		//y = 9;
		//rotation = 0;
		if (DEBUG_MODE) std::cout << "x = " << x << " y = " << y << " rotation = " << rotation << " ID: " << ID << " Durability: " << durability << std::endl; //TEST

		std::map <int, int> optimization_map = { {0, -1}, {1, 1}, {2, 1}, {3, -1} };
		int OT = optimization_map[rotation];
		bool breaksIn = true;
		bool leftIsClear = false, rightIsClear = false, upIsClear = false, downIsClear = false;
		if (x) { leftIsClear = true; } if (y) { upIsClear = true; } if (x < width_height - 1) { rightIsClear = true; } if (y < width_height - 1) { downIsClear = true; } //checking for space on all sides
		if (rotation == 0 || rotation == 2) { //vertical
			if (OT > 0) { if (y + length >= width_height - 1) { breaksIn = false; } } else { if (y - length < 0) { breaksIn = false; } } //check for the ability to place the ship
			for (int h = 0; h < length; h++) { if (Field_ID[side][x][y + h * OT].first > 0) { breaksIn = false; } } //check for the ability to place the ship part 2
			if (breaksIn) {
				OT > 0 ? breaksIn = upIsClear : breaksIn = downIsClear;
				if (breaksIn) {
					if (leftIsClear) { if (Field_ID[side][x - 1][y - 1 * OT].first == 0) { Field_ID[side][x - 1][y - 1 * OT].first = 1; } }
					if (Field_ID[side][x][y - 1 * OT].first == 0) { Field_ID[side][x][y - 1 * OT].first = 1; }
					if (rightIsClear) { if (Field_ID[side][x + 1][y - 1 * OT].first == 0) { Field_ID[side][x + 1][y - 1 * OT].first = 1; } }
				}
				for (int counter = 0; counter < length; counter++) {
					if (leftIsClear) { if (Field_ID[side][x - 1][y + counter * OT].first == 0) { Field_ID[side][x - 1][y + counter * OT].first = 1; } }
					Field_ID[side][x][y + counter * OT].first = ID;
					Field_ID[side][x][y + counter * OT].second = counter;
					Field_Durability[side][x][y + counter * OT] = durability;
					if (rightIsClear) { if (Field_ID[side][x + 1][y + counter * OT].first == 0) { Field_ID[side][x + 1][y + counter * OT].first = 1; } }
				}
				OT > 0 ? breaksIn = downIsClear : breaksIn = upIsClear;
				if (breaksIn) {
					if (leftIsClear) { if (Field_ID[side][x - 1][y + length * OT].first == 0) { Field_ID[side][x - 1][y + length * OT].first = 1; } }
					if (Field_ID[side][x][y + length * OT].first == 0) { Field_ID[side][x][y + length * OT].first = 1; }
					if (rightIsClear) { if (Field_ID[side][x + 1][y + length * OT].first == 0) { Field_ID[side][x + 1][y + length * OT].first = 1; } }
				}
				stop = true;
			}
		}
		else { //horizontal
			if (OT > 0) { if (x + length >= width_height - 1) { breaksIn = false; } }
			else { if (x - length < 0) { breaksIn = false; } } //check for the ability to place the ship
			for (int h = 0; h < length; h++) { if (Field_ID[side][x + h * OT][y].first > 0) { breaksIn = false; } } //check for the ability to place the ship part 2
			if (breaksIn) {
				OT > 0 ? breaksIn = leftIsClear : breaksIn = rightIsClear;
				if (breaksIn) {
					if (downIsClear) { if (Field_ID[side][x - 1 * OT][y + 1].first == 0) { Field_ID[side][x - 1 * OT][y + 1].first = 1; } }
					if (Field_ID[side][x - 1 * OT][y].first == 0) { Field_ID[side][x - 1 * OT][y].first = 1; }
					if (upIsClear) { if (Field_ID[side][x - 1 * OT][y - 1].first == 0) { Field_ID[side][x - 1 * OT][y - 1].first = 1; } }
				}
				for (int counter = 0; counter < length; counter++) {
					if (upIsClear) { if (Field_ID[side][x + counter * OT][y - 1].first == 0) { Field_ID[side][x + counter * OT][y - 1].first = 1; } }
					Field_ID[side][x + counter * OT][y].first = ID;
					Field_ID[side][x + counter * OT][y].second = counter;
					Field_Durability[side][x + counter * OT][y] = durability;
					if (downIsClear) { if (Field_ID[side][x + counter * OT][y + 1].first == 0) { Field_ID[side][x + counter * OT][y + 1].first = 1; } }
				}
				OT > 0 ? breaksIn = rightIsClear : breaksIn = leftIsClear;
				if (breaksIn) {
					if (downIsClear) { if (Field_ID[side][x + length * OT][y + 1].first == 0) { Field_ID[side][x + length * OT][y + 1].first = 1; } }
					if (Field_ID[side][x + length * OT][y].first == 0) { Field_ID[side][x + length * OT][y].first = 1; }
					if (upIsClear) { if (Field_ID[side][x + length * OT][y - 1].first == 0) { Field_ID[side][x + length * OT][y - 1].first = 1; } }
				}
				stop = true;
			}
		}
	}
}