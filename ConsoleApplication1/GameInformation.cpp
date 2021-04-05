#include <iostream>
#include <map>
#include <fstream>
#include "GameInformation.h"
#include "Small.h"
#include "ship.h"

GameInformation::GameInformation()
{
}

void output_achievement_info(const std::vector<std::pair<std::string, bool>>& achievements)
{
	std::cout << "Achievements: " << std::endl;
	for (unsigned int i = 0; i < achievements.size(); i++)
	{
		std::cout << i + 1 << ")" << achievements[i].first << ": ";
		achievements[i].second ? std::cout << "Received\n" : std::cout << "Not received\n";
	}
	std::cout << std::endl;
}

std::vector<std::pair<std::string, bool>> read_achievements_from_file()
{
	std::vector<std::pair<std::string, bool>> achievement_array;
	//Place your achievements here
	achievement_array.emplace_back(std::make_pair("Win a PVE match on Normal difficulty", 0));
	achievement_array.emplace_back(std::make_pair("Win a PVE match on Hard difficulty", 0));
	achievement_array.emplace_back(std::make_pair("Try to win a PVE match on Impossible difficulty", 0));
	achievement_array.emplace_back(std::make_pair("Play PVP match", 0));
	/////////////////////////////
	std::ofstream file_creation(
		achievement_file, std::ios::in | std::ios::out | std::ios::app | std::ios::binary | std::ios::ate);
	file_creation.close();
	std::ifstream file_reading(achievement_file);
	std::string str;
	getline(file_reading, str);
	for (auto& i : str)
	{
		i == '1' ? achievement_array[i].second = true : achievement_array[i].second = false;
	}
	file_reading.close();
	std::ofstream file_filling(achievement_file);
	for (auto& i : achievement_array)
	{
		file_filling << i.second;
	}
	file_filling.close();
	return achievement_array;
}

void give_achievement(std::vector<std::pair<std::string, bool>>& achievement_array, const int& num)
{
	achievement_array[num].second = true;
	std::ofstream out(achievement_file);
	for (unsigned int i = 0; i < achievement_array.size(); i++)
	{
		out << achievement_array[i].second;
	}
	out.close();
}

auto GameInformation::return_field_final() const {
	return &field_final_;
}

auto GameInformation::return_field_id() const {
	return &field_id_;
}

auto GameInformation::return_field_war() const{
	return &field_war_;
}

void GameInformation::set_field_id(const bool side, const unsigned int x, const unsigned int y, const unsigned int value) {
	field_id_[side][x][y].first = value;
}

void GameInformation::set_field_indexes(const bool side, const unsigned int x, const unsigned int y, const unsigned int value) {
	field_id_[side][x][y].first = value;
}

void GameInformation::set_field_war(const bool side, const unsigned int x, const unsigned int y, const unsigned int value) {
	field_id_[side][x][y].first = value;
}

void GameInformation::ha_you_are_small_now(std::string& str) {
	std::string small = "abcdefghijklmnopqrstuvwxyz";
	std::string big = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (int i = 0; i < str.length(); i++)
	{
		for (int j = 0; j < big.length(); j++)
		{
			if (str[i] == big[j])
				str[i] = small[j];
		}
	}
}

char GameInformation::int_to_letter(const int i) {
	std::string alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return alf[i];
}

void GameInformation::do_action(Fleet& whose, Fleet& whom, const std::vector<unsigned int>& order, const int& round) {
	if (debug_mode_) { std::cout << "[DEBUG INFO]order[round] = " << order[round] << std::endl; }
	std::cout << "Current position: " << int_to_letter(whose.get_ship_vector()[order[round]].get_coordinates().first) << " " <<
		whose.get_ship_vector()[order[round]].get_coordinates().second << std::endl;
	std::cout << "Current type: " << whose.get_ship_by_index(order[round]).get_type()->get_name() << std::endl;
	std::cout << "What do you want?\n\n";
	std::string action;
	while (true)
	{
		if (whose.get_ship_by_index(order[round]).get_durability_sum())
		{
			if (whose.get_ship_by_index(order[round]).get_type()->get_name() == "Small")
			{
				//single-deck abilities
				std::cout << "-Shoot\n-Move\n" << std::endl;
				std::cin >> action;
				ha_you_are_small_now(action);
				if (action == "shoot")
				{
					//Shot
					whom.damage_by_index_player(whose.get_ship_by_index(order[round]));
					break;
				}
				if (action == "move_small")
				{
					whose.get_ship_by_index(order[round]).get_type()->move_small();
					initialize_field_final(whose);
					break;
				}
				std::cout << "Wrong command!" << std::endl;
				system("pause");
				continue;
			}
			if (whose.get_ship_by_index(order[round]).get_type()->get_name() == "Tsundere")
			{
				std::cout << "-Shoot\n-Repair\n" << std::endl;
				std::cin >> action;
				ha_you_are_small_now(action);
				if (action == "shoot")
				{
					whom.damage_by_index_player(whose.get_ship_by_index(order[round]));
					break;
				}
				if (action == "repair")
				{
					whose.get_ship_by_index(order[round])++;
					std::cout << "Ship repaired!" << std::endl;
					initialize_field_final(whose);
					break;
				}
				std::cout << "Wrong command!" << std::endl;
				system("pause");
				continue;
			}
			if (whose.get_ship_by_index(order[round]).get_type()->get_name() == "Heavy Cruiser")
			{
				//Shot
				std::cout << "Point the center where to shoot (Write X and Y coordinates): ";
				whom.heavy_cruiser_attack(whose.get_ship_by_index(order[round]).get_type()->get_damage_value());
				break;
			}
			if (whose.get_ship_by_index(order[round]).get_type()->get_name() == "Aircraft Carrier")
			{
				ha_you_are_small_now(action);
				std::cout << "Specify the type of attack (1x3 or 3x1): \n" << std::endl;
				std::cin >> action;
				ha_you_are_small_now(action);
				if (action == "1x3" || action == "1")
				{
					whom.aircraft_attack(true, whose.get_ship_by_index(order[round]).get_type()->get_damage_value());
					break;
				}
				if (action == "3x1" || action == "3")
				{
					whom.aircraft_attack(false, whose.get_ship_by_index(order[round]).get_type()->get_damage_value());
					break;
				}
				std::cout << "Wrong command!" << std::endl;
				system("pause");
			}
		}
		else
		{
			std::cout << "This ship is sunk, you miss this turn." << std::endl; // -а в смысле пропуск хода? -Да
			return;
		}
	}
	system("pause");
	if (!debug_mode_) { system("cls"); }
}

void GameInformation::field_get_vision(const unsigned int x, const unsigned int y, const bool side) {
	field_war_[side][x][y] = true;
}

void GameInformation::initialize_field_final(const Fleet& fleet) {
	for (unsigned int y = 0; y < width_height; y++)
	{
		for (unsigned int x = 0; x < width_height; x++)
		{
			if (field_id_[fleet.get_side()][x][y].first > 1)
			{
				field_final_[fleet.get_side()][x][y] = std::to_string(
					fleet.get_ship_by_index(field_id_[fleet.get_side()][x][y].first - 2).get_durability()[field_id_[fleet.get_side()][x][y].second]);
			}
			else if (field_war_[fleet.get_side()][x][y])
			{
				field_final_[fleet.get_side()][x][y] = "X";
			}
			else
			{
				field_final_[fleet.get_side()][x][y] = " ";
			}
		}
	}
}

void GameInformation::output_field_final(const bool& side, const std::string& name1, const std::string& name2) {
	std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::map<int, std::string> SideToName = { {0, name1}, {1, name2} };
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
			std::cout << field_final_[side][x][y] << "|";
		}
		std::cout << "\t\t" << y << "||";
		for (unsigned int x = 0; x < width_height; x++)
		{
			if (field_war_[!side][x][y])
			{
				if (field_id_[!side][x][y].first > 1) { std::cout << field_final_[!side][x][y] << "|"; }
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

void GameInformation::output_field_id_indexes(const bool side) const {
		std::cout << "id_[" << side << "](NOT FOR USER): \n\n";
		for (unsigned int y = 0; y < width_height; y++)
		{
			std::cout << "         |";
			for (unsigned int x = 0; x < width_height; x++)
			{
				std::cout << field_id_[side][x][y].first << "|";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl << std::endl << std::endl;
		std::cout << "Indexes[" << side << "](NOT FOR USER): \n\n";
		for (unsigned int y = 0; y < width_height; y++)
		{
			std::cout << "         |";
			for (unsigned int x = 0; x < width_height; x++)
			{
				std::cout << field_id_[side][x][y].second << "|";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
}

void GameInformation::output_field_war(const bool side) const {
	//DEBUG FUNC
	std::cout << "War[" << side << "](NOT FOR USER): \n\n";
	for (unsigned int y = 0; y < width_height; y++)
	{
		std::cout << "         |";
		for (unsigned int x = 0; x < width_height; x++)
		{
			std::cout << field_war_[side][x][y] << "|";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

std::vector<unsigned int> GameInformation::first_order(Fleet& fleet1, Fleet& fleet2)const {
	std::vector<unsigned int> orderList;
	bool stopper = true; //if index hasn't already been

	const unsigned int max = std::max(fleet1.get_ship_vector().size(), fleet2.get_ship_vector().size());

	unsigned int random_index = 0;

	for (unsigned int i = 0; i < max; i++)
	{
		stopper = true;
		random_index = rand() % max;
		for (auto& j : orderList)
		{
			if (random_index == j)
			{
				stopper = false;
			}
		}
		if (stopper)
		{
			orderList.emplace_back(random_index);
		}
		else
		{
			i--;
		}
	}

	if (debug_mode_)
	{
		std::cout << "[DEBUG INFO]Indexes order list:";
		for (auto& i : orderList)
		{
			std::cout << " " << i;
		}
		std::cout << std::endl << std::endl;
	}

	return orderList;
}

bool GameInformation::get_debug_mode() const {
	return debug_mode_;
}
