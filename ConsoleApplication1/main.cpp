#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include "ship.h"
#include "generator.h"
#include "fleet.h"

bool Ironman = 1;

/*Список найденных багов(на русском, ибо кому-то лень пропускать это через переводчик):
1)Если игрок введёт сначала число, а затем букву, то выстрел пройдёт по X = цифре Y = 0, а в дальнейшем игрок не сможет вводить координаты до конца игры
*/

int main(int argc, char * argv[]) {
	srand(time(0));

	if (!DEBUG_MODE) {
		std::cout << "This is a playable build! Most of the information unnecessary to the player will be shown only after enabling DEBUG_MODE in ship.h!\n\n";
	} else {
		std::cout << "WARNING! DEBUG MODE ON! \n" << std::endl;
	}

	if (width_height > 26) {
		std::cout << "Warning! The game is not designed for such a large field size! Please limit yourself to 26 cells!" << std::endl;
		return -26;
	}

	//[IN DEVELOPMENT]ACHIEVEMENTS
	//TODO: код тупо чистит файл с ачивками, если там что-то было
	//std::vector <std::pair<std::string, bool>> achievement_vector;
	//int i = -1;
	//std::string achievement_status = "";
	//std::ofstream achievements_file1("achievements.save");
	//achievements_file1.close();
	//std::ifstream achievements_file2("achievements.save", std::ios::in | std::ios::out);
	//while (!achievements_file2.eof()) {
	//	i++;
	//	achievement_vector.push_back(std::make_pair("", 0));
	//	std::getline(achievements_file2, achievement_vector[i].first);
	//	std::getline(achievements_file2, achievement_status);
	//	achievement_status == "1" ? achievement_vector[i].second = 1 : achievement_vector[i].second = 0;
	//}
	//////////////////////////////

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


	if (!fleet_2.GetFleet().size()) { std::cout << "Warning! Connect the file with the second fleet!" << std::endl; return -2; }
	/*				Тут заканчивается наша первая лабораторная работа(по словам Вани)				*/
	
	//Generate here
	for (int i = 0; i < fleet_1.GetFleet().size(); i++) {
		Generate_ship(fleet_1.GetShipByIndex(i), fleet_1.GetSide());
	}

	for (int i = 0; i < fleet_2.GetFleet().size(); i++) {
		Generate_ship(fleet_2.GetShipByIndex(i), fleet_2.GetSide());
	}
	///////////////

	//DEBUG FUNCTIONS
	if (DEBUG_MODE) {
		OutputAchievementInfo(achievement_vector);
		fleet_1.Print(std::cout);
		fleet_2.Print(std::cout);
		Output_Field_ID_Indexes(0);
		Output_Field_War(0);
		Output_Field_ID_Indexes(1);
		Output_Field_War(1);
	}
	/////////////////

	////INITIALISATION FIELDS
	Initialize_Field_Final(fleet_1);
	Initialize_Field_Final(fleet_2);
	/////////////////////////

	//DAMAGE TEST
	/*if (DEBUG_MODE) {
		std::cout << "DAMAGE TEST:" << std::endl << std::endl;
		std::cout << "Before attack in random place:" << std::endl << std::endl;
		Output_Field_Final_REFORGED(0);
		std::cout << std::endl << std::endl;
		Output_Field_Final_REFORGED(1);

		fleet_2.ConsDmgToIndBot(2); //Wasn't tested after rework

		std::cout << "After attack in random place:" << std::endl << std::endl;
		std::cout << std::endl;
		Output_Field_Final_REFORGED(0);
		std::cout << std::endl << std::endl;
		Output_Field_Final_REFORGED(1);
	}*/
	/////////////

	//FOG OF WAR TEST
	//if (DEBUG_MODE) {
	//	std::cout << "FOG OF WAR TEST:" << std::endl << std::endl;
	//	std::cout << "FOR PLAYER: " << std::endl;
	//	Output_Field_Final_REFORGED(0, 0);
	//	Output_Field_Final_REFORGED(1, 0);

	//	std::cout << "FOR BOT: " << std::endl;
	//	Output_Field_Final_REFORGED(0);
	//	Output_Field_Final_REFORGED(1);
	//}
	/////////////////

	if (DEBUG_MODE) {
		std::cout << "Game Fields:" << std::endl << std::endl;
		Output_Field_Final_REFORGED(0, fleet_1.GetName(), fleet_2.GetName());
		Output_Field_Final_REFORGED(1, fleet_1.GetName(), fleet_2.GetName());
	}

	if (fleet_1.GetFleet().size() != fleet_2.GetFleet().size()) {
		std::cout << "Warning! Different number of ships in fleets! Ironman mode is disabled." << std::endl << std::endl;
		Ironman = 0;
	}

	First_order(fleet_1, fleet_2);

	//Начинается цикл игры
	std::cout << "Start game?\n\n";
	system("pause");

	while (fleet_1.GetHealth() && fleet_2.GetHealth()) {
		system("cls");
		std::string BattleMode = "";
		std::cout << "Select battle mode (PvE / PvP): ";
		std::cin >> BattleMode;
		BattleMode = hahaYouAreSmallNow(BattleMode);

		int first = rand() % 2;
		if (BattleMode == "pvp") {
			system("cls");
			if (DEBUG_MODE) {
				std::cout << "First side: " << first << std::endl;
			}
			while (fleet_1.GetHealth() && fleet_2.GetHealth()) {
				switch (first % 2) {
					case 0:
						//Смена хода
						Initialize_Field_Final(fleet_1);
						std::cout << fleet_1.GetName() << " turn." << std::endl << std::endl;
						//Вывод поля игрока 1
						Output_Field_Final_REFORGED(0, fleet_1.GetName(), fleet_2.GetName());
						//Выстрел игрока 1
						std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
						fleet_2.ConsDmgToIndPlayer(2);
						Initialize_Field_Final(fleet_2);
						system("pause");
						system("cls");
						first++;
						break;
					case 1:
						//Смена хода
						Initialize_Field_Final(fleet_2);
						std::cout << fleet_2.GetName() << " turn." << std::endl << std::endl;
						//Вывод поля игрока 2
						Output_Field_Final_REFORGED(1, fleet_1.GetName(), fleet_2.GetName());
						//Выстрел игрока 2
						std::cout << "Order, commander! (Write X and Y coordinates): ";
						fleet_1.ConsDmgToIndPlayer(2);
						Initialize_Field_Final(fleet_1);
						system("pause");
						system("cls");
						first++;
						break;
				}
			}
		} else if (BattleMode == "pve") {
			while (fleet_1.GetHealth() && fleet_2.GetHealth()) {
				int difficulty = 0;
				system("cls");
				std::cout << "Select difficulty level NUMBER: " << std::endl;
				std::cout << "1)Normal" << std::endl; //Everything is fair
				std::cout << "2)Hard" << std::endl; //Bot has the right to make mistake
				std::cout << "3)Impossible" << std::endl << std::endl; //Bot will try until it hits, and it will always go first
				std::cout << "Difficulty: ";
				std::cin >> difficulty;
				difficulty--;

				if (difficulty == 2) {
					first = 1; //Bot will always go first
				}

				if (difficulty >= 0 && difficulty <= 2) { //0 - 2(1 - 3 for user)
					system("cls");
					if (DEBUG_MODE) {
						std::cout << "First side: " << first << std::endl;
						Output_Field_ID_Indexes(0); Output_Field_ID_Indexes(1);
					}
					while (fleet_1.GetHealth() && fleet_2.GetHealth()) {
						std::cout << fleet_1.GetName() << " Health = " << fleet_1.GetHealth() << "; " << fleet_2.GetName() << " Health = " << fleet_2.GetHealth() << std::endl;
						switch (first % 2) {
							case 0: //Player
								Initialize_Field_Final(fleet_1);
								std::cout << fleet_1.GetName() << " turn." << std::endl << std::endl;
								//Вывод поля для игрока 1
								Output_Field_Final_REFORGED(0, fleet_1.GetName(), fleet_2.GetName());
								//Shot
								std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
								fleet_2.ConsDmgToIndPlayer(2);
								Initialize_Field_Final(fleet_2); //MUST HAVE AFTER ANY DAMAGE
								system("pause");
								if (!DEBUG_MODE) { system("cls"); }
								first++;
								break;
							case 1: //Bot
								std::cout << fleet_2.GetName() << " turn." << std::endl << std::endl;
								//Shot
								fleet_1.ConsDmgToIndBot(2, difficulty);
								Initialize_Field_Final(fleet_1); //MUST HAVE AFTER ANY DAMAGE
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
	std::cout << " won!";
	return 0;
}