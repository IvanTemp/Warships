#include "functions.h"
#include "Fleet.h"
#include "AircraftCarrier.h"
#include "HeavyCruiser.h"
#include "Tsundere.h"
#include "Small.h"
#include <string>
#include <vector>
#include <iostream>


int main(int argc, char* argv[]) {
	switch (SEED) {
	case 0:
		srand(time(nullptr));
		if constexpr (DEBUG_MODE) {
			std::cout << "[MAIN]Seed: " << time(nullptr) << std::endl;
		}
		break;
	default:
		srand(SEED);
		if constexpr (DEBUG_MODE) {
			std::cout << "[MAIN]Seed: " << SEED << std::endl;
		}
		break;
	}

	if constexpr (DEBUG_MODE) {
		std::cout << "WARNING! DEBUG MODE ON! \n" << std::endl;
	}
	else {
		std::cout << "This is a playable build! Most of the information unnecessary to the player will be shown only after enabling DEBUG_MODE in Ship.h!\n\n";
	}

	if constexpr (width_height > 26) {
		std::cout << "Warning! The game is not designed for such a large field size! Please limit yourself to 26 cells!" << std::endl;
		return -26;
	}

	//FLEET 1
	
	AircraftCarrier air1;
	HeavyCruiser HwCrus1, HwCrus2;
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
		if (fleet_2.get_ship_vector().empty()) {
			std::cout << "Warning! Connect the file with the second fleet!" << std::endl;
			return -2;
		}
	}
	////////

	fleet_1.print(std::cout);
	std::cout << std::endl;
	fleet_2.print(std::cout);
	std::cout << std::endl;
	
	//Gemu ga hajimarimasu(прим. переводчика: Игра начинается)
	bool ironman = true;
	fleet_1.generate_fleet();
	fleet_2.generate_fleet();
	///////////////

	//Order
	std::vector <unsigned int> order = first_order(std::max(fleet_1.get_ship_vector().size(), fleet_2.get_ship_vector().size()));
	//std::vector <unsigned int> order = { 8 };
	///////

	//DEBUG FUNCTIONS
	if constexpr (DEBUG_MODE) {
		fleet_1.print(std::cout);
		fleet_2.print(std::cout);
		fleet_1.output_field_id();
		fleet_1.output_field_index();
		fleet_1.output_field_war();
		fleet_2.output_field_id();
		fleet_2.output_field_index();
		fleet_2.output_field_war();
		////Initialisation fields
		fleet_1.initialize_field_final();
		fleet_2.initialize_field_final();
		/////////////////////////
		std::cout << "Game Fields:" << std::endl << std::endl;
		fleet_1.output_field_final(fleet_2);
		fleet_2.output_field_final(fleet_1);
		std::cout << std::endl << "Order: ";
		for (auto& i : order) {
			std::cout << i << " ";
		}
		std::cout << std::endl << std::endl;
	}
	/////////////////

	//Achievements
	std::vector <std::pair<std::string, bool>> achievement_array = read_achievements();
	output_achievement_info(achievement_array);
	//////////////

	if (fleet_1 != fleet_2) {
		std::cout << "Warning! Dizballans! Ironman mode is disabled." << std::endl << std::endl;
		ironman = false;
	}

	std::cout << "Start game?\n";
	system("pause");

	if constexpr (!DEBUG_MODE) { system("cls"); }

	//Selecting a game mode
	std::string battle_mode;
	while (true)
	{
		std::cout << "Select game mode: \n-PvP\n-PvE\n-Missions\n\n";
		std::cin >> battle_mode;
		ha_you_are_small_now(battle_mode);
		if (battle_mode == "pve" || battle_mode == "pvp" || battle_mode == "missions")
		{
			break;
		}
		if constexpr (!DEBUG_MODE) { system("cls"); }
		std::cout << "E-error! This is inappropriate... I... What should I...?" << std::endl << std::endl;
		std::cout << "You scared the program with your wrong input. Be careful next time." << std::endl << std::endl;
		system("pause");
	}

	int difficulty = 0, round = 0, temple = rand() % 2;
	if (battle_mode == "pvp" || battle_mode == "p") { //PVP
		if constexpr (!DEBUG_MODE) system("cls");
		while (fleet_1.get_health() && fleet_2.get_health()) {
			switch (temple % 2) {
				case 0:
					fleet_1.initialize_field_final();
					std::cout << fleet_1.get_name() << " turn." << std::endl << std::endl;
					fleet_1.output_field_final(fleet_2);
					fleet_1.do_action(fleet_2, order[round]);
					break;
				case 1:
					fleet_2.initialize_field_final();
					std::cout << fleet_2.get_name() << " turn." << std::endl << std::endl;
					fleet_2.output_field_final(fleet_1);
					fleet_2.do_action(fleet_1, order[round]);
					break;
			}
			if constexpr (!DEBUG_MODE) system("cls");
			if (!fleet_1.get_health() || !fleet_2.get_health()) break;
			temple++;
			switch (temple % 2) {
				case 0:
					fleet_1.initialize_field_final();
					std::cout << fleet_1.get_name() << " turn." << std::endl << std::endl;
					fleet_1.output_field_final(fleet_2);
					fleet_1.do_action(fleet_2, order[round]);
					break;
				case 1:
					fleet_2.initialize_field_final();
					std::cout << fleet_2.get_name() << " turn." << std::endl << std::endl;
					fleet_2.output_field_final(fleet_1);
					fleet_2.do_action(fleet_1, order[round]);
					break;
				}
			temple--;
			round++;
			if (order.size() == round) round = 0;
			if constexpr (!DEBUG_MODE) system("cls");
		}
	}
	else if (battle_mode == "pve" || battle_mode == "e") //PVE
	{
		while (true) {
			if constexpr (!DEBUG_MODE) { system("cls"); }
			std::cout << "Select difficulty level NUMBER: " << std::endl;
			std::cout << "1)Normal" << std::endl; //Everything is fair
			std::cout << "2)Hard" << std::endl; //Bot has the right to make mistake
			std::cout << "3)Impossible" << std::endl << std::endl; //Bot will try until it hits, and it will always go first
			std::cout << "Difficulty: ";
			std::cin >> difficulty;
			difficulty--;
			if (difficulty >= 0 && difficulty <= 2) break;
			else  // Protect from Epic Games Store users
			{
				if constexpr (!DEBUG_MODE) { system("cls"); }
				std::cout << "E-error! This is inappropriate... I... What should I...?" << std::endl << std::endl;
				std::cout << "You scared the program with your wrong input. Be careful next time." << std::endl << std::endl;
				system("pause");
			}
		}

			if (difficulty == 2) {
				temple = 1; //Bot will always go first (Kappa)
			}

			if (difficulty >= 0 && difficulty <= 2) { //0 - 2(1 - 3 for user)
				if constexpr (!DEBUG_MODE) system("cls");
				while (fleet_1.get_health() && fleet_2.get_health()) {
					switch (temple % 2) {
					case 0:
						fleet_1.initialize_field_final();
						std::cout << fleet_1.get_name() << " turn." << std::endl << std::endl;
						fleet_1.output_field_final(fleet_2);
						fleet_1.do_action(fleet_2, order[round]);
						break;
					case 1:
						fleet_2.initialize_field_final();
						std::cout << fleet_2.get_name() << " turn." << std::endl << std::endl;
						fleet_2.ai(order[round], difficulty, fleet_1);
						system("pause");
						break;
					}

					if constexpr (!DEBUG_MODE) system("cls");
					if (!fleet_1.get_health() || !fleet_2.get_health()) break;
					temple++;

					switch (temple % 2) {
					case 0:
						fleet_1.initialize_field_final();
						std::cout << fleet_1.get_name() << " turn." << std::endl << std::endl;
						fleet_1.output_field_final(fleet_2);
						fleet_1.do_action(fleet_2, order[round]);
						break;
					case 1:
						fleet_2.initialize_field_final();
						std::cout << fleet_2.get_name() << " turn." << std::endl << std::endl;
						fleet_2.ai(order[round], difficulty, fleet_1);
						system("pause");
						break;
					}
					temple--;
					round++;
					if (order.size() == round) round = 0;
					if constexpr (!DEBUG_MODE) system("cls");
				}
			}
	}
	else if (battle_mode == "missions") {
		std::string mission_number;
		while (true)
		{
			if constexpr (!DEBUG_MODE) { system("cls"); }
			std::cout << "Type the secret mission number: ";
			std::cin >> mission_number;
			if (mission_number == "344460") {
				//Cleaning from Aircraft Carrier
				for (int i = 0; i < fleet_1.get_ship_vector().size();) {
					if (fleet_1.get_ship_vector()[i].get_type()->get_name() == "Aircraft Carrier") {
						fleet_1.remove_ship_from_fleet(fleet_1.get_ship_vector()[i]);
					}
					if (fleet_1.get_ship_by_index(i).get_type()->get_name() != "Aircraft Carrier") i++;
				}
				for (int i = 0; i < fleet_2.get_ship_vector().size();) {
					if (fleet_2.get_ship_vector()[i].get_type()->get_name() == "Aircraft Carrier") {
						fleet_2.remove_ship_from_fleet(fleet_2.get_ship_vector()[i]);
					}
					if (fleet_2.get_ship_by_index(i).get_type()->get_name() != "Aircraft Carrier") i++;
				}
				///////////////////////////////

				int nuclear_id = -1, finder_id = -1, damager_id = -1;
				bool playable_fleet = false; //who will shoot(false - fleet1, true - fleet2)
				if (fleet_2.find_small_ship_id() != -1 && fleet_1.find_heavy_cruiser_ship_id() != -1 && fleet_1.find_tsundere_ship_id() != -1) {
					//nothing
				}
				else if (fleet_1.find_small_ship_id() != -1 && fleet_2.find_heavy_cruiser_ship_id() != -1 && fleet_2.find_tsundere_ship_id() != -1) {
					playable_fleet = true;
				}
				else {
					std::cout << "\nError. To launch, it is necessary that in one fleet there is at least one Small ship, and in the other one Heavy Cruiser ship and one Tsundere ship." << std::endl;
					return -277716;
				}

				switch (playable_fleet) //удаляем ненужные корабли
				{
				case false:
					for (int i = 0; i < fleet_1.get_ship_vector().size();) {
						if (fleet_1.get_ship_by_index(i).get_type()->get_name() == "Small") {
							fleet_1.remove_ship_from_fleet(fleet_1.get_ship_by_index(i));
						}
						if (i < fleet_1.get_ship_vector().size()) {
							if (fleet_1.get_ship_by_index(i).get_type()->get_name() != "Small") i++;
						}
					}
					for (int i = 0; i < fleet_2.get_ship_vector().size();) {
						if (fleet_2.get_ship_by_index(i).get_type()->get_name() == "Tsundere") {
							fleet_2.remove_ship_from_fleet(fleet_2.get_ship_by_index(i));
						}
						if (fleet_2.get_ship_by_index(i).get_type()->get_name() == "Heavy Cruiser") {
							fleet_2.remove_ship_from_fleet(fleet_2.get_ship_by_index(i));
						}
						if (fleet_2.get_ship_by_index(i).get_type()->get_name() != "Tsundere" && fleet_2.get_ship_by_index(i).get_type()->get_name() != "Heavy Cruiser") i++;
					}
					break;
				case true:
					for (int i = 0; i < fleet_2.get_ship_vector().size();) {
						if (fleet_2.get_ship_by_index(i).get_type()->get_name() == "Small") {
							fleet_2.remove_ship_from_fleet(fleet_2.get_ship_by_index(i));
						}
						if (fleet_2.get_ship_by_index(i).get_type()->get_name() != "Small") i++;
					}
					for (int i = 0; i < fleet_1.get_ship_vector().size();) {
						if (fleet_1.get_ship_by_index(i).get_type()->get_name() == "Tsundere") {
							fleet_1.remove_ship_from_fleet(fleet_1.get_ship_by_index(i));
						}
						if (fleet_1.get_ship_by_index(i).get_type()->get_name() == "Heavy Cruiser") {
							fleet_1.remove_ship_from_fleet(fleet_1.get_ship_by_index(i));
						}
						if (fleet_1.get_ship_by_index(i).get_type()->get_name() != "Tsundere" && fleet_1.get_ship_by_index(i).get_type()->get_name() != "Heavy Cruiser") i++;
					}
					break;
				}

				////Clearing fields
				fleet_1.clear_fields();
				fleet_2.clear_fields();
				////Generating fields
				fleet_1.generate_fleet();
				fleet_2.generate_fleet();
				////Initialisation fields
				fleet_1.initialize_field_final();
				fleet_2.initialize_field_final();

				switch (playable_fleet)
				{
				case false:
					nuclear_id = fleet_2.find_small_ship_id();
					finder_id = fleet_1.find_heavy_cruiser_ship_id();
					damager_id = fleet_1.find_tsundere_ship_id();
					break;
				case true:
					nuclear_id = fleet_1.find_small_ship_id();
					finder_id = fleet_2.find_heavy_cruiser_ship_id();
					damager_id = fleet_2.find_tsundere_ship_id();
					break;
				};

				if constexpr (DEBUG_MODE) {
					std::cout << "[MAIN]Playable fleet: " << playable_fleet << std::endl;
					if (playable_fleet) {
						fleet_1.output_field_final(fleet_2);
					}
					else {
						fleet_2.output_field_final(fleet_1);
					}
					fleet_1.print(std::cout);
					fleet_2.print(std::cout);
					std::cout << "[MAIN]nuclear_id = " << nuclear_id << std::endl;
					std::cout << "[MAIN]finder_id = " << finder_id << std::endl;
					std::cout << "[MAIN]damager_id = " << damager_id << std::endl;
				}

				std::cout << std::endl;
				if constexpr (!DEBUG_MODE) system("cls");
				std::cout << "Captain! The enemy intends to use nuclear weapons! The location is unknown, but we know that the missile cave is on one of the enemy single cells. The only way out is to sink it before the bomb explodes." << std::endl << std::endl;
				system("pause");
				if constexpr (!DEBUG_MODE) system("cls");
				bool stop = true;
				while (stop && round < width_height) {
					switch (playable_fleet) {
					case false:
						fleet_1.output_field_final(fleet_2);
						fleet_1.do_action_344460(fleet_2, fleet_1.get_ship_by_index(damager_id));
						fleet_2.initialize_field_final();
						if (!fleet_2.get_ship_by_index(nuclear_id).get_durability_sum()) stop = false;
						break;
					case true:
						fleet_2.output_field_final(fleet_1);
						fleet_2.do_action_344460(fleet_1, fleet_2.get_ship_by_index(damager_id));
						fleet_1.initialize_field_final();
						if (!fleet_1.get_ship_by_index(nuclear_id).get_durability_sum()) stop = false;
						break;
					}
					round++;
				}
				if (round == width_height) {
					std::cout << "Captain! The enemy launched a nuclear missile!" << std::endl;
					std::cout << "You lose!" << std::endl;
					break;
				}
				else {
					std::cout << "Captain! The ship with the missile silo is sunk!" << std::endl;
					std::cout << "You won!" << std::endl;
					give_achievement(achievement_array, 4);
					break;
				}
			}
			else {
				if constexpr (!DEBUG_MODE) { system("cls"); }
				std::cout << "E-error! This is inappropriate... I... What should I...?" << std::endl << std::endl;
				std::cout << "You scared the program with your wrong input. Be careful next time." << std::endl << std::endl;
				system("pause");
			}
		}
	}
	else  // Protect from Epic Games Store users
	{
		if constexpr (!DEBUG_MODE) { system("cls"); }
		std::cout << "E-error! This is inappropriate... I... What should I...?" << std::endl << std::endl;
		std::cout << "You scared the program with your wrong input. Be careful next time." << std::endl << std::endl;
		system("pause");
	}

	//Issuance of achievements after the game
	if (battle_mode == "pve" || battle_mode == "pvp") {
		if (fleet_1.get_health() > fleet_2.get_health()) {
			std::cout << "=====" << fleet_1.get_name() << " won!" << "=====" << std::endl;
			if (battle_mode == "pve" && difficulty < 2 && ironman) {
				give_achievement(achievement_array, difficulty);
			}
		}
		else if (fleet_1.get_health() < fleet_2.get_health()) {
			std::cout << "=====" << fleet_2.get_name() << " won!" << "=====" << std::endl;
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
	}

	//Let's output fleets to the file output.txt (names in the project parameters)
	if (argc > 1)
	{
		std::ofstream out(argv[1]);
		fleet_1.print(out);
		fleet_2.print(out);
		out.close();
	}
	system("pause");
	return 0;
}