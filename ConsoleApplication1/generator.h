#pragma once
#include "Fleet.h"

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
