#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include "ship.h"
#include "generator.h"
#include "Fleet.h"

int main()
{
	ship ship1("Enterprise", "Aircraft Carrier", 2);
	//Создадим вектор флот
	std::vector<ship> fleet_11;
	//Запихнем в вектор флот наши кораблики
	fleet_11.push_back({ "Enterprise", "Aircraft Carrier", 2 });
	fleet_11.push_back({ "Prinz Eugene", "Heavy Cruiser", 3 });
	fleet_11.push_back({ "Atago", "Heavy Cruiser", 4 });
	fleet_11.push_back({ "FLX1", "Tsundere", 5 });
	fleet_11.push_back({ "FLX2", "Tsundere", 6 });
	fleet_11.push_back({ "FLX3", "Tsundere", 7 });
	fleet_11.push_back({ "Flaffey1", "Small", 8 });
	fleet_11.push_back({ "Flaffey2", "Small", 9 });
	fleet_11.push_back({ "Flaffey3", "Small", 10 });
	fleet_11.push_back({ "Flaffey4", "Small", 11 });
	//Запихнем в вектор флот свои кораблики
	Fleet fleet_1("Eagle Union", fleet_11);



	Fleet fleet_2("Sakura Empire");
	fleet_2.AddshipToFleet({ "Akagi", "Aircraft Carrier", 2 });
	fleet_2.AddshipToFleet({ "SAKURA_NAME1", "Heavy Cruiser", 3 });
	fleet_2.AddshipToFleet({ "SAKURA_NAME2", "Heavy Cruiser", 4 });
	fleet_2.AddshipToFleet({ "SAKURA_NAME3", "Tsundere", 5 });
	fleet_2.AddshipToFleet({ "SAKURA_NAME4", "Tsundere", 6 });
	fleet_2.AddshipToFleet({ "SAKURA_NAME5", "Tsundere", 7 });
	fleet_2.AddshipToFleet({ "Ayanami1", "Small", 8 });
	fleet_2.AddshipToFleet({ "Ayanami2", "Small", 9 });
	fleet_2.AddshipToFleet({ "Ayanami3", "Small", 10 });
	fleet_2.AddshipToFleet({ "Ayanami4", "Small", 11 });
	//fleet_1.Print();
	//fleet_2.Print();

	//Удаление файлов с проверкой выхода за границы
	try
	{
		fleet_1.GetshipByIndex(15).Print();
	}
	catch (std::out_of_range)
	{
		std::cout << "OUT OF RANGE" << std::endl;
	}


	////Generate here
	for (int i = 0; i < 8; i++)
	Generate_ship(fleet_2.GetshipByIndex(i), 0);
	///////////////
	
	//DEBUG FUNCTIONS
	if (DEBUG_MODE) std::cout << "WARNING! DEBUG MODE ON! \n" << std::endl;
	Output_Field_ID_Indexes(0);
	Output_Field_Durability(0);
	Output_Field_War(0);
	Output_Field_ID_Indexes(1);
	Output_Field_Durability(1);
	Output_Field_War(1);
	/////////////////

	//INITIALISATION FIELDS (DO IT AFTER INITIALIZATION OF ALL SHIPS)
	Initialize_Field_Final(0);
	std::cout << std::endl << std::endl;
	Initialize_Field_Final(1);
	///////////////////////

	Output_Field_Final(0);
	std::cout << std::endl << std::endl;
	Output_Field_Final(1);

	return 0;
}