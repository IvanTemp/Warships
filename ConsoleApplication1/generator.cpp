#include <iostream>
#include <locale>
#include <vector>
#include <map>
#include <string>
#include "generator.h"
#include "Fleet.h"

std::string Field_Final[2][width_height][width_height] = { "#", "#", "#" }; //The field seen by the player and the AI
std::pair<unsigned int, unsigned int> Field_ID[2][width_height][width_height] = { std::make_pair(0, 0) }; //The field with ID and indexes
bool Field_War[2][width_height][width_height] = { 0, 0, 0 }; //The field with fog of war

unsigned int ReturnFieldID(const bool side, const int x, const int y)
{
	return Field_ID[side][x][y].first;
}

unsigned int ReturnFieldIndex(const bool side, const int x, const int y)
{
	return Field_ID[side][x][y].second;
}

bool ReturnFieldWar(const bool side, const int x, const int y) {
	return Field_War[side][x][y];
}

std::string hahaYouAreSmallNow(std::string str) {
	std::string small = "abcdefghijklmnopqrstuvwxyz";
	std::string big = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (int i = 0; i < str.length(); i++) {
		for (int j = 0; j < big.length(); j++) {
			if (str[i] == big[j])
				str[i] = small[j];
		}
	}
	return str;
}

void Initialize_Field_Final(const Fleet fleet) {
	for (unsigned int y = 0; y < width_height; y++) {
		for (unsigned int x = 0; x < width_height; x++) {
			if (Field_ID[fleet.GetSide()][x][y].first > 1) {
				Field_Final[fleet.GetSide()][x][y] = std::to_string(fleet.GetShipByIndex(Field_ID[fleet.GetSide()][x][y].first - 2).GetDurability()[Field_ID[fleet.GetSide()][x][y].second]);
			}
			else if (Field_War[fleet.GetSide()][x][y]) {
				Field_Final[fleet.GetSide()][x][y] = "X";
			} else {
				Field_Final[fleet.GetSide()][x][y] = " ";
			}
		}
	}
}

void Output_Field_Final_REFORGED(const bool side, std::string name1, std::string name2) { //TODO —ƒ≈À¿“‹
	std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::map<int, std::string> SideToName = { { 0, name1 }, {1, name2} };
	std::cout << "\tSide: " << SideToName[side] << "\t\tSide: " << SideToName[!side] << std::endl;
	std::cout << "\t ||";
	for (unsigned int x = 0; x < width_height; x++) 
	{
		std::cout << letters[x] << "|";
	}
	std::cout << "\t\t   ";
	for (unsigned int x = 0; x < width_height; x++) 
	{
		std::cout << letters[x] << "|";
	}
	std::cout << std::endl;
	for (unsigned int y = 0; y < width_height; y++)
	{
		std::cout << "\t" << y << "||";
		for (unsigned int x = 0; x < width_height; x++)
		{
			std::cout << Field_Final[side][x][y] << "|";
		}
		std::cout << "\t\t" << y << "||";
		for (unsigned int x = 0; x < width_height; x++)
		{
			if (Field_War[!side][x][y])
			{
				if (Field_ID[!side][x][y].first > 1) { std::cout << Field_Final[!side][x][y] << "|"; }
				else { std::cout << " |"; }
			}
			else
			{
				std::cout << "#" << "|";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Output_Field_ID_Indexes(const bool side) { //DEBUG FUNC
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

void Output_Field_War(const bool side) { //DEBUG FUNC
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

void Field_Get_Vision(const unsigned int x, const unsigned int y, const bool side) {
	Field_War[side][x][y] = 1;
}

void Generate_ship(ship sheep, bool side) {
	std::map <std::string, int> TypeToLength = { {"Aircraft Carrier", 4}, {"Heavy Cruiser", 3}, {"Tsundere", 2}, {"Small", 1} };
	bool stop = false, breaksIn = true;
	int x = 0, y = 0, rotation = 0, length = TypeToLength[sheep.GetType()], ID = sheep.GetID();
	while (!stop) {
		x = rand() % width_height;
		y = rand() % width_height;
		rotation = rand() % 4;
		//TEST YOUR OUTPUT HERE //rotation: 0 - North, 1 - East, 2 - South - 3 - West
		//x = 5; y = 5; rotation = 0;
		if (DEBUG_MODE) {
			std::cout << "[DEBUG INFO]Trying to: x = " << x;
			std::cout << "; y = " << y;
			std::cout << "; rotation = " << rotation;
			std::cout << "; ID: " << ID;
			std::cout << "; Length: " << length;
			std::cout << "; Default durability: " << sheep.GetDurability()[0];
			std::cout << "; Status: ";
		}
		
		std::map <int, int> optimization_map = { {0, -1}, {1, 1}, {2, 1}, {3, -1} };

		int OT = optimization_map[rotation];

		bool breaksIn = true;
		bool leftIsClear = false,
		rightIsClear = false,
		upIsClear = false,
		downIsClear = false;

		//checking for space on all sides
		if (x) {
			leftIsClear = true;
		}

		if (y) {
			upIsClear = true;
		}

		if (x < width_height - 1) {
			rightIsClear = true;
		}

		if (y < width_height - 1) {
			downIsClear = true;
		}
		/////////////////////////////////

		if (rotation == 0 || rotation == 2) { //vertical

			if (length > 1) { //check for the ability to place the ship
				if (OT > 0) {
					if (y + length >= width_height - 1) {
						breaksIn = false;
					}
				}
				else {
					if (y - length < 0) {
						breaksIn = false;
					}
				}
			}

			for (int h = 0; h < length; h++) { //check for the ability to place the ship part 2
				if (Field_ID[side][x][y + h * OT].first > 0) {
					breaksIn = false;
				}
			}

			if (breaksIn) {
				OT > 0 ? breaksIn = upIsClear : breaksIn = downIsClear;
				if (breaksIn) {
					if (leftIsClear) {
						if (Field_ID[side][x - 1][y - 1 * OT].first == 0) {
							Field_ID[side][x - 1][y - 1 * OT].first = 1;
						}
					}

					if (Field_ID[side][x][y - 1 * OT].first == 0) {
						Field_ID[side][x][y - 1 * OT].first = 1;
					}

					if (rightIsClear) {
						if (Field_ID[side][x + 1][y - 1 * OT].first == 0) {
							Field_ID[side][x + 1][y - 1 * OT].first = 1;
						}
					}
				}

				for (int counter = 0; counter < length; counter++) {
					if (leftIsClear) {
						if (Field_ID[side][x - 1][y + counter * OT].first == 0) {
							Field_ID[side][x - 1][y + counter * OT].first = 1;
						}
					}

					Field_ID[side][x][y + counter * OT].first = ID;
					Field_ID[side][x][y + counter * OT].second = counter;

					if (rightIsClear) {
						if (Field_ID[side][x + 1][y + counter * OT].first == 0) {
							Field_ID[side][x + 1][y + counter * OT].first = 1;
						}
					}
				}

				OT > 0 ? breaksIn = downIsClear : breaksIn = upIsClear;
				if (breaksIn) {
					if (leftIsClear) {
						if (Field_ID[side][x - 1][y + length * OT].first == 0) {
							Field_ID[side][x - 1][y + length * OT].first = 1;
						}
					}

					if (Field_ID[side][x][y + length * OT].first == 0) {
						Field_ID[side][x][y + length * OT].first = 1;
					}

					if (rightIsClear) {
						if (Field_ID[side][x + 1][y + length * OT].first == 0) {
							Field_ID[side][x + 1][y + length * OT].first = 1;
						}
					}

				}
				if (DEBUG_MODE) {
					std::cout << "Successfully!" << std::endl;
				}
				stop = true;
			}
		}
		else { //horizontal
			if (length > 1) { //check for the ability to place the ship
				if (OT > 0) {
					if (x + length >= width_height - 1) {
						breaksIn = false;
					}
				}
				else {
					if (x - length < 0) {
						breaksIn = false;
					}
				}
			}

			for (int h = 0; h < length; h++) { //check for the ability to place the ship part 2
				if (Field_ID[side][x + h * OT][y].first > 0) {
					breaksIn = false;
				}
			}

			if (breaksIn) {
				OT > 0 ? breaksIn = leftIsClear : breaksIn = rightIsClear;
				if (breaksIn) {
					if (downIsClear) {
						if (Field_ID[side][x - 1 * OT][y + 1].first == 0) {
							Field_ID[side][x - 1 * OT][y + 1].first = 1;
						}
					}

					if (Field_ID[side][x - 1 * OT][y].first == 0) {
						Field_ID[side][x - 1 * OT][y].first = 1;
					}

					if (upIsClear) {
						if (Field_ID[side][x - 1 * OT][y - 1].first == 0) {
							Field_ID[side][x - 1 * OT][y - 1].first = 1;
						}
					}
				}
				for (int counter = 0; counter < length; counter++) {
					if (upIsClear) {
						if (Field_ID[side][x + counter * OT][y - 1].first == 0) {
							Field_ID[side][x + counter * OT][y - 1].first = 1;
						}
					}

					Field_ID[side][x + counter * OT][y].first = ID;
					Field_ID[side][x + counter * OT][y].second = counter;

					if (downIsClear) {
						if (Field_ID[side][x + counter * OT][y + 1].first == 0) {
							Field_ID[side][x + counter * OT][y + 1].first = 1;
						}
					}
				}

				OT > 0 ? breaksIn = rightIsClear : breaksIn = leftIsClear;
				if (breaksIn) {
					if (downIsClear) {
						if (Field_ID[side][x + length * OT][y + 1].first == 0) {
							Field_ID[side][x + length * OT][y + 1].first = 1;
						}
					}

					if (Field_ID[side][x + length * OT][y].first == 0) {
						Field_ID[side][x + length * OT][y].first = 1;
					}

					if (upIsClear) {
						if (Field_ID[side][x + length * OT][y - 1].first == 0) {
							Field_ID[side][x + length * OT][y - 1].first = 1;
						}
					}
				}
				if (DEBUG_MODE) {
					std::cout << "Successfully!" << std::endl;
				}
				stop = true;
			}
		}
		if (DEBUG_MODE && !stop) {
			std::cout << "Failed!" << std::endl;
		}
	}
}

std::vector <unsigned int> First_order(Fleet &fleet1, Fleet &fleet2) {
	std::vector <unsigned int> orderList;
	bool buleidu = false; //if index hasn't already been

	unsigned int max = std::max(fleet1.GetFleet().size(), fleet2.GetFleet().size());

	for (int i = 0; i < max; i++) {
		buleidu = true;
		unsigned int random_index = rand() % max;
		for (int j = 0; j < orderList.size(); j++) {
			if (random_index == orderList[j]) {
				buleidu = false;
			}
		}
		if (buleidu) {
			orderList.push_back(random_index);
		}
		else {
			i--;
		}
	}

	if (DEBUG_MODE) {
		std::cout << "[DEBUG INFO]Indexes order list:";
		for (int i = 0; i < orderList.size(); i++) {
			std::cout << " " << orderList[i];
		}
		std::cout << std::endl << std::endl;
	}

	return orderList;
}