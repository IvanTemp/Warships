#include <string>
#include <vector>
#include <iostream>
#include "ship.h"
#include "generator.h"



int main()
{

	Generate_ships_in_random_places(1, 1, 1, 1);
	std::cout << std::endl << std::endl << std::endl;
	Output_Field();
	std::cout << std::endl << std::endl << std::endl;

	//Получение урона
	//Создадим вектор флот
	std::vector<ship> fleet;
	//Запихнем в вектор флот наши кораблики
	fleet.push_back({ "Enterprise", "Aircraft Carrier" });
	fleet.push_back({ "Prinz Eugene1", "Heavy Cruiser" });
	fleet.push_back({ "Prinz Eugene2", "Heavy Cruiser" });
	fleet.push_back({ "FLX1", "Tsundere" });
	fleet.push_back({ "FLX2", "Tsundere" });
	fleet.push_back({ "FLX3", "Tsundere" });
	fleet.push_back({ "Flaffey1", "Small" });
	fleet.push_back({ "Flaffey2", "Small" });
	fleet.push_back({ "Flaffey3", "Small" });
	fleet.push_back({ "Flaffey4", "Small" });
	//Выведем флот
	std::cout << "======Fleet=======" << std::endl;
	for (const auto& x : fleet)
	{
		x.Print();
	}
	return 0;
}