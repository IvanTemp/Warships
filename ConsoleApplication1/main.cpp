#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include "ship.h"
#include "generator.h"
#include "fleet.h"
//#include "attacks.h"


int main(int argc, char * argv[]) {
	srand(time(0));
	if (DEBUG_MODE) std::cout << "WARNING! DEBUG MODE ON! \n" << std::endl;


	ship ship1("Enterprise", "Aircraft Carrier", 2);
	//Создадим вектор флот
	std::vector<ship> fleet_11;
	//Запихнем в вектор наш кораблик
	fleet_11.push_back(ship1);
	//Добавим еще кораблики
	fleet_11.push_back({ "Prinz Eugene", "Heavy Cruiser", 3 });
	fleet_11.push_back({ "Atago", "Heavy Cruiser", 4 });
	fleet_11.push_back({ "FLX1", "Tsundere", 5 });
	fleet_11.push_back({ "FLX2", "Tsundere", 6 });
	fleet_11.push_back({ "FLX3", "Tsundere", 7 });
	fleet_11.push_back({ "Flaffey1", "Small", 8 });
	fleet_11.push_back({ "Flaffey2", "Small", 9 });
	fleet_11.push_back({ "Flaffey3", "Small", 10 });
	fleet_11.push_back({ "Flaffey4", "Small", 11 });
	//Запихнем флот в класс
	Fleet fleet_1("Eagle Union", fleet_11);
	fleet_1.SetSide(0);
	//Считаем флот из файла input.txt (имена в параметрах проекта)
	Fleet fleet_2;
	if (argc > 2)
	{
		std::ifstream fin(argv[2]);
		fleet_2.Read(fin);
		fin.close();
		//Выведем флот из файла
		fleet_2.Print(std::cout);
	}
	//Выведем их в файл output.txt (имена в параметрах проекта)
	if (argc > 1)
	{
		std::ofstream fout(argv[1]);
		fleet_1.Print(fout);
		fleet_2.Print(fout);
		fout.close();
	}

	//Считаем флот из консоли
	/*Fleet fleet_4;
	fleet_4.Read(std::cin);
	fleet_4.Print(std::cout);*/





	if (DEBUG_MODE) { std::cout << "\nShips count: " << ship1.GetCount() << std::endl << std::endl; }

	////Generate here
	for (int i = 0; i < 1; i++) {
		Generate_ship(fleet_1.GetShipByIndex(i), 0);
	}
	///////////////
	
	//DEBUG FUNCTIONS
	Output_Field_ID_Indexes(0);
	Output_Field_Durability(0);
	Output_Field_War(0);
	Output_Field_ID_Indexes(1);
	Output_Field_Durability(1);
	Output_Field_War(1);
	/////////////////

	////INITIALISATION FIELDS
	Initialize_Field_Final(0);
	Initialize_Field_Final(1);
	/////////////////////////

	std::cout << std::endl << std::endl;
	//Output_Field_Final(0);
	std::cout << std::endl << std::endl;
	//Output_Field_Final(1);

	////Changing durability
	//fleet_1.GetShipByIndex(0).SetDurability({ fleet_1.GetShipByIndex(0).GetDurability()[0], fleet_1.GetShipByIndex(0).GetDurability()[1] - 2, fleet_1.GetShipByIndex(0).GetDurability()[2] - 2, fleet_1.GetShipByIndex(0).GetDurability()[3] });
	//Field_Refresh_Durability(fleet_1.GetShipByID(0), 0); //Must have after any damage

	//Damage
	//Simple_Attack(fleet_1, 5, 5, 2);
	//fleet_1.GetShipByIndex(0).DmgtoInd(2, 3);
	////////

	Output_Field_Final(0);
	std::cout << std::endl << std::endl;
	Output_Field_Final(1);

	fleet_1.DmgToInd(5, 5, -3);

	fleet_1.Print(std::cout);


	return 0;
}