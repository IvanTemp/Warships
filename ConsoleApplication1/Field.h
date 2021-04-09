#pragma once
#include <string>
#include "Fleet.h"
#include <iostream>
#include <locale>
#include <vector>
#include <map>
#include <fstream>

class Field
{
public:
	void output_achievement_info(const std::vector <std::pair<std::string, bool>>& achievements);
	std::vector <std::pair<std::string, bool>> read_achievements();
	void give_achievement(std::vector <std::pair<std::string, bool>>& achievement_array, const int& num);
	void do_action(Fleet& whose, Fleet& whom, const std::vector<unsigned int>& order, const int& round);
	unsigned int return_field_id_value(const bool& side, const int& x, const int& y);
	unsigned int return_field_index_value(const bool& side, const int& x, const int& y);
	bool return_field_war_value(const bool& side, const int& x, const int& y);
	void ha_you_are_small_now(std::string& str);
	void initialize_field_final(const Fleet& fleet);
	void output_field_final(const bool& side, const std::string& name1, const std::string& name2);
	void output_field_id_indexes(const bool side);
	void output_field_war(const bool side);
	void field_get_vision(const unsigned int x, const unsigned int y, const bool side);
	void generate_ship(const Ship& sheep, const bool side);
	std::vector <unsigned int> first_order(Fleet& fleet1, Fleet& fleet2);
	std::pair <unsigned int, unsigned int> return_x_y(const unsigned int id, const int side);
	char int_to_letter(const int i);
	bool area_is_clear(const bool side, const unsigned int x, const unsigned int y);
	void small_move(const unsigned int index, const int side);
	void get_damage(const bool side, const unsigned int x, const unsigned int y, const int dmg, std::vector <Ship>& fleet);
private:
	std::string field_final[2][width_height][width_height] = { "#", "#", "#" }; //The field seen by the player and the AI
	std::pair<unsigned int, unsigned int> field_id[2][width_height][width_height] = { (std::make_pair(0, 0)) };
	//The field with id_(.first) and indexes(.second)
	bool field_war[2][width_height][width_height] = { (false), (false), (false) }; //The field with fog of war
};

