#pragma once
#include "Fleet.h"

void OutputAchievementInfo(std::vector<std::pair<std::string, bool>> achievement_vector);

std::vector <std::pair<std::string, bool>> ReadAchievements();

void GiveAchievement(int achivement_plus);

unsigned int ReturnFieldID(bool side, int x, int y);

unsigned int ReturnFieldIndex(bool side, int x, int y);

bool ReturnFieldWar(const bool side, const int x, const int y);

std::string hahaYouAreSmallNow(std::string str);

void Initialize_Field_Final(const Fleet fleet);

void Output_Field_Final_REFORGED(const bool side, std::string name1, std::string name2);

void Output_Field_ID_Indexes(bool side);

void Output_Field_War(bool side);

void Field_Get_Vision(const unsigned int x, const unsigned int y, const bool side);

void Generate_ship(ship sheep, bool side);

std::vector <unsigned int> First_order(Fleet& fleet1, Fleet& fleet2);

std::pair<unsigned int, unsigned int> Return_X_Y(const unsigned int index, const int side);

char IntToLetter(const int Int);

void Small_Move(const unsigned int index, const int side);

void GetDamage(const bool side, const unsigned int x, const unsigned int y, const int dmg, std::vector<ship> &fleet);