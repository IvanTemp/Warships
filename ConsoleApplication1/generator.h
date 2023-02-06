#pragma once
#include "fleet.h"

void generate_ship(const ship& sheep, const bool side);

void get_damage(const bool side, const unsigned int x, const unsigned int y, const int dmg, std::vector <ship>& fleet);