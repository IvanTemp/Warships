#include <iostream>
#include <locale>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include "generator.h"
#include "fleet.h"

std::string Field_Final[2][width_height][width_height] = { "#", "#", "#" }; //The field seen by the player and the AI
std::pair<unsigned int, unsigned int> Field_ID[2][width_height][width_height] = { std::make_pair(0, 0) }; //The field with ID and indexes
bool Field_War[2][width_height][width_height] = { 0, 0, 0 }; //The field with fog of war

void OutputAchievementInfo(std::vector <std::pair<std::string, bool>> achievement_array) {
	std::cout << "Achievements: " << std::endl;
	for (int i = 0; i < achievement_array.size(); i++) {
		std::cout << i + 1 << ")" << achievement_array[i].first << ": ";
		achievement_array[i].second ? std::cout << "Received\n" : std::cout << "Not received\n";
	}
	std::cout << std::endl;
}

std::vector <std::pair<std::string, bool>> ReadAchievements() {
	std::vector <std::pair<std::string, bool>> achievement_array;
	//Place your achivements here
	achievement_array.push_back(std::make_pair("Win a PVE match on Normal difficulty", 0));
	achievement_array.push_back(std::make_pair("Win a PVE match on Hard difficulty", 0));
	achievement_array.push_back(std::make_pair("Try to win a PVE match on Impossible difficulty", 0));
	achievement_array.push_back(std::make_pair("Play PVP match", 0));
	/////////////////////////////
	std::ofstream nekostil(achievement_file, std::ios::in | std::ios::out | std::ios::app | std::ios::binary | std::ios::ate);
	nekostil.close();
	std::ifstream achivIn(achievement_file);
	std::string strin = "";
	getline(achivIn, strin);
	for (int i = 0; i < strin.length(); i++) {
		strin[i] == '1' ? achievement_array[i].second = 1 : achievement_array[i].second = 0;
	}
	achivIn.close();
	std::ofstream achivOut(achievement_file);
	for (int i = 0; i < achievement_array.size(); i++) {
		achivOut << achievement_array[i].second;

	}
	achivOut.close();
	return achievement_array;
}

void GiveAchievement(std::vector <std::pair<std::string, bool>> &achievement_array, int achivement_plus) {
	achievement_array[achivement_plus].second = true;
	std::ofstream achivOut(achievement_file);
	for (int i = 0; i < achievement_array.size(); i++) {
		achivOut << achievement_array[i].second;
	}
	achivOut.close();
}

void DoAction(Fleet &whose, Fleet &whom, std::vector<unsigned int> &order, int &round, int &first) {
		if (DEBUG_MODE) { std::cout << "[DEBUG INFO]order[round] = " << order[round] << std::endl; }
		std::cout << "Current position: " << IntToLetter(Return_X_Y(order[round] + 2, first % 2).first) << " " << Return_X_Y(order[round] + 2, first % 2).second << std::endl;
		std::cout << "What do you want?\n\n";
		std::string action = "";
		while (true) { //IN DEVELOPMENT
		if (whose.GetShipByIndex(order[round]).GetDurabilitySum()) {
			if (whose.GetShipByIndex(order[round]).GetType() == "Small") { //single-deck abilities
				std::cout << "-Shoot\n-Move\n" << std::endl;
				std::cin >> action;
				action = hahaYouAreSmallNow(action);
				if (action == "shoot") {
					//Shot
					std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
					whom.ConsDmgToIndPlayer(Small_Damage);
					break;
				}
				else if (action == "move") {
					Small_Move(order[round], whose.GetSide());
					Initialize_Field_Final(whose);
					break;
				}
				else {
					std::cout << "Wrong command!" << std::endl;
					system("pause");
					continue;
				}
			}
			else if (whose.GetShipByIndex(order[round]).GetType() == "Tsundere") {
				std::cout << "-Shoot\n" << std::endl;
				std::cin >> action;
				action = hahaYouAreSmallNow(action);
				if (action == "shoot") {
					//Shot
					std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
					whom.ConsDmgToIndPlayer(Tsundere_Damage);
					break;
				}
				else {
					std::cout << "Wrong command!" << std::endl;
					system("pause");
					continue;
				}
			}
			else if (whose.GetShipByIndex(order[round]).GetType() == "Heavy Cruiser") {
				std::cout << "-Shoot\n" << std::endl;
				std::cin >> action;
				action = hahaYouAreSmallNow(action);
				if (action == "shoot") {
					//Shot
					std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
					whom.ConsDmgToIndPlayer(Heavy_Cruiser_Damage);
					break;
				}
				else {
					std::cout << "Wrong command!" << std::endl;
					system("pause");
					continue;
				}
			}
			else if (whose.GetShipByIndex(order[round]).GetType() == "Aircraft Carrier") {
				std::cout << "-Shoot\n" << std::endl;
				std::cin >> action;
				action = hahaYouAreSmallNow(action);
				if (action == "shoot") {
					//Shot
					std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
					whom.ConsDmgToIndPlayer(Aircraft_Carrier_Damage);
					break;
				}
				else {
					std::cout << "Wrong command!" << std::endl;
					system("pause");
					continue;
				}
			}
			else {
				std::cout << "ERROR! Unknown type of ship! Please contact the team leader, he will make sure that Vanya gets into a corner for poor testing. Get into a waiting pose if you don't want to miss the party." << std::endl;
				system("pause");
				return;
			}
		}
		else {
			std::cout << "This ship is sunk, you miss this turn." << std::endl;
			return;
		}
	}
	system("pause");
	if (!DEBUG_MODE) { system("cls"); }
	first++;
}

unsigned int ReturnFieldID(const bool side, const int x, const int y) {
	return Field_ID[side][x][y].first;
}

unsigned int ReturnFieldIndex(const bool side, const int x, const int y) {
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

void Output_Field_Final_REFORGED(const bool side, const std::string name1, const std::string name2) {
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
			std::cout << "[Generator]Trying to: x = " << x;
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

	for (unsigned int i = 0; i < max; i++) {
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

std::pair <unsigned int, unsigned int> Return_X_Y(const unsigned int ID, const int side) {
	unsigned int start_x = 0, start_y = 0;
	for (unsigned int y = 0; y < width_height; y++) {
		for (unsigned int x = 0; x < width_height; x++) {
			if (Field_ID[side][x][y].first == ID) {
				start_x = x;
				start_y = y;
				return std::make_pair(start_x, start_y);
			}
		}
	}
	return std::make_pair(start_x, start_y);;
}

char IntToLetter(const int Int) {
	std::string alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return alf[Int];
}

bool AreaIsClear(const bool side, const unsigned int x, const unsigned int y) {
	if (y) {
		if (x) {
			if (Field_ID[side][x - 1][y - 1].first > 1) return false;
		}
		if (Field_ID[side][x][y - 1].first > 1) return false;
		if (x < width_height - 1) {
			if (Field_ID[side][x + 1][y - 1].first > 1) return false;
		}
	}
	if (x) {
		if (Field_ID[side][x - 1][y].first > 1) return false;
	}
	if (x < width_height - 1) {
		if (Field_ID[side][x + 1][y].first > 1) return false;
	}
	if (y < width_height - 1) {
		if (x) {
			if (Field_ID[side][x - 1][y + 1].first > 1) return false;
		}
		if (Field_ID[side][x][y + 1].first > 1) return false;
		if (x < width_height - 1) {
			if (Field_ID[side][x + 1][y + 1].first > 1) return false;
		}
	}
	return true;
}

void Small_Move(const unsigned int index, const int side) {
	int x = 0, y = -1;
	std::cout << "Where are we going? (Write X and Y coordinates): ";
	std::string alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char strx;
	std::cin >> strx >> y;
	if (DEBUG_MODE) std::cout << "[Move small]X = " << strx << "; Y = " << y << std::endl;

	if (y > width_height) {
		std::cout << "Captain! Are you trying to steer the ship out of the battlefield?\n" << std::endl;
		system("pause");
		Small_Move(index, side);
		return;
	}
	strx = std::toupper(strx);
	for (int i = 0; i < width_height; i++) {
		if (alf[i] == strx) {
			x = i;
			break;
		}
		if (i == width_height - 1) {
			std::cout << "Captain! Are you trying to steer the ship out of the battlefield?\n" << std::endl;
			system("pause");
			Small_Move(index, side);
			return;
		}
	}

	std::pair <unsigned int, unsigned int> start = Return_X_Y(index + 2, side);

	if (DEBUG_MODE) {
		std::cout << "[Move small]Start X = " << start.first << "; Start Y = " << start.second << std::endl;
		std::cout << "[Move small]X = " << x << "; Y = " << y << std::endl;
		std::cout << "[Move small]shift: " << start.first - x << " " << start.second - y << " " << std::endl;
	}

	if ((start.first - x <= 1 || start.first - x >= UINT_MAX - 1) && (start.second - y <= 1 || start.second - y >= UINT_MAX - 1)) {
		Field_ID[side][start.first][start.second].first = 0;
		if (AreaIsClear(side, x, y)) {
			if (start.second) {
				if (start.first) {
					if (AreaIsClear(side, start.first - 1, start.second - 1)) Field_ID[side][start.first - 1][start.second - 1].first = 0;
				}
				if (AreaIsClear(side, start.first, start.second - 1)) Field_ID[side][start.first][start.second - 1].first = 0;
				if (start.first < width_height) {
					if (AreaIsClear(side, start.first + 1, start.second - 1)) Field_ID[side][start.first + 1][start.second - 1].first = 0;
				}
			}
			if (start.first) {
				if (AreaIsClear(side, start.first - 1, start.second)) Field_ID[side][start.first - 1][start.second].first = 0;
			}
			if (start.first < width_height - 1) {
				if (AreaIsClear(side, start.first + 1, start.second)) Field_ID[side][start.first + 1][start.second].first = 0;
			}
			if (start.second < width_height - 1) {
				if (start.first) {
					if (AreaIsClear(side, start.first - 1, start.second + 1)) Field_ID[side][start.first - 1][start.second + 1].first = 0;
				}
				if (AreaIsClear(side, start.first, start.second + 1)) Field_ID[side][start.first][start.second + 1].first = 0;
				if (start.first < width_height - 1) {
					if (AreaIsClear(side, start.first + 1, start.second + 1)) Field_ID[side][start.first + 1][start.second + 1].first = 0;
				}
			}

			if (y) {
				if (x) {
					Field_ID[side][x - 1][y - 1].first = 1;
				}
				Field_ID[side][x][y - 1].first = 1;
				if (x < width_height) {
					Field_ID[side][x + 1][y - 1].first = 1;
				}
			}
			if (x) {
				Field_ID[side][x - 1][y].first = 1;
			}
			if (x < width_height - 1) {
				Field_ID[side][x + 1][y].first = 1;
			}
			if (y < width_height - 1) {
				if (x) {
					Field_ID[side][x - 1][y + 1].first = 1;
				}
				Field_ID[side][x][y + 1].first = 1;
				if (x < width_height - 1) {
					Field_ID[side][x + 1][y + 1].first = 1;
				}
			}

			Field_ID[side][x][y].first = index + 2;
		}
		else {
			Field_ID[side][start.first][start.second].first = index + 2;
			std::cout << "Captain! This square is already taken!\n" << std::endl;
			system("pause");
			Small_Move(index, side);
			return;
		}
	}
	else {
		Field_ID[side][start.first][start.second].first = index + 2;
		std::cout << "Captain! This is not a <<Meteor>> for you, a single-decker can only move one square.\n" << std::endl;
		system("pause");
		Small_Move(index, side);
		return;
	}
	std::cout << "Complete!\n\n";
}

void GetDamage(const bool side, const unsigned int x, const unsigned int y, const int dmg, std::vector <ship> &fleet) {
	std::string alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int index = Field_ID[side][x][y].first - 2;
	fleet[index].DmgtoInd(dmg, Field_ID[side][x][y].second);
	std::cout << "Dodge this! You are hit!" << std::endl;
	std::cout << "You hit him in " << alf[x] << " " << y << std::endl;

	std::vector <std::pair<unsigned int, unsigned int>> coords;

	if (DEBUG_MODE) {
		std::cout << "[DEBUG INFO]Ship name: " << fleet[index].GetName();
		std::cout << "; new durability =";

		for (int i = 0; i < fleet[index].GetDurability().size(); i++) {
			std::cout << " " << fleet[index].GetDurability()[i];
		}

		std::cout << std::endl;
	}

	if (!fleet[index].GetDurabilitySum()) {
		for (int x = 0; x < width_height; x++) {
			for (int y = 0; y < width_height; y++) {
				if (ReturnFieldID(side, x, y) == index + 2) {
					coords.push_back(std::make_pair(x, y));
				}
			}
		}
		fleet[index].Klee(coords, side);
	}
}