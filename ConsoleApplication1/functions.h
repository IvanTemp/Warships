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

int letter_to_int(const char chr);

int difference_modulus(int first, int second);

std::vector<int> first_order(const size_t count);

const std::pair<int, int> load_settings();