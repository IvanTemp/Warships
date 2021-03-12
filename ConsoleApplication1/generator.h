#pragma once
#include "Fleet.h"

unsigned int ReturnFieldID(bool side, int x, int y);

unsigned int ReturnFieldIndex(bool side, int x, int y);

void Initialize_Field_Final(bool side);

void Output_Field_Final(const bool side, const bool for_whom);

void Output_Field_ID_Indexes(bool side);

void Output_Field_War(bool side);

void Output_Field_Durability(bool side);

void Field_Refresh_Durability(std::vector<ship> fleet, bool side);

void Field_Get_Vision(const int x, const int y, const bool side);

void Generate_ship(ship sheep, bool side);