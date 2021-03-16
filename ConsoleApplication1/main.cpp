#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include "ship.h"
#include "generator.h"
#include "fleet.h"


int main(int argc, char * argv[]) {
	srand(time(0));

	if (!DEBUG_MODE) {
		std::cout << "This is a playable build! Most of the implemented features will be enabled only after enabling DEBUG_MODE in ship.h!\n\n";
	} else {
		std::cout << "WARNING! DEBUG MODE ON! \n" << std::endl;
	}

	if (width_height > 26) {
		std::cout << "Warning! The game is not designed for such a large field size! Please limit yourself to 26 cells!" << std::endl;
		return -26;
	}

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
	//Считаем флот из файла input.txt (имена в параметрах проекта)
	Fleet fleet_2;
	if (argc > 2)
	{
		std::ifstream fin(argv[2]);
		fleet_2.Read(fin);
		std::cout << fleet_2.GetName() << " is loaded from file!" << std::endl << std::endl;
		fin.close();
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
	//Выведем количество кораблей (по факту это количество вызовов конструктора... поэтому можно вызывать у любого корабля и плюс, и минус)
	std::cout << "Ships count: " << ship1.GetCount() << std::endl << std::endl; //(Для Алексея)Да, это надо в лабу!(Для Вани)Эх, ну лааадно :(



	/*				Тут заканчивается наша первая лабораторная работа(по словам Вани)				*/
	
	if (DEBUG_MODE) 
	{
		fleet_1.Print(std::cout);
		fleet_2.Print(std::cout);
	}

	//Generate here
	for (int i = 0; i < fleet_1.GetFleet().size(); i++) {
		Generate_ship(fleet_1.GetShipByIndex(i), fleet_1.GetSide());
	}

	for (int i = 0; i < fleet_2.GetFleet().size(); i++) {
		Generate_ship(fleet_2.GetShipByIndex(i), fleet_2.GetSide());
	}
	///////////////

	//DEBUG FUNCTIONS
	if (DEBUG_MODE)
	{
		Output_Field_ID_Indexes(0);
		Output_Field_Durability(0);
		Output_Field_War(0);
		Output_Field_ID_Indexes(1);
		Output_Field_Durability(1);
		Output_Field_War(1);
	}
	/////////////////

	////INITIALISATION FIELDS
	Initialize_Field_Final(0);
	Initialize_Field_Final(1);
	/////////////////////////

	//DAMAGE TEST
	/*if (DEBUG_MODE) {
		std::cout << "DAMAGE TEST:" << std::endl << std::endl;
		std::cout << "Before attack in random place:" << std::endl << std::endl;
		Output_Field_Final(0, 0);
		std::cout << std::endl << std::endl;
		Output_Field_Final(1, 1);

		fleet_2.ConsDmgToIndBot(2); //Wasn't tested after rework

		std::cout << "After attack in random place:" << std::endl << std::endl;
		std::cout << std::endl;
		Output_Field_Final(0, 0);
		std::cout << std::endl << std::endl;
		Output_Field_Final(1, 1);
	}*/
	/////////////

	//FOG OF WAR TEST
	//if (DEBUG_MODE) {
	//	std::cout << "FOG OF WAR TEST:" << std::endl << std::endl;
	//	std::cout << "FOR PLAYER: " << std::endl;
	//	Output_Field_Final(0, 0);
	//	Output_Field_Final(1, 0);

	//	std::cout << "FOR BOT: " << std::endl;
	//	Output_Field_Final(0, 1);
	//	Output_Field_Final(1, 1);
	//}
	/////////////////

	if (DEBUG_MODE) {
		std::cout << "Game Fields:" << std::endl << std::endl;
		Output_Field_Final(0);
		Output_Field_Final(1);
	}

	//Начинается цикл игры
	std::cout << "Start game?\n\n";
	system("pause");

	while (fleet_1.GetHealth() && fleet_2.GetHealth()) {
		system("cls");
		std::string BattleMode = "";
		std::cout << "Select battle mode (PvE / PvP): ";
		std::cin >> BattleMode;
		BattleMode = hahaYouAreSmallNow(BattleMode);

		int first = -1 + rand() % 2 + 1;
		if (BattleMode == "pvp") {
			system("cls");
			while (fleet_1.GetHealth() && fleet_2.GetHealth()) {
				//Смена хода
				std::cout << fleet_1.GetName() << " turn." << std::endl << std::endl;
				//Вывод поля игрока 1
				Output_Field_Final(0);
				//Выстрел игрока 1
				std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
				fleet_2.ConsDmgToIndPlayer(2);
				Field_Refresh_Durability_REFORGED(fleet_2);
				system("pause");
				system("cls");

				//Смена хода
				std::cout << fleet_2.GetName() << " turn." << std::endl << std::endl;
				//Вывод поля игрока 2
				Output_Field_Final(1);
				//Выстрел игрока 2
				std::cout << "Order, commander! (Write X and Y coordinates): ";
				fleet_1.ConsDmgToIndPlayer(2);
				Field_Refresh_Durability_REFORGED(fleet_1);
				system("pause");
				system("cls");
			}
		} else if (BattleMode == "pve") {
			while (fleet_1.GetHealth() && fleet_2.GetHealth()) {
				int difficulty = 0;
				system("cls");
				std::cout << "Select difficulty level number: " << std::endl;
				std::cout << "1)Normal" << std::endl;
				std::cout << "2)Hard(SOON)" << std::endl;
				std::cout << "3)Impossible(SOON)" << std::endl << std::endl;
				std::cout << "Difficulty: ";
				std::cin >> difficulty;
				difficulty--;

				if (!difficulty) { //Normal difficulty
					system("cls");
					while (fleet_1.GetHealth() && fleet_2.GetHealth()) {
						std::cout << fleet_1.GetName() << " Health = " << fleet_1.GetHealth() << "; " << fleet_2.GetName() << " Health = " << fleet_2.GetHealth() << std::endl;
						switch (first % 2) {
							case 0:
								//Смена хода
								std::cout << fleet_1.GetName() << " turn." << std::endl << std::endl;
								//Вывод поля для игрока 1
								Output_Field_Final(0);
								//Выстрел игрока 1
								std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
								fleet_2.ConsDmgToIndPlayer(2);
								Field_Refresh_Durability_REFORGED(fleet_2);
								system("pause");
								if (!DEBUG_MODE) { system("cls"); }
								first++;
								break;
							case 1:
								//Смена хода
								std::cout << fleet_2.GetName() << " turn." << std::endl << std::endl;
								//Выстрел бота
								fleet_1.ConsDmgToIndBot(2, difficulty);
								Field_Refresh_Durability_REFORGED(fleet_1);
								system("pause");
								if (!DEBUG_MODE) { system("cls"); }
								first++;
								break;
						}
					}
				} else {
					system("cls");
					std::cout << "E-error! This is inapporopriate... I... What should I...?" << std::endl << std::endl;
					std::cout << "You scared the program with your wrong input. Be careful next time." << std::endl << std::endl;
					system("pause");
				}
			}
		} else {
			system("cls");
			std::cout << "E-error! This is inapporopriate... I... What should I...?" << std::endl << std::endl;
			std::cout << "You scared the program with your wrong input. Be careful next time." << std::endl << std::endl;
			system("pause");
		}
	}
	if (fleet_1.GetHealth() > fleet_2.GetHealth()) { std::cout << fleet_1.GetName(); }
	else if (fleet_1.GetHealth() < fleet_2.GetHealth()) { std::cout << fleet_2.GetName(); }
	else { std::cout << "Friendship"; }
	std::cout << " won";
	return 0;
}