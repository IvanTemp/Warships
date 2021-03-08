#include <string>
#include <vector>
#include <iostream>
#include "ship.h"
#include "generator.h"



int main()
{

	//Получение урона
	//Создадим вектор флот
	std::vector<ship> fleet; //TODO - СДЕЛАТЬ TUPLE
	//Запихнем в вектор флот наши кораблики
	fleet.push_back({ "Enterprise", "Aircraft Carrier", 0 });
	fleet.push_back({ "Prinz Eugene1", "Heavy Cruiser", 1 });
	fleet.push_back({ "Prinz Eugene2", "Heavy Cruiser", 2 });
	fleet.push_back({ "FLX1", "Tsundere", 3 });
	fleet.push_back({ "FLX2", "Tsundere", 4 });
	fleet.push_back({ "FLX3", "Tsundere", 5 });
	fleet.push_back({ "Flaffey1", "Small", 6 });
	fleet.push_back({ "Flaffey2", "Small", 7 });
	fleet.push_back({ "Flaffey3", "Small", 8 });
	fleet.push_back({ "Flaffey4", "Small", 9 });
	Generate_ships_in_random_places(fleet[0], 1);
	std::cout << std::endl << std::endl << std::endl;
	std::cout << "ID: \n\n";
	Output_Field_ID(1);
	std::cout << std::endl << std::endl << std::endl;
	std::cout << "War: \n\n";
	Output_Field_War(1);
	std::cout << std::endl << std::endl << std::endl;
	std::cout << "Final: \n\n";
	Output_Field_Final(1);
	std::cout << std::endl << std::endl << std::endl;
	//Выведем флот
	std::cout << "======Fleet=======" << std::endl;
	for (const auto& x : fleet)
	{
		x.Print();
	}
	system("pause");
	return 0;
}