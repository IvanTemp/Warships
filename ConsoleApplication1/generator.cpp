#include <iostream>
#include <locale>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include "generator.h"
#include "fleet.h"

std::string field_final[2][width_height][width_height] = { "#", "#", "#" }; //The field seen by the player and the AI
std::pair<unsigned int, unsigned int> field_id[2][width_height][width_height] = { (std::make_pair(0, 0)) }; //The field with ID(.first) and indexes(.second)
bool field_war[2][width_height][width_height] = { false, false, false }; //The field with fog of war

void output_achievement_info(const std::vector <std::pair<std::string, bool>> achievements) {
	std::cout << "Achievements: " << std::endl;
	for (int i = 0; i < achievements.size(); i++) {
		std::cout << i + 1 << ")" << achievements[i].first << ": ";
		achievements[i].second ? std::cout << "Received\n" : std::cout << "Not received\n";
	}
	std::cout << std::endl;
}

std::vector <std::pair<std::string, bool>> read_achievements() {
	std::vector <std::pair<std::string, bool>> achievement_array;
	//Place your achivements here
	achievement_array.emplace_back(std::make_pair("Win a PVE match on Normal difficulty", 0));
	achievement_array.emplace_back(std::make_pair("Win a PVE match on Hard difficulty", 0));
	achievement_array.emplace_back(std::make_pair("Try to win a PVE match on Impossible difficulty", 0));
	achievement_array.emplace_back(std::make_pair("Play PVP match", 0));
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

void give_achievement(std::vector <std::pair<std::string, bool>> &achievement_array, const int &achv_num) {
	achievement_array[achv_num].second = true;
	for (auto i = 0; i < achievement_array.size(); i++) {
		std::ofstream(achievement_file) << achievement_array[i].second;
	}
	std::ofstream(achievement_file).close();
}

void do_action(Fleet &whose, Fleet &whom, const std::vector<unsigned int> &order, const int &round) {
		if (DEBUG_MODE) { std::cout << "[DEBUG INFO]order[round] = " << order[round] << std::endl; }
		std::cout << "Current position: " << int_to_letter(return_x_y(order[round] + 2, whose.GetSide()).first) << " " << return_x_y(order[round] + 2, whose.GetSide()).second << std::endl;
		std::cout << "Current type: " << whose.GetShipByIndex(order[round]).GetType() << std::endl;
		std::cout << "What do you want?\n\n";
		std::string action;
		while (true) {
		if (whose.GetShipByIndex(order[round]).GetDurabilitySum()) {
			if (whose.GetShipByIndex(order[round]).GetType() == "Small") { //single-deck abilities
				std::cout << "-Shoot\n-Move\n" << std::endl;
				std::cin >> action;
				ha_you_are_small_now(action);
				if (action == "shoot") {
					//Shot
					std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
					if (whom.GetShipByIndex(order[round]).GetType() == "Aircraft Carrier")
					{
						whom.ConsDmgToIndPlayer(Small_Damage*2);
					}
					else
					{
						whom.ConsDmgToIndPlayer(Small_Damage);
					}
					break;
				}
				else if (action == "move") {
					small_move(order[round], whose.GetSide());
					initialize_field_final(whose);
					break;
				}
				else {
					std::cout << "Wrong command!" << std::endl;
					system("pause");
					continue;
				}
			}
			else if (whose.GetShipByIndex(order[round]).GetType() == "Tsundere") {
				std::cout << "-Shoot\n-Repair\n" << std::endl;
				std::cin >> action;
				ha_you_are_small_now(action);
				if (action == "shoot") {
					//Shot
					std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
					if (whom.GetShipByIndex(order[round]).GetType() == "Small")
					{
						whom.GetShipByIndex(order[round]).SetDurability({ 0 });
					}
					else
					{
						whom.ConsDmgToIndPlayer(Tsundere_Damage);
					}
					break;
				}
				else if (action == "repair")
				{
					whose.GetShipByIndex(order[round])++;
					std::cout << "Ship repaired!" << std::endl;
					initialize_field_final(whose);
					break;
				}
				else {
					std::cout << "Wrong command!" << std::endl;
					system("pause");
					continue;
				}
			}
			else if (whose.GetShipByIndex(order[round]).GetType() == "Heavy Cruiser") {
				//Shot
				std::cout << "Point the center where to shoot (Write X and Y coordinates): ";
				whom.ConsDmgHeavyCruiser(Heavy_Cruiser_Damage);
				break;
			}
			else if (whose.GetShipByIndex(order[round]).GetType() == "Aircraft Carrier") {
				ha_you_are_small_now(action);
				std::cout << "Specify the type of attack (1x3 or 3x1): \n" << std::endl;
				std::cin >> action;
				ha_you_are_small_now(action);
				if (action == "1x3" || action == "1") {
					std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
					whom.ConsDmgAircraft(true, Aircraft_Carrier_Damage);
					break;
				}
				else if (action == "3x1" || action == "3") {
					std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
					whom.ConsDmgAircraft(false, Aircraft_Carrier_Damage);
					break;
				} else {
					std::cout << "Wrong command!" << std::endl;
					system("pause");
					continue;
				}
			}
		}
		else {
			std::cout << "This ship is sunk, you miss this turn." << std::endl; // -а в смысле пропуск хода? -Да
			return;
		}
	}
	system("pause");
	if (!DEBUG_MODE) { system("cls"); }
}

unsigned int return_field_id_value(const bool &side, const int &x, const int &y) {
	return field_id[side][x][y].first;
}

unsigned int return_field_index_value(const bool &side, const int &x, const int &y) {
	return field_id[side][x][y].second;
}

bool return_field_war_value(const bool &side, const int &x, const int &y) {
	return field_war[side][x][y];
}

void ha_you_are_small_now(std::string &str) {
	std::string small = "abcdefghijklmnopqrstuvwxyz";
	std::string big = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (int i = 0; i < str.length(); i++) {
		for (int j = 0; j < big.length(); j++) {
			if (str[i] == big[j])
				str[i] = small[j];
		}
	}
}

void initialize_field_final(const Fleet &fleet) {
	for (unsigned int y = 0; y < width_height; y++) {
		for (unsigned int x = 0; x < width_height; x++) {
			if (field_id[fleet.GetSide()][x][y].first > 1) {
				field_final[fleet.GetSide()][x][y] = std::to_string(fleet.GetShipByIndex(field_id[fleet.GetSide()][x][y].first - 2).GetDurability()[field_id[fleet.GetSide()][x][y].second]);
			}
			else if (field_war[fleet.GetSide()][x][y]) {
				field_final[fleet.GetSide()][x][y] = "X";
			} else {
				field_final[fleet.GetSide()][x][y] = " ";
			}
		}
	}
}

void output_field_final(const bool &side, const std::string &name1, const std::string &name2) {
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
			std::cout << field_final[side][x][y] << "|";
		}
		std::cout << "\t\t" << y << "||";
		for (unsigned int x = 0; x < width_height; x++)
		{
			if (field_war[!side][x][y])
			{
				if (field_id[!side][x][y].first > 1) { std::cout << field_final[!side][x][y] << "|"; }
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

void output_field_id_indexes(const bool side) { //DEBUG FUNC
	std::cout << "ID[" << side << "](NOT FOR USER): \n\n";
	for (unsigned int y = 0; y < width_height; y++) {
		std::cout << "         |";
		for (unsigned int x = 0; x < width_height; x++) {
			std::cout << field_id[side][x][y].first << "|";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl << std::endl;
	std::cout << "Indexes[" << side << "](NOT FOR USER): \n\n";
	for (unsigned int y = 0; y < width_height; y++) {
		std::cout << "         |";
		for (unsigned int x = 0; x < width_height; x++) {
			std::cout << field_id[side][x][y].second << "|";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void output_field_war(const bool side) { //DEBUG FUNC
	std::cout << "War[" << side << "](NOT FOR USER): \n\n";
	for (unsigned int y = 0; y < width_height; y++) {
		std::cout << "         |";
		for (unsigned int x = 0; x < width_height; x++) {
			std::cout << field_war[side][x][y] << "|";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void field_get_vision(const unsigned int x, const unsigned int y, const bool side) {
	field_war[side][x][y] = true;
}

void generate_ship(const ship &sheep, bool side) {
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
				if (field_id[side][x][y + h * OT].first > 0) {
					breaksIn = false;
				}
			}

			if (breaksIn) {
				OT > 0 ? breaksIn = upIsClear : breaksIn = downIsClear;
				if (breaksIn) {
					if (leftIsClear) {
						if (field_id[side][x - 1][y - 1 * OT].first == 0) {
							field_id[side][x - 1][y - 1 * OT].first = 1;
						}
					}

					if (field_id[side][x][y - 1 * OT].first == 0) {
						field_id[side][x][y - 1 * OT].first = 1;
					}

					if (rightIsClear) {
						if (field_id[side][x + 1][y - 1 * OT].first == 0) {
							field_id[side][x + 1][y - 1 * OT].first = 1;
						}
					}
				}

				for (int counter = 0; counter < length; counter++) {
					if (leftIsClear) {
						if (field_id[side][x - 1][y + counter * OT].first == 0) {
							field_id[side][x - 1][y + counter * OT].first = 1;
						}
					}

					field_id[side][x][y + counter * OT].first = ID;
					field_id[side][x][y + counter * OT].second = counter;

					if (rightIsClear) {
						if (field_id[side][x + 1][y + counter * OT].first == 0) {
							field_id[side][x + 1][y + counter * OT].first = 1;
						}
					}
				}

				OT > 0 ? breaksIn = downIsClear : breaksIn = upIsClear;
				if (breaksIn) {
					if (leftIsClear) {
						if (field_id[side][x - 1][y + length * OT].first == 0) {
							field_id[side][x - 1][y + length * OT].first = 1;
						}
					}

					if (field_id[side][x][y + length * OT].first == 0) {
						field_id[side][x][y + length * OT].first = 1;
					}

					if (rightIsClear) {
						if (field_id[side][x + 1][y + length * OT].first == 0) {
							field_id[side][x + 1][y + length * OT].first = 1;
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
				if (field_id[side][x + h * OT][y].first > 0) {
					breaksIn = false;
				}
			}

			if (breaksIn) {
				OT > 0 ? breaksIn = leftIsClear : breaksIn = rightIsClear;
				if (breaksIn) {
					if (downIsClear) {
						if (field_id[side][x - 1 * OT][y + 1].first == 0) {
							field_id[side][x - 1 * OT][y + 1].first = 1;
						}
					}

					if (field_id[side][x - 1 * OT][y].first == 0) {
						field_id[side][x - 1 * OT][y].first = 1;
					}

					if (upIsClear) {
						if (field_id[side][x - 1 * OT][y - 1].first == 0) {
							field_id[side][x - 1 * OT][y - 1].first = 1;
						}
					}
				}
				for (int counter = 0; counter < length; counter++) {
					if (upIsClear) {
						if (field_id[side][x + counter * OT][y - 1].first == 0) {
							field_id[side][x + counter * OT][y - 1].first = 1;
						}
					}

					field_id[side][x + counter * OT][y].first = ID;
					field_id[side][x + counter * OT][y].second = counter;

					if (downIsClear) {
						if (field_id[side][x + counter * OT][y + 1].first == 0) {
							field_id[side][x + counter * OT][y + 1].first = 1;
						}
					}
				}

				OT > 0 ? breaksIn = rightIsClear : breaksIn = leftIsClear;
				if (breaksIn) {
					if (downIsClear) {
						if (field_id[side][x + length * OT][y + 1].first == 0) {
							field_id[side][x + length * OT][y + 1].first = 1;
						}
					}

					if (field_id[side][x + length * OT][y].first == 0) {
						field_id[side][x + length * OT][y].first = 1;
					}

					if (upIsClear) {
						if (field_id[side][x + length * OT][y - 1].first == 0) {
							field_id[side][x + length * OT][y - 1].first = 1;
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

std::vector <unsigned int> first_order(Fleet &fleet1, Fleet &fleet2) {
	std::vector <unsigned int> orderList;
	bool buleidu = false; //if index hasn't already been

	const unsigned int max = std::max(fleet1.GetFleet().size(), fleet2.GetFleet().size());

	for (unsigned int i = 0; i < max; i++) {
		buleidu = true;
		const auto random_index = rand() % max;
		for (int j = 0; j < orderList.size(); j++) {
			if (random_index == orderList[j]) {
				buleidu = false;
			}
		}
		if (buleidu) {
			orderList.emplace_back(random_index);
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

std::pair <unsigned int, unsigned int> return_x_y(const unsigned int id, const int side) {
	unsigned int start_x = 0, start_y = 0;
	for (unsigned int y = 0; y < width_height; y++) {
		for (unsigned int x = 0; x < width_height; x++) {
			if (field_id[side][x][y].first == id) {
				start_x = x;
				start_y = y;
				return std::make_pair(start_x, start_y);
			}
		}
	}
	return std::make_pair(start_x, start_y);;
}

char int_to_letter(const int i) {
	std::string alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return alf[i];
}

bool area_is_clear(const bool side, const unsigned int x, const unsigned int y) {
	if (y) {
		if (x) {
			if (field_id[side][x - 1][y - 1].first > 1) return false;
		}
		if (field_id[side][x][y - 1].first > 1) return false;
		if (x < width_height - 1) {
			if (field_id[side][x + 1][y - 1].first > 1) return false;
		}
	}
	if (x) {
		if (field_id[side][x - 1][y].first > 1) return false;
	}
	if (x < width_height - 1) {
		if (field_id[side][x + 1][y].first > 1) return false;
	}
	if (y < width_height - 1) {
		if (x) {
			if (field_id[side][x - 1][y + 1].first > 1) return false;
		}
		if (field_id[side][x][y + 1].first > 1) return false;
		if (x < width_height - 1) {
			if (field_id[side][x + 1][y + 1].first > 1) return false;
		}
	}
	return true;
}

void small_move(const unsigned int index, const int side) {
	int x = 0, y = -1;
	std::cout << "Where are we going? (Write X and Y coordinates): ";
	std::string alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char strx;
	std::cin >> strx >> y;
	if (DEBUG_MODE) std::cout << "[Move small]X = " << strx << "; Y = " << y << std::endl;

	if (y > width_height) {
		std::cout << "Captain! Are you trying to steer the ship out of the battlefield?\n" << std::endl;
		system("pause");
		small_move(index, side);
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
			small_move(index, side);
			return;
		}
	}

	std::pair <unsigned int, unsigned int> start = return_x_y(index + 2, side);

	if (DEBUG_MODE) {
		std::cout << "[Move small]Start X = " << start.first << "; Start Y = " << start.second << std::endl;
		std::cout << "[Move small]X = " << x << "; Y = " << y << std::endl;
		std::cout << "[Move small]shift: " << start.first - x << " " << start.second - y << " " << std::endl;
	}

	if ((start.first - x <= 1 || start.first - x >= UINT_MAX - 1) && (start.second - y <= 1 || start.second - y >= UINT_MAX - 1)) {
		field_id[side][start.first][start.second].first = 0;
		if (area_is_clear(side, x, y)) {
			if (start.second) {
				if (start.first) {
					if (area_is_clear(side, start.first - 1, start.second - 1)) field_id[side][start.first - 1][start.second - 1].first = 0;
				}
				if (area_is_clear(side, start.first, start.second - 1)) field_id[side][start.first][start.second - 1].first = 0;
				if (start.first < width_height) {
					if (area_is_clear(side, start.first + 1, start.second - 1)) field_id[side][start.first + 1][start.second - 1].first = 0;
				}
			}
			if (start.first) {
				if (area_is_clear(side, start.first - 1, start.second)) field_id[side][start.first - 1][start.second].first = 0;
			}
			if (start.first < width_height - 1) {
				if (area_is_clear(side, start.first + 1, start.second)) field_id[side][start.first + 1][start.second].first = 0;
			}
			if (start.second < width_height - 1) {
				if (start.first) {
					if (area_is_clear(side, start.first - 1, start.second + 1)) field_id[side][start.first - 1][start.second + 1].first = 0;
				}
				if (area_is_clear(side, start.first, start.second + 1)) field_id[side][start.first][start.second + 1].first = 0;
				if (start.first < width_height - 1) {
					if (area_is_clear(side, start.first + 1, start.second + 1)) field_id[side][start.first + 1][start.second + 1].first = 0;
				}
			}

			if (y) {
				if (x) {
					field_id[side][x - 1][y - 1].first = 1;
				}
				field_id[side][x][y - 1].first = 1;
				if (x < width_height) {
					field_id[side][x + 1][y - 1].first = 1;
				}
			}
			if (x) {
				field_id[side][x - 1][y].first = 1;
			}
			if (x < width_height - 1) {
				field_id[side][x + 1][y].first = 1;
			}
			if (y < width_height - 1) {
				if (x) {
					field_id[side][x - 1][y + 1].first = 1;
				}
				field_id[side][x][y + 1].first = 1;
				if (x < width_height - 1) {
					field_id[side][x + 1][y + 1].first = 1;
				}
			}

			field_id[side][x][y].first = index + 2;
		}
		else {
			field_id[side][start.first][start.second].first = index + 2;
			std::cout << "Captain! This square is already taken!\n" << std::endl;
			system("pause");
			small_move(index, side);
			return;
		}
	}
	else {
		field_id[side][start.first][start.second].first = index + 2;
		std::cout << "Captain! This is not a <<Meteor>> for you, a single-decker can only move one square.\n" << std::endl;
		system("pause");
		small_move(index, side);
		return;
	}
	std::cout << "Complete!\n\n";
}

void get_damage(const bool side, const unsigned int x, const unsigned int y, const int dmg, std::vector <ship> &fleet) {
	std::string alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int index = field_id[side][x][y].first - 2;
	fleet[index].DmgtoInd(dmg, field_id[side][x][y].second);
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
				if (return_field_id_value(side, x, y) == index + 2) {
					coords.emplace_back(std::make_pair(x, y));
				}
			}
		}
		fleet[index].Klee(coords, side);
	}
}