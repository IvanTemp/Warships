#include <iostream>
#include <locale>
#include <vector>
#include <map>
#include <string>
#include "generator.h"

std::map <std::string, std::string> design = { {"Unknown", "#"}, {"Clear", " "} };

std::string Field_Final[2][width_height][width_height] = { design["Unknown"], design["Unknown"], design["Unknown"] }; //The field seen by the player and the AI
std::pair<unsigned int, unsigned int> Field_ID[2][width_height][width_height] = { std::make_pair(0, 0) }; //The field with ID and indexes
bool Field_War[2][width_height][width_height] = { 0, 0, 0 }; //The field with fog of war
unsigned int Field_Durability[2][width_height][width_height] = { 0, 0, 0 }; //The field with durability

unsigned int ReturnFieldID(const bool side, int x, int y)
{
	return Field_ID[side][x][y].first;
}

unsigned int ReturnFieldIndex(const bool side, int x, int y)
{
	return Field_ID[side][x][y].second;
}

void Initialize_Field_Final(const bool side) {
	for (unsigned int y = 0; y < width_height; y++) {
		for (unsigned int x = 0; x < width_height; x++) {
			if (Field_ID[side][x][y].first > 1) {
				Field_Final[side][x][y] = std::to_string(Field_Durability[side][x][y]);
			}
			else {
				Field_Final[side][x][y] = design["Clear"];
			}
		}
	}
}

void Output_Field_Final(const bool side, const bool for_whom) {
	std::cout << "Final[" << side << "] for [" << for_whom << "]: \n\n";
			if (side != for_whom) {
				for (unsigned int y = 0; y < width_height; y++) {
					std::cout << "         |";
					for (unsigned int x = 0; x < width_height; x++) {
						if (Field_War[side][x][y]) { std::cout << Field_Final[side][x][y] << "|"; }
						else { std::cout << design["Unknown"] << "|"; }
					}
					std::cout << std::endl;
				}
			}
			else {
				for (unsigned int y = 0; y < width_height; y++) {
					std::cout << "         |";
					for (unsigned int x = 0; x < width_height; x++) {
						std::cout << Field_Final[side][x][y] << "|";
					}
					std::cout << std::endl;

				}
			}
			std::cout << std::endl;
}

void Output_Field_ID_Indexes(const bool side) {
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

void Output_Field_War(const bool side) {
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

void Output_Field_Durability(const bool side) {
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

void Field_Refresh_Durability(std::vector<ship> fleet, const bool side) {
	for (unsigned int y = 0; y < width_height; y++) {
		for (unsigned int x = 0; x < width_height; x++) {
			std::cout << x << " " << y << " " << Field_ID[side][x][y].second << " " << Field_ID[side][x][y].first - 2 << std::endl;
			if (Field_ID[side][x][y].first > 1) { Field_Durability[side][x][y] = fleet[Field_ID[side][x][y].first - 2].GetDurability()[Field_ID[side][x][y].second]; }
		}
	}
	Initialize_Field_Final(side);
}

void Field_Get_Vision(const int x, const int y, const bool side) { Field_War[side][x][y] = 1; }

void Generate_ship(ship sheep, bool side) {
	std::map <std::string, int> TypeToLength = { {"Aircraft Carrier", 4}, {"Heavy Cruiser", 3}, {"Tsundere", 2}, {"Small", 1} };
	bool stop = false, breaksIn = true, kostil = true;
	int x = 0, y = 0, rotation = 0, length = TypeToLength[sheep.GetType()], ID = sheep.GetID();
	while (!stop) {
		x = -1 + rand() % width_height + 1; y = -1 + rand() % width_height + 1, rotation = - 1 + rand() % 4 + 1;
		//TEST YOUR OUTPUT HERE //rotation: 0 - North, 1 - East, 2 - South - 3 - West
		//x = 5; y = 5; rotation = 0;
		if (DEBUG_MODE) std::cout << "Trying to: x = " << x << "; y = " << y << "; rotation = " << rotation << "; ID: " << ID << "; Length: " << length << "; Default durability: " << sheep.GetDurability()[0] << "; Status: ";

		std::map <int, int> optimization_map = { {0, -1}, {1, 1}, {2, 1}, {3, -1} };
		int OT = optimization_map[rotation];
		bool breaksIn = true;
		bool leftIsClear = false, rightIsClear = false, upIsClear = false, downIsClear = false;
		if (x) { leftIsClear = true; } if (y) { upIsClear = true; } if (x < width_height - 1) { rightIsClear = true; } if (y < width_height - 1) { downIsClear = true; } //checking for space on all sides
		if (rotation == 0 || rotation == 2) { //vertical
			if (length > 1) {
				if (OT > 0) { if (y + length >= width_height - 1) { breaksIn = false; } }
				else { if (y - length < 0) { breaksIn = false; } } //check for the ability to place the ship
			}
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
					Field_Durability[side][x][y + counter * OT] = sheep.GetDurability()[counter];
					if (rightIsClear) { if (Field_ID[side][x + 1][y + counter * OT].first == 0) { Field_ID[side][x + 1][y + counter * OT].first = 1; } }
				}
				OT > 0 ? breaksIn = downIsClear : breaksIn = upIsClear;
				if (breaksIn) {
					if (leftIsClear) { if (Field_ID[side][x - 1][y + length * OT].first == 0) { Field_ID[side][x - 1][y + length * OT].first = 1; } }
					if (Field_ID[side][x][y + length * OT].first == 0) { Field_ID[side][x][y + length * OT].first = 1; }
					if (rightIsClear) { if (Field_ID[side][x + 1][y + length * OT].first == 0) { Field_ID[side][x + 1][y + length * OT].first = 1; } }
				}
				if (DEBUG_MODE) { std::cout << "Successfully!" << std::endl; }
				stop = true;
			}
		}
		else { //horizontal
			if (length > 1) {
				if (OT > 0) { if (x + length >= width_height - 1) { breaksIn = false; } }
				else { if (x - length < 0) { breaksIn = false; } } //check for the ability to place the ship
			}
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
					Field_Durability[side][x + counter * OT][y] = sheep.GetDurability()[counter];
					if (downIsClear) { if (Field_ID[side][x + counter * OT][y + 1].first == 0) { Field_ID[side][x + counter * OT][y + 1].first = 1; } }
				}
				OT > 0 ? breaksIn = rightIsClear : breaksIn = leftIsClear;
				if (breaksIn) {
					if (downIsClear) { if (Field_ID[side][x + length * OT][y + 1].first == 0) { Field_ID[side][x + length * OT][y + 1].first = 1; } }
					if (Field_ID[side][x + length * OT][y].first == 0) { Field_ID[side][x + length * OT][y].first = 1; }
					if (upIsClear) { if (Field_ID[side][x + length * OT][y - 1].first == 0) { Field_ID[side][x + length * OT][y - 1].first = 1; } }
				}
				if (DEBUG_MODE) { std::cout << "Successfully!" << std::endl; }
				stop = true;
			}
		}
		if (DEBUG_MODE && !stop) { std::cout << "Failed!" << std::endl; }
	}
}