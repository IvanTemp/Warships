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
			std::cout << "================" << std::endl;
			std::cout << "Seed: " << time(nullptr) << std::endl;
			std::cout << "================" << std::endl;
		}
		break;
	default:
		srand(SEED);
		if constexpr (DEBUG_MODE) {
			std::cout << "======================" << std::endl;
			std::cout << "[MAIN]Seed: " << SEED << std::endl;
			std::cout << "======================" << std::endl;
		}
		break;
	}

	if constexpr (DEBUG_MODE) {
		std::cout << "=======================" << std::endl;
		std::cout << "WARNING! DEBUG MODE ON!" << std::endl;
		std::cout << "=======================" << std::endl;
	}

	if constexpr (width_height > 26) {
		std::cout << "=================================================================================================" << std::endl;
		std::cout << "Warning! The game is not designed for such a large field size! Please limit yourself to 26 cells!" << std::endl;
		std::cout << "=================================================================================================" << std::endl;
		system("pause");
		return -26;
	}

	if constexpr (width_height != 10) {
		std::cout << "===============================================================================" << std::endl;
		std::cout << "Warning! You are using an experimental field size(" << width_height << ").\nPlease increase the size of the window to full or change the size of the field." << std::endl;
		std::cout << "===============================================================================" << std::endl << std::endl;
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
		fin.close();
		//Check fleet_2 for empty
		if (fleet_2.get_ship_vector().empty()) {
			std::cout << "Warning! Connect the file with the second fleet!" << std::endl;
			system("pause");
			return -2;
		}
	}
	//else //��� �������, �� ������ ���� ���!!!!!11111!
	//{
	//	std::ifstream fin("input.txt");
	//	fleet_2.read(fin);
	//	fin.close();
	//	//Check fleet_2 for empty
	//	if (fleet_2.get_ship_vector().empty()) {
	//		std::cout << "Warning! Connect the file with the second fleet!" << std::endl;
	//		system("pause");
	//		return -2;
	//	}
	//}

	////////
	fleet_1.print(std::cout);
	std::cout << std::endl;
	fleet_2.print(std::cout);
	std::cout << std::endl;
	
	//Gemu ga hajimarimasu(прим. переводчика: Игра начинается)
	bool ironman = true;
	fleet_1.generate_field();
	fleet_2.generate_field();
	///////////////

	//Order
	std::vector <int> order = first_order(std::max(fleet_1.get_ship_vector().size(), fleet_2.get_ship_vector().size()));
	//std::vector <int> order = { 1 };
	///////

	//DEBUG FUNCTIONS
	if constexpr (DEBUG_MODE) {
		std::cout << std::endl;
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

	if (fleet_1 != fleet_2) {
		std::cout << "Imbalance! Achievements are disabled." << std::endl << std::endl;
		ironman = false;
	}

	//Achievements
	std::vector <std::pair<std::string, bool>> achievement_array = read_achievements();
	if (ironman) output_achievement_info(achievement_array);
	//////////////

	std::cout << "Start game?\n";
	system("pause");

	if constexpr (!DEBUG_MODE) { system("cls"); }

	//Selecting a game mode
	std::string battle_mode;
	while (true)
	{
		std::cout << "Select game mode: \n-PvP\n-PvE\n-Arcade\n\n";
		std::cin >> battle_mode;
		ha_you_are_small_now(battle_mode);
		if (battle_mode == "pve" || battle_mode == "e" || battle_mode == "pvp" || battle_mode == "p" || battle_mode == "arcade" || battle_mode == "a")
		{
			break;
		}
		if constexpr (!DEBUG_MODE) { system("cls"); }
		std::cout << "E-error! This is inappropriate... I... What should I...?" << std::endl << std::endl;
		std::cout << "You scared the program with your wrong input. Be careful next time." << std::endl << std::endl;
		system("pause");
		if (!DEBUG_MODE) system("cls");
	}

	int difficulty = 0, round = 0, temple = rand() % 2;
	std::string arcade_game_number;
	if (battle_mode == "pvp" || battle_mode == "p") { //PVP
		if constexpr (!DEBUG_MODE) system("cls");
		while (fleet_1.get_health_sum() && fleet_2.get_health_sum()) {
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
			if (!fleet_1.get_health_sum() || !fleet_2.get_health_sum()) break;
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
				if (!DEBUG_MODE) system("cls");
			}
		}

			if (difficulty == 2) {
				temple = 1; //Bot will always go first (Kappa)
			}

			if (difficulty >= 0 && difficulty <= 2) { //0 - 2(1 - 3 for user)
				if constexpr (!DEBUG_MODE) system("cls");
				while (fleet_1.get_health_sum() && fleet_2.get_health_sum()) {
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
					if (!fleet_1.get_health_sum() || !fleet_2.get_health_sum()) break;
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
	else if (battle_mode == "arcade" || battle_mode == "a") {
		while (true)
		{
			if constexpr (!DEBUG_MODE) { system("cls"); }
			std::cout << "Arcade games list: " << std::endl << std::endl;
			std::cout << "1) Standard Warships - Primitive" << std::endl << std::endl;
			std::cout << "2) Standard Warships - Impossible" << std::endl << std::endl;
			if (achievement_array[6].second) {
				std::cout << "344460) Nuclear finders" << std::endl << std::endl;
			}
			if (achievement_array[7].second) {
				std::cout << "354735) Shipsweeper" << std::endl << std::endl;
			}

			if (!achievement_array[6].second && !achievement_array[7].second) {
				std::cout << "and two secret arcade games.." << std::endl << std::endl;
			}
			else if (!achievement_array[6].second || !achievement_array[7].second) {
				std::cout << "and one secret arcade game.." << std::endl << std::endl;
			}
			std::cout << "Type the mission number: ";
			std::cin >> arcade_game_number;

			if (arcade_game_number == "1") {
				//Стандартный морской бой - примитивный бот
				if constexpr (!DEBUG_MODE) system("cls");
				std::cout << "Standard warships on normal difficulty." << std::endl;
				system("pause");
				if constexpr (!DEBUG_MODE) system("cls");

				//first re-initialization
				fleet_1.initialize_field_final();
				fleet_2.initialize_field_final();

				//Oneing durability
				fleet_1.oneing_durability();
				fleet_2.oneing_durability();

				temple = rand() % 2; //Bot will always go first (Kappa)

				while (fleet_1.get_health_sum() && fleet_2.get_health_sum())
				{
					switch (temple % 2) {
					case 0:
						//Player
						fleet_1.initialize_field_final();
						std::cout << fleet_1.get_name() << " turn." << std::endl << std::endl;
						fleet_1.output_field_final(fleet_2);
						std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
						fleet_2.damage_by_index_player_simple();
						system("pause");
						break;
					case 1:
						//bot
						fleet_2.initialize_field_final();
						std::cout << fleet_2.get_name() << " turn." << std::endl << std::endl;
						fleet_1.damage_by_index_bot_primitive();
						system("pause");
						break;
					}
					temple++;
					if (!DEBUG_MODE) system("cls");
				}
				if (fleet_1.get_health_sum()) give_achievement(achievement_array, 4);
				break;
			}
			else if (arcade_game_number == "2") {
				//Стандартный морской бой - невозможно
				if constexpr (!DEBUG_MODE) system("cls");
				std::cout << "Standard warships on impossible difficulty." << std::endl;
				system("pause");
				if constexpr (!DEBUG_MODE) system("cls");

				//first re-initialization
				//fleet_1.initialize_field_final();
				//fleet_2.initialize_field_final();
				//не помню зачем это написал, но и без этого работает :\

				//Oneing durability
				fleet_1.oneing_durability();
				fleet_2.oneing_durability();

				temple = 1; //Bot will always go first (Kappa)

				while (fleet_1.get_health_sum() && fleet_2.get_health_sum())
				{
					switch (temple % 2) {
					case 0:
						//Player
						fleet_1.initialize_field_final();
						std::cout << fleet_1.get_name() << " turn." << std::endl << std::endl;
						fleet_1.output_field_final(fleet_2);
						std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
						fleet_2.damage_by_index_player_simple();
						system("pause");
						break;
					case 1:
						//bot
						fleet_2.initialize_field_final();
						std::cout << fleet_2.get_name() << " turn." << std::endl << std::endl;
						fleet_1.damage_by_index_bot_simple();
						system("pause");
						break;
					}
					temple++;
					if (!DEBUG_MODE) system("cls");
				}
				if (fleet_1.get_health_sum()) give_achievement(achievement_array, 5);
			break;
			} 
			else if (arcade_game_number == "344460") {
				//кастомка, которую один из кодеров(не Ваня) сделал со скуки
				//Cleaning from Aircraft Carrier
				for (int i = 0; i < fleet_1.get_ship_vector().size();) {
					if (fleet_1.get_ship_vector()[i].get_type()->get_size() == 4) {
						fleet_1 -= fleet_1.get_ship_vector()[i];
					}
					if (fleet_1.get_ship_by_index(i).get_type()->get_size() != 4) i++;
				}
				for (int i = 0; i < fleet_2.get_ship_vector().size();) {
					if (fleet_2.get_ship_vector()[i].get_type()->get_size() == 4) {
						fleet_2 -= fleet_2.get_ship_vector()[i];
					}
					if (fleet_2.get_ship_by_index(i).get_type()->get_size() != 4) i++;
				}
				///////////////////////////////

				int nuclear_id = -1, finder_id = -1, damager_id = -1;
				bool playable_fleet = false; //who will shoot(false - fleet1, true - fleet2)
				if (fleet_1.find_undead_small_ship_id() != -1 && fleet_2.find_undead_heavy_cruiser_ship_id() != -1 && fleet_2.find_undead_tsundere_ship_id() != -1) {
					playable_fleet = true;
				}
				else {
					std::cout << "\nError. To launch, it is necessary that in one fleet there is at least one Small ship, and in the other one Heavy Cruiser ship and one Tsundere ship." << std::endl;
					return -277716;
				}

				switch (playable_fleet) //was comment
				{
				case false:
					for (int i = 0; i < fleet_1.get_ship_vector().size();) {
						if (fleet_1.get_ship_by_index(i).get_type()->get_size() == 1) {
							fleet_1 -= fleet_1.get_ship_by_index(i);
						}
						if (i < fleet_1.get_ship_vector().size()) {
							if (fleet_1.get_ship_by_index(i).get_type()->get_size() != 1) i++;
						}
					}
					for (int i = 0; i < fleet_2.get_ship_vector().size();) {
						if (fleet_2.get_ship_by_index(i).get_type()->get_size() == 2) {
							fleet_2 -= fleet_2.get_ship_by_index(i);
						}
						if (fleet_2.get_ship_by_index(i).get_type()->get_size() == 3) {
							fleet_2 -= fleet_2.get_ship_by_index(i);
						}
						if (fleet_2.get_ship_by_index(i).get_type()->get_size() != 2 && fleet_2.get_ship_by_index(i).get_type()->get_size() != 3) i++;
					}
					break;
				case true:
					for (int i = 0; i < fleet_2.get_ship_vector().size();) {
						if (fleet_2.get_ship_by_index(i).get_type()->get_size() == 1) {
							fleet_2 -= fleet_2.get_ship_by_index(i);
						}
						if (fleet_2.get_ship_by_index(i).get_type()->get_size() != 1) i++;
					}
					for (int i = 0; i < fleet_1.get_ship_vector().size();) {
						if (fleet_1.get_ship_by_index(i).get_type()->get_size() == 2) {
							fleet_1 -= fleet_1.get_ship_by_index(i);
						}
						if (fleet_1.get_ship_by_index(i).get_type()->get_size() == 3) {
							fleet_1 -= fleet_1.get_ship_by_index(i);
						}
						if (fleet_1.get_ship_by_index(i).get_type()->get_size() != 2 && fleet_1.get_ship_by_index(i).get_type()->get_size() != 3) i++;
					}
					break;
				}

				////Clearing fields
				fleet_1.clear_fields();
				fleet_2.clear_fields();
				////Generating fields
				fleet_1.generate_field();
				fleet_2.generate_field();
				////Initialisation fields
				fleet_1.initialize_field_final();
				fleet_2.initialize_field_final();

				switch (playable_fleet)
				{
				case false:
					nuclear_id = fleet_2.find_undead_small_ship_id();
					finder_id = fleet_1.find_undead_heavy_cruiser_ship_id();
					damager_id = fleet_1.find_undead_tsundere_ship_id();
					break;
				case true:
					nuclear_id = fleet_1.find_undead_small_ship_id();
					finder_id = fleet_2.find_undead_heavy_cruiser_ship_id();
					damager_id = fleet_2.find_undead_tsundere_ship_id();
					break;
				}

				if constexpr (DEBUG_MODE) {
					std::cout << "[344460]Playable fleet: " << playable_fleet << std::endl << std::endl << "[344460]Enemy field: " << std::endl;
					if (playable_fleet) {
						fleet_1.output_field_final(fleet_2);
					}
					else {
						fleet_2.output_field_final(fleet_1);
					}
					std::cout << "[344460]Fleets info:" << std::endl;
					fleet_1.print(std::cout);
					std::cout << std::endl;
					fleet_2.print(std::cout);
					std::cout << "\n[344460]nuclear_id = " << nuclear_id << std::endl;
					std::cout << "[344460]finder_id = " << finder_id << std::endl;
					std::cout << "[344460]damager_id = " << damager_id << std::endl;
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
					give_achievement(achievement_array, 6);
					break;
				}
			}
			else if (arcade_game_number == "354735") {
			//ещё одна кастомка, которую один из кодеров(всё ещё не Ваня) сделал со скуки
			//по задумке это должен был быть PvE, но кому-то(и тут не Ваня) было лень писать ИИ под это
			if constexpr (!DEBUG_MODE) system("cls");
			std::cout << "PvP Mode, But It's Minesweeper" << std::endl;
			system("pause");
			if constexpr (!DEBUG_MODE) system("cls");

			//rebuild fields for shipsweeper
			fleet_1.rebuild_fields_for_shipsweeper();
			fleet_2.rebuild_fields_for_shipsweeper();

			temple = rand() % 2; //who will go first

			if constexpr (DEBUG_MODE) {
				std::cout << "[SHIPSWEEPER]" << std::endl;
				fleet_1.output_field_final(fleet_2);
				fleet_2.output_field_final(fleet_1);
				std::cout << "[/SHIPSWEEPER]" << std::endl;
			}

			bool bad = true;

			while (!fleet_1.check_good_end_game_shipsweeper() && !fleet_2.check_good_end_game_shipsweeper() && bad)
			{
				switch (temple % 2) {
				case 0:
					//Player 1
					bad = !fleet_1.check_bad_end_game_shipsweeper();
					if (!bad) break;
					std::cout << fleet_1.get_name() << " turn." << std::endl << std::endl;
					std::cout << "You have " << fleet_1.count_remaining_markers_shipsweeper() << " markers left." << std::endl;
					fleet_1.output_field_final_shipsweeper(fleet_2);
					temple += fleet_1.play_shipsweeper();
					break;
				case 1:
					//Player 1+1
					bad = !fleet_2.check_bad_end_game_shipsweeper();
					if (!bad) break;
					std::cout << fleet_2.get_name() << " turn." << std::endl << std::endl;
					std::cout << "You have " << fleet_2.count_remaining_markers_shipsweeper() << " markers left." << std::endl;
					fleet_2.output_field_final_shipsweeper(fleet_1);
					temple += fleet_2.play_shipsweeper();
					break;
				}
				temple++;
				if (!DEBUG_MODE) system("cls");
			}
			if (fleet_1.check_bad_end_game_shipsweeper()) {
				std::cout << fleet_2.get_name() << " win." << std::endl << std::endl;
				fleet_1.output_field_final_shipsweeper(fleet_2);
			}
			else if (fleet_2.check_bad_end_game_shipsweeper()) {
				std::cout << fleet_1.get_name() << " win." << std::endl << std::endl;
				fleet_2.output_field_final_shipsweeper(fleet_1);
			}
			else if (fleet_1.check_good_end_game_shipsweeper()) {
				std::cout << fleet_1.get_name() << " win." << std::endl << std::endl;
				fleet_1.output_field_final_shipsweeper(fleet_2);
			}
			else {
				std::cout << fleet_2.get_name() << " win." << std::endl << std::endl;
				fleet_2.output_field_final_shipsweeper(fleet_1);
			}
			give_achievement(achievement_array, 7);
			system("pause");
			break;
			}
			else {
				if constexpr (!DEBUG_MODE) { system("cls"); }
				std::cout << "E-error! This is inappropriate... I... What should I...?" << std::endl << std::endl;
				std::cout << "You scared the program with your wrong input. Be careful next time." << std::endl << std::endl;
				system("pause");
				if (!DEBUG_MODE) system("cls");
			}
		}
	}
	else  // Protect from Epic Games Store users
	{
		if constexpr (!DEBUG_MODE) { system("cls"); }
		std::cout << "E-error! This is inappropriate... I... What should I...?" << std::endl << std::endl;
		std::cout << "You scared the program with your wrong input. Be careful next time." << std::endl << std::endl;
		system("pause");
		if (!DEBUG_MODE) system("cls");
	}

	//Issuance of achievements after the game
	if (arcade_game_number != "344460") {
		if (fleet_1.get_health_sum() > fleet_2.get_health_sum()) {
			std::cout << "=====" << fleet_1.get_name() << " won!" << "=====" << std::endl;
			if (battle_mode == "pve" && difficulty < 2 && ironman) {
				give_achievement(achievement_array, difficulty);
			}
		}
		else if (fleet_1.get_health_sum() < fleet_2.get_health_sum()) {
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
	if (arcade_game_number != "344460") {
		system("pause");
	}
	return 0;
}