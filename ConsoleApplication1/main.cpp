#include <string>
#include <vector>
#include <iostream>
#include "generator.h"



int main()
{

	//Получение урона
	//Создадим вектор флот
	std::vector<ship> fleet_1;
	std::vector<ship> fleet_2;
	//Запихнем в вектор флот наши кораблики
	fleet_1.push_back({ "Enterprise", "Aircraft Carrier", 0 });
	fleet_1.push_back({ "Prinz Eugene1", "Heavy Cruiser", 1 });
	fleet_1.push_back({ "Prinz Eugene2", "Heavy Cruiser", 2 });
	fleet_1.push_back({ "FLX1", "Tsundere", 3 });
	fleet_1.push_back({ "FLX2", "Tsundere", 4 });
	fleet_1.push_back({ "FLX3", "Tsundere", 5 });
	fleet_1.push_back({ "Flaffey1", "Small", 6 });
	fleet_1.push_back({ "Flaffey2", "Small", 7 });
	fleet_1.push_back({ "Flaffey3", "Small", 8 });
	fleet_1.push_back({ "Flaffey4", "Small", 9 });
	Generate_ship(fleet_1[0], 1);
	std::cout << std::endl << std::endl << std::endl;
	std::cout << "ID: \n\n";
	Output_Field_ID(0);
	std::cout << std::endl << std::endl << std::endl;
	std::cout << "War: \n\n";
	Output_Field_War(0);
	std::cout << std::endl << std::endl << std::endl;
	std::cout << "Final: \n\n";
	Output_Field_Final(0);
	std::cout << std::endl << std::endl << std::endl;
	//Выведем флот
	std::cout << "======Fleet=======" << std::endl;
	for (const auto& x : fleet_1)
	{
		x.Print();
	}
	return 0;
}