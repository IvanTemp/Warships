#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include "ship.h"
#include "generator.h"
#include "fleet.h"
#include "attacks.h"

void setup() {
	srand(time(0));
}


int main(int argc, char * argv[]) {
	setup();
	if (DEBUG_MODE) std::cout << "WARNING! DEBUG MODE ON! \n" << std::endl;
	ship ship1("Enterprise", "Aircraft Carrier", 2);
	//Создадим вектор флот
	std::vector<ship> fleet_11;
	//Запихнем в вектор флот наши кораблики
	fleet_11.push_back(ship1);
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
	//Создадим второй флот
	Fleet fleet_2("Sakura Empire");
	fleet_2.AddShipToFleet({ "Akagi", "Aircraft Carrier", 2 });
	fleet_2.AddShipToFleet({ "SAKURA_NAME1", "Heavy Cruiser", 3 });
	fleet_2.AddShipToFleet({ "SAKURA_NAME2", "Heavy Cruiser", 4 });
	fleet_2.AddShipToFleet({ "SAKURA_NAME3", "Tsundere", 5 });
	fleet_2.AddShipToFleet({ "SAKURA_NAME4", "Tsundere", 6 });
	fleet_2.AddShipToFleet({ "SAKURA_NAME5", "Tsundere", 7 });
	fleet_2.AddShipToFleet({ "Ayanami1", "Small", 8 });
	fleet_2.AddShipToFleet({ "Ayanami2", "Small", 9 });
	fleet_2.AddShipToFleet({ "Ayanami3", "Small", 10 });
	fleet_2.AddShipToFleet({ "Ayanami4", "Small", 11 });
	//Выведем оба флота
	if (DEBUG_MODE) {
		fleet_1.Print(std::cout);
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
	//Считаем флот из файла input.txt (имена в параметрах проекта)
	if (argc > 2)
	{
		Fleet fleet_3;
		std::ifstream fin(argv[2]);
		fleet_3.Read(fin);
		fin.close();
		//Выведем флот из файла
		fleet_3.Print(std::cout);
	}
	//Считаем флот из консоли
	/*Fleet fleet_4;
	fleet_4.Read(std::cin);
	fleet_4.Print(std::cout);*/

	if (DEBUG_MODE) { std::cout << "\nShips count: " << ship1.GetCount() << std::endl << std::endl; }

	////Generate here
	for (int i = 0; i < 10; i++) {
		Generate_ship(fleet_2.GetShipByIndex(i), 0);
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
	Output_Field_Final(0);
	std::cout << std::endl << std::endl;
	Output_Field_Final(1);

	////Changing durability
	fleet_1.GetShipByIndex(0).SetDurability({ fleet_1.GetShipByIndex(0).GetDurability()[0], fleet_1.GetShipByIndex(0).GetDurability()[1] - 2, fleet_1.GetShipByIndex(0).GetDurability()[2] - 2, fleet_1.GetShipByIndex(0).GetDurability()[3] });

	Field_Refresh_Durability(fleet_1.GetShipByIndex(0), 0); //Must have after any damage

	Output_Field_Final(0);
	//std::cout << std::endl << std::endl;
	//Output_Field_Final(1);

	return 0;
}