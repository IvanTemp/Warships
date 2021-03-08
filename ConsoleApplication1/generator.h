#pragma once
#include "ship.h"

//Настройки игры
#define width_height 10 //Ширина высота поля

void Output_Field_Final(bool side);

void Output_Field_ID(bool side);

void Output_Field_War(bool side);

void Generate_ships_in_random_places(ship sheep, bool side);
