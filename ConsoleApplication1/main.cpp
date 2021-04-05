#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include "ship.h"
#include "generator.h"
#include "fleet.h"
#include "Aircraft_Carrier.h"
#include "Heavy_Cruiser.h"
#include "Tsundere.h"
#include "Small.h"
//ñùüüóòå

int main(int argc, char* argv[]) {
	srand(time(nullptr));

	if constexpr (DEBUG_MODE) {
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
	if (argc > 1)
	{
		std::ifstream fin(argv[2]);
		fleet_2.read(fin);
		std::cout << fleet_2.get_name() << " is loaded from file!" << std::endl << std::endl;
		fin.close();
		//Check fleet_2 for empty
		if (!fleet_2.get_fleet().size()) {
			std::cout << "Warning! Connect the file with the second fleet!" << std::endl;
			return -2;
		}
	}

	fleet_1.print(std::cout);
	fleet_2.print(std::cout);
	//Gemu ga hajimarimasu (game is starting)
	bool ironman = true;

	//Generate here
	for (int i = 0; i < fleet_1.get_fleet().size(); i++) {
		generate_ship(fleet_1.get_ship_by_index(i), fleet_1.get_side());
	}

	for (int i = 0; i < fleet_2.get_fleet().size(); i++) {
		generate_ship(fleet_2.get_ship_by_index(i), fleet_2.get_side());
	}
	///////////////

	//DEBUG FUNCTIONS
	if (DEBUG_MODE) {
		fleet_1.print(std::cout);
		fleet_2.print(std::cout);
		output_field_id_indexes(false);
		output_field_war(false);
		output_field_id_indexes(true);
		output_field_war(true);
		////INITIALISATION FIELDS
		initialize_field_final(fleet_1);
		initialize_field_final(fleet_2);
		/////////////////////////
		std::cout << "Game Fields:" << std::endl << std::endl;
		output_field_final(false, fleet_1.get_name(), fleet_2.get_name());
		output_field_final(true, fleet_1.get_name(), fleet_2.get_name());
	}
	/////////////////

	//Achievements
	std::vector <std::pair<std::string, bool>> achievement_array = read_achievements();
	output_achievement_info(achievement_array);
	//////////////

	if (fleet_1.get_fleet().size() != fleet_2.get_fleet().size()) {
		std::cout << "Warning! Different number of ships in fleets! Ironman mode is disabled." << std::endl << std::endl;
		ironman = false;
	}

	//std::vector <unsigned int> order = first_order(fleet_1, fleet_2);
	std::vector <unsigned int> order = {5};
	std::cout << "Start game?\n\n";
	system("pause");

	if (!DEBUG_MODE) { system("cls"); }

	//Selecting a game mode
	std::string battle_mode;
	while (true)
	{
		std::cout << "Select battle mode (PVE / PvP): "; //USE PVP FOR ATTACKS TESTS
		std::cin >> battle_mode;
		ha_you_are_small_now(battle_mode);
		if (battle_mode == "pve" || battle_mode == "pvp")
		{
			break;
		}
		if constexpr (!DEBUG_MODE) { system("cls"); }
		std::cout << "E-error! This is inappropriate... I... What should I...?" << std::endl << std::endl;
		std::cout << "You scared the program with your wrong input. Be careful next time." << std::endl << std::endl;
		system("pause");
	}

	int difficulty = 0, round = 0, first = rand() % 2;
	if (battle_mode == "pvp") { //PVP
		if constexpr (DEBUG_MODE) { std::cout << "First side: " << first << std::endl; }
		else {
			system("cls");
		}
		while (fleet_1.get_health() && fleet_2.get_health()) {
			switch (first % 2) {
			case 0:
				initialize_field_final(fleet_1);
				std::cout << fleet_1.get_name() << " turn." << std::endl << std::endl;
				output_field_final(0, fleet_1.get_name(), fleet_2.get_name());
				do_action(fleet_1, fleet_2, order, round);
				first++;
				break;
			case 1:
				initialize_field_final(fleet_2);
				std::cout << fleet_2.get_name() << " turn." << std::endl << std::endl;
				output_field_final(1, fleet_1.get_name(), fleet_2.get_name());
				do_action(fleet_2, fleet_1, order, round);
				first++;
				break;
			}
		}
	}
	else if (battle_mode == "pve") //PVE(BOT IS DUMB)
	{
		while (fleet_1.get_health() && fleet_2.get_health()) {
			if (!DEBUG_MODE) { system("cls"); }
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
				if (DEBUG_MODE) {
					std::cout << "First side: " << first << std::endl;
					output_field_id_indexes(false); output_field_id_indexes(true);
				} 
				else {
					system("cls");
				}
				while (fleet_1.get_health() && fleet_2.get_health()) {
					std::cout << fleet_1.get_name() << " Health = " << fleet_1.get_health() << "; " << fleet_2.get_name() << " Health = " << fleet_2.get_health() << std::endl;
					switch (first % 2) {
					case 0: //Player
						initialize_field_final(fleet_1);
						std::cout << fleet_1.get_name() << " turn." << std::endl << std::endl;
						output_field_final(false, fleet_1.get_name(), fleet_2.get_name());
						do_action(fleet_1, fleet_2, order, round);
						first++;
						break;
					case 1: //Bot(ON REWORK)
						initialize_field_final(fleet_2);
						std::cout << fleet_2.get_name() << " turn." << std::endl << std::endl;
						fleet_1.damage_by_index_bot(Default_Damage, difficulty);
						initialize_field_final(fleet_1); //MUST HAVE AFTER ANY DAMAGE
						system("pause");
						if (!DEBUG_MODE) { system("cls"); }
						first++;
						round++;
						if (round == order.size()) {
							round = 0;
						}
						break;
					}
				}
			}
			else {
				if (!DEBUG_MODE) { system("cls"); }
				std::cout << "E-error! This is inappropriate... I... What should I...?" << std::endl << std::endl;
				std::cout << "You scared the program with your wrong input. Be careful next time." << std::endl << std::endl;
				system("pause");
			}
		}
	}
	else  // Protect from Epic Games Store users
	{
		if (!DEBUG_MODE) { system("cls"); }
		std::cout << "E-error! This is inappropriate... I... What should I...?" << std::endl << std::endl;
		std::cout << "You scared the program with your wrong input. Be careful next time." << std::endl << std::endl;
		system("pause");
	}

	//Issuance of achievements after the game
	if (fleet_1.get_health() > fleet_2.get_health()) {
		std::cout << fleet_1.get_name() << " won!";
		if (battle_mode == "pve" && ironman) {
			give_achievement(achievement_array, difficulty);
		}
	}
	else if (fleet_1.get_health() < fleet_2.get_health()) {
		std::cout << fleet_2.get_name() << " won!";
	}
	else { //IDK when it will be work :/
		std::cout << "Friendship";
	}
	if (difficulty == 2 && ironman) {
		give_achievement(achievement_array, 2);
	}
	if (battle_mode == "pvp" && ironman) {
		give_achievement(achievement_array, 3);
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