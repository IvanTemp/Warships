#pragma once
#include "ship.h"

unsigned int ReturnFieldID(bool side, int x, int y);

unsigned int ReturnFieldIndex(bool side, int x, int y);

void Initialize_Field_Final(bool side);

void Output_Field_ID_Indexes(bool side);

void Output_Field_War(bool side);

void Output_Field_Durability(bool side);

void Field_Refresh_Durability(ship shop, bool side);

void Generate_ship(ship sheep, bool side);

void Output_Field_Final(bool side);