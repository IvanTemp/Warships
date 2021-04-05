#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include "fleet.h"
#include "Aircraft_Carrier.h"
#include "Heavy_Cruiser.h"
#include "Tsundere.h"
#include "Small.h"
#include "GameInformation.h"

//Game Information
GameInformation game_info();
//////////////////

int main(int argc, char* argv[]) {
	srand(time(nullptr));

	if (game_info().get_debug_mode()) {
		std::cout << "WARNING! DEBUG MODE ON! \n" << std::endl;
	}
	else {
		std::cout << "This is a playable build! Most of the information unnecessary to the player will be shown only after enabling DEBUG_MODE in ship.h!\n\n";
	}

	if constexpr (width_height > 26) {
		std::cout << "Warning! The game is not designed for such a large field size! Please limit yourself to 26 cells!" << std::endl;
		return -26;
	}
	
	//FLEET 1
	
	Aircraft_Carrier air1;
	Heavy_Cruiser HwCrus1, HwCrus2;
	Tsundere Tsun1, Tsun2, Tsun3;
	Small Sm1, Sm2, Sm3, Sm4;
	Fleet fleet_1 = { "Eagle Union",{
		{"Enterprise", air1, 2},
		{"Prinz Eugene", HwCrus1, 3},
		{"Atago", HwCrus2, 4},
		{"FLX1", Tsun1, 5},
		{"FLX2", Tsun2, 6},
		{"FLX3", Tsun3, 7},
		{"Flaffey1", Sm1, 8},
		{"Flaffey2", Sm2, 9},
		{"Flaffey3", Sm3, 10},
		{"Flaffey4", Sm4, 11} } };
	//FLEET 2
	//We read the fleet from the file input.txt (names in the project parameters)
	Fleet fleet_2;
	if (argc > 2)
	{
		std::ifstream fin(argv[2]);
		fleet_2.read(fin);
		std::cout << fleet_2.get_name() << " is loaded from file!" << std::endl << std::endl;
		fin.close();
		//Check fleet_2 for empty
		if (!fleet_2.get_ship_vector().size()) {
			std::cout << "Warning! File with the second fleet is empty!" << std::endl;
			return -2;
		}
	}

	fleet_1.print(std::cout);
	fleet_2.print(std::cout);
	
	bool ironman = true;

	//Generate here
	for (int i = 0; i < fleet_1.get_ship_vector().size(); i++) {
		generate_ship(fleet_1.get_ship_by_index(i), fleet_1.get_side());
	}

	for (int i = 0; i < fleet_2.get_ship_vector().size(); i++) {
		generate_ship(fleet_2.get_ship_by_index(i), fleet_2.get_side());
	}
	///////////////

	//DEBUG FUNCTIONS
	if (game_info().get_debug_mode()) {
		fleet_1.print(std::cout);
		fleet_2.print(std::cout);
		game_info().output_field_id_indexes(false);
		game_info().output_field_war(false);
		game_info().output_field_id_indexes(true);
		game_info().output_field_war(true);
		////INITIALISATION FIELDS
		game_info().initialize_field_final(fleet_1);
		game_info().initialize_field_final(fleet_2);
		/////////////////////////
		std::cout << "Game Fields:" << std::endl << std::endl;
		game_info().output_field_final(false, fleet_1.get_name(), fleet_2.get_name());
		game_info().output_field_final(true, fleet_1.get_name(), fleet_2.get_name());
	}
	/////////////////

	//Achievements
	std::vector <std::pair<std::string, bool>> achievement_array = game_info().read_achievements_from_file();
	game_info().output_achievement_info(achievement_array);
	//////////////

	if (fleet_1.get_ship_vector().size() != fleet_2.get_ship_vector().size()) {
		std::cout << "Warning! Different number of ships in fleets! Ironman mode is disabled." << std::endl << std::endl;
		ironman = false;
	}

	//std::vector <unsigned int> order = first_order(fleet_1, fleet_2);
	std::vector <unsigned int> order = {5};
	std::cout << "Start game?\n\n";
	system("pause");

	if (!game_info().get_debug_mode()) { system("cls"); }

	//Selecting a game mode
	std::string battle_mode;
	while (true)
	{
		std::cout << "Select battle mode (PVE / PvP): "; //USE PVP FOR ATTACKS TESTS
		std::cin >> battle_mode;
		game_info().ha_you_are_small_now(battle_mode); //Почему я не мог оставить эту функцию в generator.cpp....
		if (battle_mode == "pve" || battle_mode == "pvp")
		{
			break;
		}
		if (!game_info().get_debug_mode()) { system("cls"); }
		std::cout << "E-error! This is inappropriate... I... What should I...?" << std::endl << std::endl;
		std::cout << "You scared the program with your wrong input. Be careful next time." << std::endl << std::endl;
		system("pause");
	}

	int difficulty = 0, round = 0, first = rand() % 2;
	if (battle_mode == "pvp" || battle_mode == "p") { //PVP
		if (game_info().get_debug_mode()) { std::cout << "First side: " << first << std::endl; }
		else {
			system("cls");
		}
		while (fleet_1.get_health() && fleet_2.get_health()) {
			switch (first % 2) {
				case 0:
					game_info().initialize_field_final(fleet_1);
					std::cout << fleet_1.get_name() << " turn." << std::endl << std::endl;
					game_info().output_field_final(false, fleet_1.get_name(), fleet_2.get_name());
					game_info().do_action(fleet_1, fleet_2, order, round);
					break;
				case 1:
					game_info().initialize_field_final(fleet_2);
					std::cout << fleet_2.get_name() << " turn." << std::endl << std::endl;
					game_info().output_field_final(true, fleet_1.get_name(), fleet_2.get_name());
					game_info().do_action(fleet_2, fleet_1, order, round);
					break;
			}
			switch (first + 1 % 2) {
				case 0:
					game_info().initialize_field_final(fleet_1);
					std::cout << fleet_1.get_name() << " turn." << std::endl << std::endl;
					game_info().output_field_final(false, fleet_1.get_name(), fleet_2.get_name());
					game_info().do_action(fleet_1, fleet_2, order, round);
					break;
				case 1:
					game_info().initialize_field_final(fleet_2);
					std::cout << fleet_2.get_name() << " turn." << std::endl << std::endl;
					game_info().output_field_final(true, fleet_1.get_name(), fleet_2.get_name());
					game_info().do_action(fleet_2, fleet_1, order, round);
					break;
				}
			first++;
		}
	}
	else if (battle_mode == "pve" || battle_mode == "e") //PVE
	{
		while (fleet_1.get_health() && fleet_2.get_health()) {
			if (!game_info().get_debug_mode()) { system("cls"); }
			std::cout << "Select difficulty level NUMBER: " << std::endl;
			std::cout << "1)Normal" << std::endl; //Everything is fair
			std::cout << "2)Hard" << std::endl; //Bot has the right to make mistake
			std::cout << "3)Impossible" << std::endl << std::endl; //Bot will try until it hits, and it will always go first
			std::cout << "Difficulty: ";
			std::cin >> difficulty;
			difficulty--;

			if (difficulty == 2) {
				first = 1; //Bot will always go first Kappa
			}

			if (difficulty >= 0 && difficulty <= 2) { //0 - 2(1 - 3 for user)
				if (game_info().get_debug_mode()) { std::cout << "First side: " << first << std::endl; }
				else {
					system("cls");
				}
				while (fleet_1.get_health() && fleet_2.get_health()) {
					switch (first % 2) { //0 - player; 1 - bot
						case 0:
							game_info().initialize_field_final(fleet_1);
							std::cout << fleet_1.get_name() << " turn." << std::endl << std::endl;
							game_info().output_field_final(false, fleet_1.get_name(), fleet_2.get_name());
							game_info().do_action(fleet_1, fleet_2, order, round);
							break;
						case 1:
							game_info().initialize_field_final(fleet_2);
							std::cout << fleet_2.get_name() << " turn." << std::endl << std::endl;
							fleet_2.damage_by_index_bot_v2(order[round], fleet_2.get_ship_by_index(order[round]).get_type()->get_damage_value(), difficulty);
							break;
						}
					switch (first + 1 % 2) {
						case 0:
							game_info().initialize_field_final(fleet_1);
							std::cout << fleet_1.get_name() << " turn." << std::endl << std::endl;
							game_info().output_field_final(false, fleet_1.get_name(), fleet_2.get_name());
							game_info().do_action(fleet_1, fleet_2, order, round);
							break;
						case 1:
							game_info().initialize_field_final(fleet_2);
							std::cout << fleet_2.get_name() << " turn." << std::endl << std::endl;
							game_info().output_field_final(true, fleet_1.get_name(), fleet_2.get_name());
							game_info().do_action(fleet_2, fleet_1, order, round);
							break;
					}
					first++;
				}
			}
			else {
				if (!game_info().get_debug_mode()) { system("cls"); }
				std::cout << "E-error! This is inappropriate... I... What should I...?" << std::endl << std::endl;
				std::cout << "You scared the program with your wrong input. Be careful next time." << std::endl << std::endl;
				system("pause");
			}
		}
	}
	else  // Protect from Epic Games Store users
	{
		if (!game_info().get_debug_mode()) { system("cls"); }
		std::cout << "E-error! This is inappropriate... I... What should I...?" << std::endl << std::endl;
		std::cout << "You scared the program with your wrong input. Be careful next time." << std::endl << std::endl;
		system("pause");
	}

	//Issuance of achievements after the game
	if (fleet_1.get_health() > fleet_2.get_health()) {
		std::cout << fleet_1.get_name() << " won!";
		if (battle_mode == "pve" && ironman) {
			game_info().give_achievement(achievement_array, difficulty);
		}
	}
	else if (fleet_1.get_health() < fleet_2.get_health()) {
		std::cout << fleet_2.get_name() << " won!";
	}
	else { //IDK when it will be work :/
		std::cout << "Friendship";
	}
	if (difficulty == 2 && ironman) {
		game_info().give_achievement(achievement_array, 2);
	}
	if (battle_mode == "pvp" && ironman) {
		game_info().give_achievement(achievement_array, 3);
	}

	//Let's output fleets to the file output.txt (names in the project parameters)
	if (argc > 1)
	{
		std::ofstream out(argv[1]);
		fleet_1.print(out);
		fleet_2.print(out);
		out.close();
	}

	return 0;
}