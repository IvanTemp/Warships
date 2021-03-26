#pragma once
#include "fleet.h"

void OutputAchievementInfo(const std::vector<std::pair<std::string, bool>> achievement_array);

std::vector<std::pair<std::string, bool>> ReadAchievements();

void GiveAchievement(std::vector<std::pair<std::string, bool>>& achievement_array, const int achivement_plus);

void DoAction(Fleet& whose, Fleet& whom, const std::vector<unsigned int>& order, const int& round);

void Output_Field_War(const bool side);

void Field_Get_Vision(const unsigned int x, const unsigned int y, const bool side);

void Generate_ship(ship sheep, bool side);

std::vector<unsigned int> First_order(Fleet& fleet1, Fleet& fleet2);

std::pair<unsigned int, unsigned int> Return_X_Y(const unsigned int ID, const int side);

char IntToLetter(const int i);

void Small_Move(const unsigned int index, const int side);

void GetDamage(const bool side, const unsigned int x, const unsigned int y, const int dmg, std::vector<ship>& fleet);

unsigned int Return_Field_ID_Value(const bool side, const int x, const int y);

unsigned int Return_Field_Index_Value(const bool side, const int x, const int y);

bool Return_Field_War_Value(const bool side, const int x, const int y);

void hahaYouAreSmallNow(std::string& str);

void Initialize_Field_Final(const Fleet fleet);

void Output_Field_Final_REFORGED(const bool side, const std::string name1, const std::string name2);

void Output_Field_ID_Indexes(const bool side);