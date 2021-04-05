#pragma once
#include <string>
#include "fleet.h"

#define width_height 10 //Width & height of field

class GameInformation {
public:
	GameInformation();
	void output_achievement_info(const std::vector<std::pair<std::string, bool>>& achievements);
	std::vector<std::pair<std::string, bool>> read_achievements_from_file();
	void give_achievement(std::vector<std::pair<std::string, bool>>& achievement_array, const int& num);
	auto return_field_final() const;
	auto return_field_id() const;
	auto return_field_war() const;
	void ha_you_are_small_now(std::string& str);
	char int_to_letter(const int i);
	void do_action(Fleet& whose, Fleet& whom, const std::vector<unsigned int>& order, const int& round);
	void field_get_vision(const unsigned int x, const unsigned int y, const bool side);
	void initialize_field_final(const Fleet& fleet);
	void output_field_final(const bool& side, const std::string& name1, const std::string& name2);
	void output_field_id_indexes(const bool side) const;
	void output_field_war(const bool side)const;
	std::vector<unsigned int> first_order(Fleet& fleet1, Fleet& fleet2)const;
	bool get_debug_mode()const;
private:
	std::string field_final_[2][width_height][width_height] = { "#", "#", "#" }; //The field seen by the player and the AI
	std::pair<unsigned int, unsigned int> field_id_[2][width_height][width_height] = { (std::make_pair(0, 0)) }; //The field with id_(.first) and indexes(.second)
	bool field_war_[2][width_height][width_height] = { (false), (false), (false) }; //The field with fog of war
	const bool debug_mode_ = true;
};