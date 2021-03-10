#include <string>
#include <vector>
#include <iostream>
#include "ship.h"
#include "generator.h"

//void PrintFleet(std::vector<ship> fleet321)
//{
//	std::cout << "=====Fleet======" << std::endl;
//	for (int i = 0; i < fleet321.size(); i++)
//	{
//		fleet321[i].Print();
//	}
//}

int main()
{

	////Создадим вектор флот
	//std::vector<ship> fleet_1;
	//std::vector<ship> fleet_2;
	////Запихнем в вектор флот наши кораблики
	//fleet_1.push_back({ "Enterprise", "Aircraft Carrier", 2 });
	//fleet_1.push_back({ "Prinz Eugene", "Heavy Cruiser", 3 });
	//fleet_1.push_back({ "Atago", "Heavy Cruiser", 4 });
	//fleet_1.push_back({ "FLX1", "Tsundere", 5 });
	//fleet_1.push_back({ "FLX2", "Tsundere", 6 });
	//fleet_1.push_back({ "FLX3", "Tsundere", 7 });
	//fleet_1.push_back({ "Flaffey1", "Small", 8 });
	//fleet_1.push_back({ "Flaffey2", "Small", 9 });
	//fleet_1.push_back({ "Flaffey3", "Small", 10 });
	//fleet_1.push_back({ "Flaffey4", "Small", 11 });

	////Запихнем в вектор флот вражеские кораблики
	//fleet_2.push_back({ "Akagi", "Aircraft Carrier", 2 });
	//fleet_2.push_back({ "SAKURA_NAME1", "Heavy Cruiser", 3 });
	//fleet_2.push_back({ "SAKURA_NAME2", "Heavy Cruiser", 4 });
	//fleet_2.push_back({ "SAKURA_NAME3", "Tsundere", 5 });
	//fleet_2.push_back({ "SAKURA_NAME4", "Tsundere", 6 });
	//fleet_2.push_back({ "SAKURA_NAME5", "Tsundere", 7 });
	//fleet_2.push_back({ "Ayanami1", "Small", 8 });
	//fleet_2.push_back({ "Ayanami2", "Small", 9 });
	//fleet_2.push_back({ "Ayanami3", "Small", 10 });
	//fleet_2.push_back({ "Ayanami4", "Small", 11 });

	//////Generate here
	////Generate_ship(fleet_1[0], 0);
	///////////////////
	////
	//////DEBUG FUNCTIONS
	////if (DEBUG_MODE) std::cout << "WARNING! DEBUG MODE ON! \n" << std::endl;
	////Output_Field_ID_Indexes(0);
	////Output_Field_Durability(0);
	////Output_Field_War(0);
	////Output_Field_ID_Indexes(1);
	////Output_Field_Durability(1);
	////Output_Field_War(1);
	/////////////////////

	//////INITIALISATION FIELDS (DO IT AFTER INITIALIZATION OF ALL SHIPS)
	////Initialize_Field_Final(0);
	////std::cout << std::endl << std::endl;
	////Initialize_Field_Final(1);
	///////////////////////////

	////Output_Field_Final(0);
	////std::cout << std::endl << std::endl;
	////Output_Field_Final(1);

	////Выведем флот
	//PrintFleet(fleet_1);
	//PrintFleet(fleet_2);
	return 0;
}