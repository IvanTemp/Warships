#include <string>
#include <vector>
#include <iostream>
#include "generator.h"

void PrintFleet(std::vector<ship> fleet321)
{
	std::cout << "=====Fleet=====" << std::endl;
	for (int i = 0; i < fleet321.size(); i++)
	{
		fleet321[i].Print();
	}
}

int main()
{

	//Получение урона
	//Создадим вектор флот
	std::vector<ship> fleet_1;
	std::vector<ship> fleet_2;
	//Запихнем в вектор флот наши кораблики
	fleet_1.push_back({ "Enterprise", "Aircraft Carrier", 1 });
	fleet_1.push_back({ "Prinz Eugene1", "Heavy Cruiser", 2 });
	fleet_1.push_back({ "Prinz Eugene2", "Heavy Cruiser", 3 });
	fleet_1.push_back({ "FLX1", "Tsundere", 4 });
	fleet_1.push_back({ "FLX2", "Tsundere", 5 });
	fleet_1.push_back({ "FLX3", "Tsundere", 6 });
	fleet_1.push_back({ "Flaffey1", "Small", 7 });
	fleet_1.push_back({ "Flaffey2", "Small", 8 });
	fleet_1.push_back({ "Flaffey3", "Small", 9 });
	fleet_1.push_back({ "Flaffey4", "Small", 10 });
	Generate_ship(fleet_1[0], 0);
	std::cout << std::endl << std::endl << std::endl;
	Output_Field_ID(0);
	std::cout << std::endl << std::endl << std::endl;
	Output_Field_War(0);
	std::cout << std::endl << std::endl << std::endl;
	Output_Field_Durability(0);
	std::cout << std::endl << std::endl << std::endl;
	Generate_Field_Final(0);
	std::cout << std::endl << std::endl << std::endl;
	Output_Field_Final(0);
	//Выведем флот
	PrintFleet(fleet_1);
	return 0;
}