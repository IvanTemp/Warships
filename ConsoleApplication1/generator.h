#pragma once
#include "Fleet.h"

unsigned int ReturnFieldID(bool side, int x, int y);

unsigned int ReturnFieldIndex(bool side, int x, int y);

bool ReturnFieldWar(const bool side, const int x, const int y);

unsigned int ReturnFieldDurability(const bool side, const int x, const int y);

std::string hahaYouAreSmallNow(std::string str);

void Initialize_Field_Final(bool side);

void Output_Field_Final(const bool side, const bool for_whom);

void Pepsi_Output_Field_Final(const bool side);

void Output_Field_ID_Indexes(bool side);

void Output_Field_War(bool side);

void Output_Field_Durability(bool side);

void Field_Refresh_Durability_REFORGED(Fleet flet);

void Field_Get_Vision(const int x, const int y, const bool side);

void Generate_ship(ship sheep, bool side);