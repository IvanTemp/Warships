#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

void output_achievement_info(const std::vector <std::pair<std::string, bool>>& achievements);
std::vector <std::pair<std::string, bool>> read_achievements();
void give_achievement(std::vector <std::pair<std::string, bool>>& achievement_array, const int& num);
void ha_you_are_small_now(std::string& str);
char int_to_letter(const int i);
std::vector<unsigned int> first_order(const unsigned int count); //count - length of order
bool area_is_clear(auto& field, const bool side, const unsigned int x, const unsigned int y);