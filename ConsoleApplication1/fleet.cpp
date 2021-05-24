#include <string>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <map>
#include "Fleet.h"

Fleet::Fleet() {
	resize_fields();
}

Fleet::Fleet(const std::string& nm) :name_(nm) {
	resize_fields();
}

Fleet::Fleet(const std::string& nm, const std::vector<Ship>& v) : name_(nm), ship_vector_(v) {
	resize_fields();
}

void Fleet::resize_fields() {
	field_final_.resize(width_height);
	for (int i = 0; i < field_final_.size(); i++) {
		field_final_[i].resize(width_height);
	}
	field_id_.resize(width_height);
	for (int i = 0; i < field_id_.size(); i++) {
		field_id_[i].resize(width_height);
	}
	field_war_.resize(width_height);
	for (int i = 0; i < field_war_.size(); i++) {
		field_war_[i].resize(width_height);
	}
}

void Fleet::print(std::ostream& out) const {
	out << "=====Fleet " << name_ << "=====" << std::endl;
	if (!ship_vector_.empty()) [[likely]] {
		for (const auto& x : ship_vector_)
		{
			x.print(out);
		}
	}
	else {
		out << "Fleet is empty" << std::endl;
	}
}

void Fleet::read(std::istream& in) {
	std::getline(in, name_);
	while(!(in.eof())) {
		Ship new_ship;
		new_ship.read(in);
		*this += new_ship;
	}
}

std::string Fleet::get_name() const {
	return name_;
}

std::vector<Ship> Fleet::get_ship_vector() const {
	return ship_vector_;
}

int Fleet::get_health_sum() const {
	int hp = 0;
	for (auto& i : ship_vector_)
	{
		for (int j = 0; j < i.get_durability().size(); j++)
		{
			hp += i.get_durability()[j];
		}
	}
	return hp;
}

Ship Fleet::get_ship_by_index(const int id)const {
	return ship_vector_.at(id);
}

void Fleet::damage_by_index_bot(Ship sheep, int difficulty) { //sheep - who is attack
	std::vector <std::pair <int, int>> bot_memory; //BOT Repository Of Detected Cells
	bool guras_bool = true; //Gura was still unable to plant a large tree
	int x = 0, y = 0, attempts = 0;
	int dmg = sheep.get_type()->get_damage_value();

	if (difficulty == 2) {
		difficulty = 49;
		if (find_undead_aircraft_carrier_ship_id() != -1 && sheep.get_type()->get_size() == 1) {
			int aircraft_carrier_ship_id = find_undead_aircraft_carrier_ship_id();
			std::vector<std::pair<int, int>> coordinates = find_ship_and_return_x_y_vector(aircraft_carrier_ship_id + 2);
			for (int i = 0; i < coordinates.size(); i++) {
				if (ship_vector_[aircraft_carrier_ship_id].get_durability()[field_id_[coordinates[i].first][coordinates[i].second].second] > 0) {
					x = coordinates[i].first;
					y = coordinates[i].second;
					break;
				}
			}
			guras_bool = false;
		}

		if (find_undead_small_ship_id() != -1 && sheep.get_type()->get_size() == 2) {
			int small_ship_id = find_undead_small_ship_id();
			if (ship_vector_[small_ship_id].get_durability_sum() > 0) {
				std::vector<std::pair<int, int>> coordinates = find_ship_and_return_x_y_vector(small_ship_id + 2);
				for (int i = 0; i < coordinates.size(); i++) {
					if (ship_vector_[small_ship_id].get_durability()[field_id_[coordinates[i].first][coordinates[i].second].second] > 0) {
						x = coordinates[i].first;
						y = coordinates[i].second;
						break;
					}
				}
				guras_bool = false;
			}
		}
	}

	if constexpr (DEBUG_MODE) {
		std::cout << "[DEFAULT DAMAGE BOT]bot_memory:" << std::endl;
		for (int i = 0; i < bot_memory.size(); i++) {
			std::cout << "[DEFAULT DAMAGE BOT]X = " << bot_memory[i].first << "; Y = " << bot_memory[i].second << std::endl;
		}
	}

	remember_founded_ships(bot_memory);

	while (guras_bool && attempts < difficulty + 1) {
		if (bot_memory.empty()) {//I)We scan for the number of unexplored cells and the presence of ships on them, select the most suitable one (if the difficulty is hard)
			x = rand() % (width_height - 1);
			y = rand() % (width_height - 1);
			if constexpr (DEBUG_MODE) { std::cout << "[DEFAULT DAMAGE BOT]rand_x = " << x << "; rand_y = " << y << std::endl; }
			if (field_id_[x][y].first > 1 && !field_war_[x][y]) guras_bool = false;
			attempts++;
		}
		else { //II)Finishing off found ships
			x = bot_memory[rand() % bot_memory.size()].first;
			y = bot_memory[rand() % bot_memory.size()].second;
			guras_bool = false;
		}
	}

	bot_memory.clear();

	if constexpr (DEBUG_MODE) std::cout << "[DEFAULT DAMAGE BOT]Gura AI(c) decided that: x = " << x << "; y = " << y << std::endl;

	const char str_x = int_to_letter(x);

	if (field_id_[x][y].first > 1) {
		if (ship_vector_[field_id_[x][y].first - 2].get_type()->get_size() == 1 && sheep.get_type()->get_size() == 2) {
			dmg = ship_vector_[field_id_[x][y].first - 2].get_type()->get_default_durability();
		}
		else if (ship_vector_[field_id_[x][y].first - 2].get_type()->get_size() == 4 && sheep.get_type()->get_size() == 1) {
			dmg *= 2;
		}
		get_damage(dmg, x, y);
		if (ship_vector_[field_id_[x][y].first - 2].get_durability_sum()) {
			bot_memory.emplace_back(std::make_pair(x, y));
		}
	}
	else {
		std::cout << "Miss!" << std::endl;
	}
	field_get_vision(x, y);
}

void Fleet::damage_by_index_bot_simple() {
	for (int y = 0; y < width_height; y++) {
		for (int x = 0; x < width_height; x++) {
			if (field_id_[x][y].first > 1) {
				if (ship_vector_[field_id_[x][y].first - 2].get_durability()[field_id_[x][y].second]) {
					get_damage(1, x, y);
					//there should be a code that gives a vision to the point that the bot shot, but why, if the bot shoots only at the cells with ships?
					return;
				}
			}
		}
	}
}

void Fleet::damage_by_index_bot_primitive() {
	int x = rand() % width_height, y = rand() % width_height;
	if (field_id_[x][y].first > 1) get_damage(1, x, y);
	else std::cout << "Miss!" << std::endl;
	field_get_vision(x, y);
}

void Fleet::ai(const int current_ship_id, const int difficulty, Fleet& fleet_of_player) {
	//Gura AI(not copyrighted) Reborn v1.13.2
	srand(time(nullptr));
	const std::string type = ship_vector_[current_ship_id].get_type()->get_name();

	if (ship_vector_.size() > current_ship_id) [[likely]] {
		if (ship_vector_[current_ship_id].get_durability_sum() || difficulty == 2) [[likely]] {
			std::cout << "Bot's ship is " << type << std::endl;
			if constexpr (DEBUG_MODE) std::cout << "[GURA AI]Current position: " << int_to_letter(find_ship_and_return_x_y_vector(current_ship_id + 2)[0].first) << find_ship_and_return_x_y_vector(current_ship_id + 2)[0].second << std::endl;

			if (type == "Small") {
				const std::pair <int, int> coordinates = find_ship_and_return_x_y_vector(current_ship_id + 2)[0];
				if (!field_war_[coordinates.first][coordinates.second]) {
					//If the ship is not found, then we attack
					fleet_of_player.damage_by_index_bot(ship_vector_[current_ship_id], difficulty);
				}
				else {
					//move
					std::vector<std::pair<int, int>> possible_coordinates;
					field_id_[coordinates.first][coordinates.second].first = 0;
					for (int y = coordinates.second - 1; y < coordinates.second + 2; y++) {
						for (int x = coordinates.first - 1; x < coordinates.first + 2; x++) {
							if (x >= 0 && x < width_height && y >= 0 && y < width_height) {
								if (area_is_clear(x, y) && !field_war_[x][y]) {
									//If the cell is emptyand unexplored
									possible_coordinates.emplace_back(std::make_pair(x, y));
								}
							}
						}
					}
					field_id_[coordinates.first][coordinates.second].first = current_ship_id + 2;
					if (possible_coordinates.size() > 1) {
						small_move_bot(possible_coordinates[rand() % possible_coordinates.size()], coordinates, current_ship_id);
						initialize_field_final();
					}
					else if (possible_coordinates.size() == 1) {
						small_move_bot(possible_coordinates[0], coordinates, current_ship_id);
						initialize_field_final();
					}
					else {
						field_id_[coordinates.first][coordinates.second].first = current_ship_id + 2;
						fleet_of_player.damage_by_index_bot(ship_vector_[current_ship_id], difficulty); //if there is nowhere to swim
					}
				}
			}
			else if (type == "Tsundere") {
				if (ship_vector_[current_ship_id].get_durability_sum() == ship_vector_[current_ship_id].get_type()->get_default_durability() * ship_vector_[current_ship_id].get_type()->get_size()) {
					//Если хп полное
					fleet_of_player.damage_by_index_bot(ship_vector_[current_ship_id], difficulty);
				}
				else {
					//repair
					ship_vector_[current_ship_id]++;
					std::cout << "Ship repaired!" << std::endl;
					initialize_field_final();
				}
			}
			else if (type == "Heavy Cruiser") {
				fleet_of_player.heavy_cruiser_attack_bot(ship_vector_[current_ship_id].get_type()->get_damage_value(), difficulty);
				fleet_of_player.initialize_field_final();
			}
			else {
				fleet_of_player.aircraft_attack_bot(ship_vector_[current_ship_id].get_type()->get_damage_value(), difficulty);
			}
		}
		else {
			std::cout << "This ship is sunk, bot miss this turn." << std::endl;
			if constexpr (!DEBUG_MODE) system("cls");
			return;
		}
	}
	else {
		 std::cout << "This ship disapperared, you bot this turn." << std::endl;
		 if constexpr (!DEBUG_MODE) system("cls");
		 return;
	}
}

void Fleet::damage_by_index_player(Ship &sheep) { //sheep - who is attack
	int x = 0, y = 0;
	bool not_idiot = true, negative = false;
	char char_x = ' ';
	int dmg = sheep.get_type()->get_damage_value();
	std::string str_y;
	std::cin >> char_x >> str_y;
	if constexpr (DEBUG_MODE) std::cout << "[DEFAULT DAMAGE PLAYER]X = " << char_x << "; Y = " << str_y << std::endl;

	for (int i = 0; i < str_y.length(); i++) {
		if (str_y[i] >= '0' && str_y[i] <= '9') {
			not_idiot = false;
			y *= 10;
			y += str_y[i] - '0';
		}
		if (str_y[i] == '-') {
			negative = true;
		}
	}

	if (not_idiot) y = letter_to_int(std::toupper(str_y[0]));
	if (negative) y *= -1;

	if (y > width_height - 1 || y < 0) {
		std::cout << "Captain! You shot out of bounds!" << std::endl;
		return;
	}
	
	char_x = std::toupper(char_x);
	x = letter_to_int(char_x);
	if (x > width_height - 1 || x < 0) {
		std::cout << "Captain! You shot out of bounds!" << std::endl;
		return;
	}

	if constexpr (DEBUG_MODE) { std::cout << "[DEFAULT DAMAGE PLAYER]int X = " << x << " Y = " << y << std::endl; }

	if (field_id_[x][y].first > 1) {
		if (ship_vector_[field_id_[x][y].first - 2].get_durability()[field_id_[x][y].second]) {
		if (ship_vector_[field_id_[x][y].first - 2].get_type()->get_size() == 4 && sheep.get_type()->get_size() == 1) {
				dmg *= 2;
			}
			get_damage(dmg, x, y);
		}
		else {
			std::cout << "Why did you shoot at an already sunk cell?" << std::endl;
		}
	}
	else {
		std::cout << "Miss!" << std::endl;
	}
	field_get_vision(x, y);
}

void Fleet::damage_by_index_player_simple() {
	int x = 0, y = 0;
	bool not_idiot = true, negative = false;
	char char_x = ' ';
	std::string str_y;
	std::cin >> char_x >> str_y;
	if constexpr (DEBUG_MODE) std::cout << "[DEFAULT DAMAGE PLAYER SIMPLE]X = " << char_x << "; Y = " << str_y << std::endl;

	for (int i = 0; i < str_y.length(); i++) {
		if (str_y[i] >= '0' && str_y[i] <= '9') {
			not_idiot = false;
			y *= 10;
			y += str_y[i] - '0';
		}
		if (str_y[i] == '-') {
			negative = true;
		}
	}

	if (not_idiot) y = letter_to_int(std::toupper(str_y[0]));
	if (negative) y *= -1;

	if (y > width_height - 1 || y < 0) {
		std::cout << "Captain! You shot out of bounds!" << std::endl;
		return;
	}

	char_x = std::toupper(char_x);
	x = letter_to_int(char_x);
	if (x > width_height - 1 || x < 0) {
		std::cout << "Captain! You shot out of bounds!" << std::endl;
		return;
	}

	if constexpr (DEBUG_MODE) { std::cout << "[DEFAULT DAMAGE PLAYER SIMPLE]int X = " << x << " Y = " << y << std::endl; }

	if (field_id_[x][y].first > 1) {
		if (ship_vector_[field_id_[x][y].first - 2].get_durability()[field_id_[x][y].second]) {
			get_damage(1, x, y);
		}
		else {
			std::cout << "Why did you shoot at an already sunk cell?" << std::endl;
		}
	}
	else {
		std::cout << "Miss!" << std::endl;
	}
	field_get_vision(x, y);
}

int Fleet::play_shipsweeper() {
	std::string action;
	std::cout << "What do you want? (Write command and coordinates)\n\n-Shoot \n-Place_mark\n-Delete_mark" << std::endl;
	std::cin >> action;
	ha_you_are_small_now(action);
	int x = 0, y = 0;
	bool not_idiot = true, negative = false;
	char char_x = ' ';
	std::string str_y;
	std::cin >> char_x >> str_y;
	if constexpr (DEBUG_MODE) std::cout << "[PLAY SHIPSWEEPER]X = " << char_x << "; Y = " << str_y << std::endl;

	for (int i = 0; i < str_y.length(); i++) {
		if (str_y[i] >= '0' && str_y[i] <= '9') {
			not_idiot = false;
			y *= 10;
			y += str_y[i] - '0';
		}
		if (str_y[i] == '-') {
			negative = true;
		}
	}

	if (not_idiot) y = letter_to_int(std::toupper(str_y[0]));
	if (negative) y *= -1;

	if (y > width_height - 1 || y < 0) {
		std::cout << "Captain! Out of bounds!" << std::endl;
		system("pause");
		return -1;
	}

	char_x = std::toupper(char_x);
	x = letter_to_int(char_x);
	if (x > width_height - 1 || x < 0) {
		std::cout << "Captain! Out of bounds!" << std::endl;
		system("pause");
		return -1;
	}

	if constexpr (DEBUG_MODE) { std::cout << "[PLAY SHIPSWEEPER]int X = " << x << " Y = " << y << std::endl; }

	if (action == "shoot" || action == "s") {
		std::cout << "Shooted" << std::endl;
		system("pause");
		if (field_id_[x][y].first == -1) {
			if constexpr (!DEBUG_MODE) system("cls");
			field_get_vision(x, y);
			return -1;
		}
		else {
			open_cells(x, y);
		}
	}
	else if (action == "place_mark" || action == "p") {
		if (count_remaining_markers_shipsweeper()) {
			if (!field_id_[x][y].second) {
				field_id_[x][y].second = 1;
				std::cout << "Placed!" << std::endl;
			}
			else {
				std::cout << "The mark is already there!" << std::endl;
			}
		}
		else {
			std::cout << "You have no marks!" << std::endl;
		}
		system("pause");
		if constexpr (!DEBUG_MODE) system("cls");
		return -1;
	}
	else if (action == "delete_mark" || action == "d") {
		if (field_id_[x][y].second) {
			field_id_[x][y].second = 0;
			std::cout << "Deleted!" << std::endl;
		}
		else {
			std::cout << "There is no mark!" << std::endl;
		}
		system("pause");
		if constexpr (!DEBUG_MODE) system("cls");
		return -1;
	}
	else {
		std::cout << "Wrong command!" << std::endl;
		system("pause");
		if constexpr (!DEBUG_MODE) system("cls");
		return -1;
	}
	return 0;
}

bool Fleet::check_bad_end_game_shipsweeper()const {
	for (int y = 0; y < width_height; y++) {
		for (int x = 0; x < width_height; x++) {
			if (field_id_[x][y].first == -1 && field_war_[x][y]) return true;
		}
	}
	return false;
}

bool Fleet::check_good_end_game_shipsweeper()const {
	for (int y = 0; y < width_height; y++) {
		for (int x = 0; x < width_height; x++) {
			if (field_id_[x][y].first == -1 && !field_id_[x][y].second) return false;
		}
	}
	return true;
}

int Fleet::count_remaining_markers_shipsweeper()const {
	int counter = 0;
	for (int y = 0; y < width_height; y++) {
		for (int x = 0; x < width_height; x++) {
			if (field_id_[x][y].first == -1) counter++;
			if (field_id_[x][y].second == 1) counter--;
		}
	}
	return counter;
}

void Fleet::oneing_durability() {
	std::vector<int> temp;
	for (auto& i : ship_vector_) {
		temp.clear();
		for (int j = 0; j < i.get_durability().size(); j++) {
			temp.emplace_back(1);
		}
		i.set_durability(temp);
	}
}

void Fleet::aircraft_attack_player(const int dmg) {
	//Get angle (horizontal/vertical)
	bool angle = 0;
	std::string str_angle = "";
	while (true) {
		std::cin >> str_angle;
		if (str_angle == "1x3" || str_angle == "1" || str_angle == "v") {
			angle = 0;
			break;
		}
		else if (str_angle == "3x1" || str_angle == "3" || str_angle == "h") {
			angle = 1;
			break;
		}
		else {
			std::cout << "Wrong command\n";
		}
	}
	//Get XY
	int x = 0, y = 0;
	bool not_idiot = true, negative = false;
	char char_x = ' ';
	std::string str_y;
	std::cin >> char_x >> str_y;
	if constexpr (DEBUG_MODE) std::cout << "[AIRCRAFT ATTACK PLAYER]X = " << char_x << "; Y = " << str_y << ";" << std::endl;

	for (int i = 0; i < str_y.length(); i++) {
		if (str_y[i] >= '0' && str_y[i] <= '9') {
			not_idiot = false;
			y *= 10;
			y += str_y[i] - '0';
		}
		if (str_y[i] == '-') {
			negative = true;
		}
	}

	if (not_idiot) y = letter_to_int(std::toupper(str_y[0]));
	if (negative) y *= -1;

	//Check out of bounds
	if (y > width_height - 1 || y < 0) {
		std::cout << "Captain! You shot out of bounds!" << std::endl;
		return;
	}

	char_x = std::toupper(char_x);
	x = letter_to_int(char_x);
	if (x > width_height - 1 || x < 0) {
		std::cout << "Captain! You shot out of bounds!" << std::endl;
		return;
	}

	if constexpr (DEBUG_MODE) {
		std::cout << "[AIRCRAFT ATTACK PLAYER]int X = " << x << " Y = " << y << std::endl;
	}

	//Attack
	if (angle) {
		x--;
		const int temp_x = x + 3;
		for (x; x < temp_x; x++) {
			if (x < 0 || x >= width_height) {
				std::cout << "Captain! You shot out of bounds!" << std::endl;
				continue;
			}
			if (field_id_[x][y].first > 1) {
				if (ship_vector_[field_id_[x][y].first - 2].get_durability()[field_id_[x][y].second]) {
					get_damage(dmg, x, y);
				}
				else {
					std::cout << "Why did you shoot at an already sunk ship?" << std::endl;
				}
			}
			else {
				std::cout << "Miss!" << std::endl;
			}
			field_get_vision(x, y);
		}
	}
	else {
		y--;
		int temp_y = y + 3;
		for (y; y < temp_y; y++) {
			if (y < 0 or y >= width_height) {
				std::cout << "Captain! You shot out of bounds!" << std::endl;
				continue;
			}
			if (field_id_[x][y].first > 1) {
				if (ship_vector_[field_id_[x][y].first - 2].get_durability()[field_id_[x][y].second]) {
					get_damage(dmg, x, y);
				}
				else {
					std::cout << "Why did you shoot at an already sunk ship?" << std::endl;
				}
			}
			else {
				std::cout << "Miss!" << std::endl;
			}
			field_get_vision(x, y);
		}
	}
}

void Fleet::aircraft_attack_bot(const int dmg, int difficulty) {
	std::vector <std::pair <int, int>> bot_memory; //BOT Repository Of Detected Cells
	bool guras_bool = true; //Gura was still unable to plant a large tree
	int x = 0, y = 0, random_x = 0, random_y = 0, attempts = 0, counter = 0, max = 0;
	bool angle = rand() % 2;

	if (difficulty == 2) {
		difficulty = width_height * width_height;
	}

	remember_founded_ships(bot_memory);

	if constexpr (DEBUG_MODE) {
		std::cout << "[AIRCRAFT ATTACK BOT]bot_memory:" << std::endl;
		for (int i = 0; i < bot_memory.size(); i++) {
			std::cout << "[AIRCRAFT ATTACK BOT]X = " << bot_memory[i].first << "; Y = " << bot_memory[i].second << std::endl;
		}
	}

	while (guras_bool && attempts <= difficulty) {
		if (bot_memory.empty()) {
			//I)We scan for the number of unexplored cellsand the presence of ships on them, select the most suitable one(if the difficulty is hard)
			counter = 0;
			random_x = rand() % width_height;
			random_y = rand() % width_height;
			if (angle) {
				if (!x) x++;
				else if (x == width_height - 1) x--;
			}
			else {
				if (!y) y++;
				else if (y == width_height - 1) y--;
			}
			if constexpr (DEBUG_MODE) { std::cout << "[AIRCRAFT ATTACK BOT]rand_x = " << random_x << "; rand_y = " << random_y << std::endl; }
			switch (angle) {
			case 1: //horizontal
				if (field_id_[random_x - 1][random_y].first > 1 && !field_war_[random_x - 1][random_y]) counter++;
				if (field_id_[random_x][random_y].first > 1 && !field_war_[random_x][random_y]) counter++;
				if (field_id_[random_x + 1][random_y].first > 1 && !field_war_[random_x + 1][random_y]) counter++;
				break;
			case 0: //vertical
				if (field_id_[random_x][random_y - 1].first > 1 && !field_war_[random_x][random_y - 1]) counter++;
				if (field_id_[random_x][random_y].first > 1 && !field_war_[random_x][random_y]) counter++;
				if (field_id_[random_x][random_y + 1].first > 1 && !field_war_[random_x][random_y + 1]) counter++;
				break;
			}
			if (counter >= max) {
				max = counter;
				x = random_x;
				y = random_y;
			}
			if (max == 3) {
				guras_bool = false;
			}
			attempts++;
		}
		else { //II)Finishing off found ships + alignment
			x = bot_memory[rand() % bot_memory.size()].first;
			y = bot_memory[rand() % bot_memory.size()].second;
			bot_memory.clear();
			if (angle) {
				if (!x) x++;
				else if (x == width_height - 1) x--;
			}
			else {
				if (!y) y++;
				else if (y == width_height - 1) y--;
			}
			guras_bool = false;
		}
		if (field_id_[x][y].first > 1) { //III)Trying to hit as many cells as possible
			if (field_id_[x - 1][y].first > 1 && x - 1 > 0) {
				angle = true;
				x--;
				if (field_id_[x - 1][y].first > 1 && x - 1 > 0 && field_id_[x + 1][y].first <= 1) {
					x--;
				}
			}
			if (field_id_[x + 1][y].first > 1 && x + 1 < width_height - 1) {
				angle = true;
				x++;
				if (field_id_[x + 1][y].first > 1 && x + 1 < width_height - 1 && field_id_[x - 1][y].first <= 1) {
					x++;
				}
			}
			if (field_id_[x][y - 1].first > 1 && y - 1 > 0) {
				angle = false;
				y--;
				if (field_id_[x][y - 1].first > 1 && y - 1 > 0 && field_id_[x][y + 1].first <= 1) {
					y--;
				}
			}
			if (field_id_[x][y + 1].first > 1 && y + 1 < width_height - 1) {
				angle = false;
				y++;
				if (field_id_[x][y + 1].first > 1 && y + 1 < width_height - 1 && field_id_[x][y - 1].first <= 1) {
					y++;
				}
			}
		}
	}

	if constexpr (DEBUG_MODE) { std::cout << "[AIRCRAFT ATTACK BOT]Gura decided, that X = " << x << "; Y = " << y << std::endl; }

	if (angle) {
		//horizontal
		x--;
		const int temp_x = x + 3;
		for (x; x < temp_x; x++) {
			if (field_id_[x][y].first > 1) {
				get_damage(dmg, x, y);
				if (ship_vector_[field_id_[x][y].first - 2].get_durability()[field_id_[x][y].second]) {
					bot_memory.emplace_back(std::make_pair(x, y));
				}
			}
			else {
				std::cout << "Miss!" << std::endl;
			}
			field_get_vision(x, y);
		}
	}
	else {
		//vertical
		y--;
		int temp_y = y + 3;
		for (y; y < temp_y; y++) {
			if (field_id_[x][y].first > 1) {
				get_damage(dmg, x, y);
				if (ship_vector_[field_id_[x][y].first - 2].get_durability()[field_id_[x][y].second]) {
					bot_memory.emplace_back(std::make_pair(x, y));
				}
			}
			else {
				std::cout << "Miss!" << std::endl;
			}
			field_get_vision(x, y);
		}
	}
}

void Fleet::heavy_cruiser_attack_player(const int dmg) {
	int x = 0, y = 0;
	bool not_idiot = true, negative = false;
	char char_x = ' ';
	std::string str_y;
	std::cin >> char_x >> str_y;
	if constexpr (DEBUG_MODE) std::cout << "[HEAVY CRUISER ATTACK PLAYER]X = " << char_x << "; Y = " << str_y << std::endl;

	for (int i = 0; i < str_y.length(); i++) {
		if (str_y[i] >= '0' && str_y[i] <= '9') {
			not_idiot = false;
			y *= 10;
			y += str_y[i] - '0';
		}
		if (str_y[i] == '-') {
			negative = true;
		}
	}

	if (not_idiot) y = letter_to_int(std::toupper(str_y[0]));
	if (negative) y *= -1;

	//Check out of bounds
	if (y > width_height - 1 || y < 0)
	{
		std::cout << "Captain! You shot out of bounds!" << std::endl;
	}
	char_x = std::toupper(char_x);
	x = letter_to_int(char_x);
	if (x > width_height - 1 || x < 0) {
		std::cout << "Captain! You shot out of bounds!" << std::endl;
	}

	if constexpr (DEBUG_MODE) { std::cout << "[HEAVY CRUISER ATTACK PLAYER]int X = " << x << " Y = " << y << std::endl; }
	//Attack
	x--;
	y--;
	int temp_x = x, temp_y = y;
	for (x = temp_x; x < temp_x + 3; x++) {
		for (y = temp_y; y < temp_y + 3; y++) {
			if (x >= 0 && x < width_height && y >= 0 && y < width_height) {
				if (field_id_[x][y].first > 1) {
					if (ship_vector_[field_id_[x][y].first - 2].get_durability()[field_id_[x][y].second]) {
						get_damage(dmg, x, y);
					}
					else {
						std::cout << "Why did you shoot at an already sunk ship?" << std::endl;
					}
				}
				else {
					std::cout << "Miss!" << std::endl;
				}
				field_get_vision(x, y);
			}
			else {
				std::cout << "Captain! You shot out of bounds!" << std::endl;
			}
		}
	}
}

void Fleet::heavy_cruiser_attack_bot(const int dmg, int difficulty) {
	std::vector <std::pair <int, int>> bot_memory; //BOT Repository Of Detected Cells
	bool guras_bool = true, //Gura was still unable to plant a large tree
		nice_coords_from_memory = false;
	int x = 0, y = 0, random_x = 0, random_y = 0, attempts = 0, counter = 0, max = 0;

	if (difficulty == 2) {
		difficulty = width_height * width_height;
	}

	if constexpr (DEBUG_MODE) {
		std::cout << "[HEAVY CRUISER ATTACK BOT]bot_memory:" << std::endl;
		for (int i = 0; i < bot_memory.size(); i++) {
			std::cout << "[HEAVY CRUISER ATTACK BOT]X = " << bot_memory[i].first << "; Y = " << bot_memory[i].second << std::endl;
		}
	}

	remember_founded_ships(bot_memory);

	nice_coords_from_memory = false;
	for (int i = 0; i < bot_memory.size(); i++) {
		if (ship_vector_[field_id_[bot_memory[i].first][bot_memory[i].second].first - 2].get_durability()[field_id_[bot_memory[i].first][bot_memory[i].second].second] == 1) {
			x = bot_memory[i].first;
			y = bot_memory[i].second;
			nice_coords_from_memory = true;
			bot_memory.clear();
			if (!x) {
				x++;
			} else if (x == width_height - 1) {
				x--;
			}

			if (!y) {
				y++;
			} else if (y == width_height - 1) {
				y--;
			}
		}
	}

	while (guras_bool && attempts < difficulty + 1) {

		if (nice_coords_from_memory) break;
		counter = 0;
		random_x = rand() % (width_height - 2);
		random_x++;
		random_y = rand() % (width_height - 2);
		random_y++;
		if constexpr (DEBUG_MODE) { std::cout << "[HEAVY CRUISER ATTACK BOT]rand_x = " << random_x << "; rand_y = " << random_y << std::endl; }
		if (field_id_[random_x - 1][random_y - 1].first > 1) {
			if (ship_vector_[field_id_[random_x - 1][random_y - 1].first - 2].get_durability()[field_id_[random_x - 1][random_y - 1].second]) {
				counter += 3;
			}
		}
		if (!field_war_[random_x - 1][random_y - 1]) counter++;

		if (field_id_[random_x - 1][random_y].first > 1) {
			if (ship_vector_[field_id_[random_x - 1][random_y].first - 2].get_durability()[field_id_[random_x - 1][random_y].second]) {
				counter += 3;
			}
		}
		if (!field_war_[random_x - 1][random_y]) counter++;
		if (field_id_[random_x - 1][random_y + 1].first > 1) {
			if (ship_vector_[field_id_[random_x - 1][random_y + 1].first - 2].get_durability()[field_id_[random_x - 1][random_y + 1].second]) {
				counter += 3;
			}
		}
		if (!field_war_[random_x - 1][random_y + 1])  counter++;

		if (field_id_[random_x][random_y - 1].first > 1) {
			if (ship_vector_[field_id_[random_x][random_y - 1].first - 2].get_durability()[field_id_[random_x][random_y - 1].second]) {
				counter += 3;
			}
		}
		if (!field_war_[random_x][random_y - 1])  counter++;

		if (field_id_[random_x][random_y].first > 1) {
			if (ship_vector_[field_id_[random_x][random_y].first - 2].get_durability()[field_id_[random_x][random_y].second]) {
				counter += 3;
			}
		}
		if (!field_war_[random_x][random_y]) counter++;

		if (field_id_[random_x][random_y + 1].first > 1) {
			if (ship_vector_[field_id_[random_x][random_y + 1].first - 2].get_durability()[field_id_[random_x][random_y + 1].second]) {
				counter += 3;
			}
		}
		if (!field_war_[random_x][random_y + 1]) counter++;

		if (field_id_[random_x + 1][random_y - 1].first > 1) {
			if (ship_vector_[field_id_[random_x + 1][random_y - 1].first - 2].get_durability()[field_id_[random_x + 1][random_y - 1].second]) {
				counter += 3;
			}
		}
		if (!field_war_[random_x + 1][random_y - 1]) counter++;

		if (field_id_[random_x + 1][random_y].first > 1) {
			if (ship_vector_[field_id_[random_x + 1][random_y].first - 2].get_durability()[field_id_[random_x + 1][random_y].second]) {
				counter += 3;
			}
		}
		if (!field_war_[random_x + 1][random_y]) counter++;

		if (field_id_[random_x + 1][random_y + 1].first > 1) {
			if (ship_vector_[field_id_[random_x + 1][random_y + 1].first - 2].get_durability()[field_id_[random_x + 1][random_y + 1].second]) {
				counter += 3;
			}
		}
		if (!field_war_[random_x + 1][random_y + 1]) counter++;

		if (counter >= max) {
			max = counter;
			x = random_x;
			y = random_y;
		}
		if (max == 18) {
			guras_bool = false;
		}
		attempts++;
	}
	
	if constexpr (DEBUG_MODE) { std::cout << "[HEAVY CRUISER ATTACK BOT]Gura decided, that X = " << x << "; Y = " << y << std::endl; }
	x--;
	y--;
	int temp_x = x, temp_y = y;
	for (y = temp_y; y < temp_y + 3; y++) {
		for (x = temp_x; x < temp_x + 3; x++) {
			if (field_id_[x][y].first > 1) {
				get_damage(dmg, x, y);
				if (ship_vector_[field_id_[x][y].first - 2].get_durability_sum()) {
					bot_memory.emplace_back(std::make_pair(x, y));
				}
			}
			else {
				std::cout << "Miss!" << std::endl;
			}
			field_get_vision(x, y);
		}
	}

}

void Fleet::remember_founded_ships(std::vector <std::pair <int, int>>& memory) {
	for (int y = 0; y < width_height; y++) {
		for (int x = 0; x < width_height; x++) {
			if (field_id_[x][y].first > 1 && field_war_[x][y] == true) {
				if (ship_vector_[field_id_[x][y].first - 2].get_durability()[field_id_[x][y].second]) {
					memory.emplace_back(std::make_pair(x, y));
				}
			}
		}
	}
}

void Fleet::nuclear_bomb() {
	for (auto& i : ship_vector_) {
		for (int j = 0; j < i.get_type()->get_default_durability(); j++) {
			i--;
		}
	}
}

Fleet& Fleet::operator+=(const Ship& sheep) {
	ship_vector_.push_back(sheep);
	return *this;
}

Fleet& Fleet::operator-=(const Ship& sheep) {
	bool flag = false;
	for (auto& i : ship_vector_) {
		if (i == sheep) {
			ship_vector_.erase(std::remove(ship_vector_.begin(), ship_vector_.end(), sheep));
			flag = true;
			if constexpr (DEBUG_MODE) std::cout << "[REMOVE SHIP]One ship removed!" << std::endl;
		}
	}
	if (!flag) {
		if constexpr (DEBUG_MODE) std::cout << "[REMOVE SHIP]No ship to delete" << std::endl;
	}
	return *this;
}

bool Fleet::operator==(const Fleet& flood) {
	std::vector<unsigned int> count1, count2;
	for (int i = 0; i < ship_vector_.size(); i++) {
		if (ship_vector_[i].get_type()->get_size() > count1.size()) {
			count1.resize(ship_vector_[i].get_type()->get_size());
		}
		count1[ship_vector_[i].get_type()->get_size() - 1]++;
	}

	for (int i = 0; i < flood.ship_vector_.size(); i++) {
		if (flood.ship_vector_[i].get_type()->get_size() > count2.size()) {
			count2.resize(flood.ship_vector_[i].get_type()->get_size());
		}
		count2[flood.ship_vector_[i].get_type()->get_size() - 1]++;
	}

	if (count1 == count2) {
		return true;
	}
	else {
		return false;
	}
}

bool Fleet::operator!=(const Fleet& flood) {
	return !(*this == flood);
}

std::istream& operator>>(std::istream& in, Fleet& sheep) {
	sheep.read(in);
	return in;
}

std::ostream& operator<<(std::ostream& out, const Fleet& sheep) {
	sheep.print(out);
	return out;
}

void Fleet::initialize_field_final() {
	for (int y = 0; y < width_height; y++) {
		for (int x = 0; x < width_height; x++) {
			if (field_id_[x][y].first > 1) {
				if (ship_vector_[field_id_[x][y].first - 2].get_durability()[field_id_[x][y].second] < 10) {
					field_final_[x][y] = std::to_string(ship_vector_[field_id_[x][y].first - 2].get_durability()[field_id_[x][y].second]);
				}
				else {
					field_final_[x][y] = "?";
				}
			}
			else if (field_war_[x][y]) {
				field_final_[x][y] = "X";
			}
			else {
				field_final_[x][y] = " ";
			}
		}
	}
}

void Fleet::rebuild_fields_for_shipsweeper() {
	//for convenience I split this into two different "for", please do not try to rewrite this  -Alexey
	for (int y = 0; y < width_height; y++) {
		for (int x = 0; x < width_height; x++) {
			if (field_id_[x][y].first > 1) {
				field_id_[x][y].first = -1; //bomb
			}
		}
	}

	for (int y = 0; y < width_height; y++) {
		for (int x = 0; x < width_height; x++) {
			field_id_[x][y].second = 0;
			field_war_[x][y] = false;
			if (field_id_[x][y].first == 1) {
				field_id_[x][y].first = area_is_clear_shipsweeper(x, y); //number
			}
		}
	}
}

void Fleet::open_cells(const int x, const int y) {
	field_get_vision(x, y);
	if (field_id_[x][y].first > 0) return;
	if (y) {
		if (x) {
			if (field_id_[x - 1][y - 1].first >= 0 && !field_war_[x - 1][y - 1]) {
				open_cells(x - 1, y - 1);
			}
		}
		if (field_id_[x][y - 1].first >= 0 && !field_war_[x][y - 1]) {
			open_cells(x, y - 1);
		}
		if (x < width_height - 1) {
			if (field_id_[x + 1][y - 1].first >= 0 && !field_war_[x + 1][y - 1]) {
				open_cells(x + 1, y - 1);
			}
		}
	}
	if (x) {
		if (field_id_[x - 1][y].first >= 0 && !field_war_[x - 1][y]) {
			open_cells(x - 1, y);
		}
	}
	if (x < width_height - 1) {
		if (field_id_[x + 1][y].first >= 0 && !field_war_[x + 1][y]) {
			open_cells(x + 1, y);
		}
	}
	if (y < width_height - 1) {
		if (x) {
			if (field_id_[x - 1][y + 1].first >= 0 && !field_war_[x - 1][y + 1]) {
				open_cells(x - 1, y + 1);
			}
		}
		if (field_id_[x][y + 1].first >= 0 && !field_war_[x][y + 1]) {
			open_cells(x, y + 1);
		}
		if (x < width_height - 1) {
			if (field_id_[x + 1][y + 1].first >= 0 && !field_war_[x + 1][y + 1]) {
				open_cells(x + 1, y + 1);
			}
		}
	}
}

void Fleet::output_field_final(const Fleet& fleet2)const {
	//We transfer only the enemy fleet, we call through the current!
	std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::cout << "\t";
	if (width_height <= 10) std::cout << " ";
	std::cout << "Side: " << name_ << "[" << get_health_in_perc() << "%]";
	if (get_health_in_perc() < 100) std::cout << " ";
	if (get_health_in_perc() < 10) std::cout << " ";
	for (int i = 6; i <= width_height; i += 4) {
		std::cout << "\t";
	}
	if (width_height <= 10) std::cout << " ";
	std::cout << "Side: " << fleet2.name_ << "[" << fleet2.get_health_in_perc() << "%]" << std::endl;

	//Chars
	std::cout << "\t    ";
	for (int x = 0; x < width_height; x++) {
		std::cout << letters[x] << "|";
	}
	if (width_height == 1) {
		std::cout << "\t";
	}
	std::cout << "\t\t    ";
	for (int x = 0; x < width_height; x++) {
		std::cout << letters[x] << "|";
	}
	std::cout << std::endl;

	//game fields
	for (int y = 0; y < width_height; y++) {
		//our
		std::cout << "\t";
		//if y is one sign then " "
		if (y < 10) {
			std::cout << " ";
		}
		std::cout << y << "||";
		for (int x = 0; x < width_height; x++) {
			std::cout << field_final_[x][y] << "|";
		}
		//enemy
		std::cout << "\t\t";
		if (width_height == 1) {
			std::cout << "\t";
		}
		//if y is 1 chars then " "
		if (y < 10) {
			std::cout << " ";
		}
		std::cout << y << "||";
		for (int x = 0; x < width_height; x++) {
			if (fleet2.field_war_[x][y]) {
				if (fleet2.field_id_[x][y].first > 1) {
					std::cout << fleet2.field_final_[x][y] << "|";
				}
				else {
					std::cout << " |";
				}
			}
			else {
				std::cout << "#" << "|";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Fleet::output_field_final_shipsweeper(const Fleet& fleet2)const {
	//We transfer only the enemy fleet, we call through the current
	std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::cout << "\tSide: " << name_ << "\t";
	for (int i = 6; i <= width_height; i += 4) {
		std::cout << "\t";
	}
	std::cout << " Side: " << fleet2.name_ << std::endl;
	//Chars
	std::cout << "\t    ";
	for (int x = 0; x < width_height; x++) {
		std::cout << letters[x] << "|";
	}
	if (width_height == 1) {
		std::cout << "\t";
	}
	std::cout << "\t\t    ";
	for (int x = 0; x < width_height; x++) {
		std::cout << letters[x] << "|";
	}
	std::cout << std::endl;
	//game fields
	for (int y = 0; y < width_height; y++) {
		//our
		std::cout << "\t";
		//if y is 1 chars then " "
		if (y < 10) {
			std::cout << " ";
		}
		std::cout << y << "||";
		for (int x = 0; x < width_height; x++) {
			if (!field_id_[x][y].second) {
				if (field_war_[x][y]) {
					if (field_id_[x][y].first == -1) {
						std::cout << "B|";
					}
					else if (!field_id_[x][y].first) {
						std::cout << " |";
					}
					else {
						std::cout << field_id_[x][y].first << "|";
					}
				}
				else {
					std::cout << "#|";
				}
			}
			else {
				std::cout << "M|";
			}
		}
		//enemy
		std::cout << "\t\t";
		if (width_height == 1) {
			std::cout << "\t";
		}
		//if y is 1 chars then " "
		if (y < 10) {
			std::cout << " ";
		}
		std::cout << y << "||";
		for (int x = 0; x < width_height; x++) {
			if (!fleet2.field_id_[x][y].second) {
				if (fleet2.field_war_[x][y]) {
					if (fleet2.field_id_[x][y].first == -1) {
						std::cout << "B|";
					}
					else if (!fleet2.field_id_[x][y].first) {
						std::cout << " |";
					}
					else {
						std::cout << fleet2.field_id_[x][y].first << "|";
					}
				}
				else {
					std::cout << "#|";
				}
			}
			else {
				std::cout << "M|";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Fleet::output_field_id()const {
	//DEBUG FUNCTION
	std::cout << "id[" << name_ << "](NOT FOR USER): \n\n";
	for (int y = 0; y < width_height; y++) {
		std::cout << "         |";
		for (int x = 0; x < width_height; x++) {
			std::cout << field_id_[x][y].first << "|";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl << std::endl;
}

void Fleet::output_field_index()const {
	//DEBUG FUNCTION
	std::cout << "index[" << name_ << "](NOT FOR USER): \n\n";
	for (int y = 0; y < width_height; y++) {
		std::cout << "         |";
		for (int x = 0; x < width_height; x++) {
			std::cout << field_id_[x][y].second << "|";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl << std::endl;
}

void Fleet::output_field_war()const {
	//DEBUG FUNCTION
	std::cout << "War[" << name_ << "](NOT FOR USER): \n\n";
	for (int y = 0; y < width_height; y++) {
		std::cout << "         |";
		for (int x = 0; x < width_height; x++) {
			std::cout << field_war_[x][y] << "|";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Fleet::field_get_vision(const int x, const int y) {
	field_war_[x][y] = true;
}

std::vector<std::pair<int, int>> Fleet::find_ship_and_return_x_y_vector(const int& id)const {
	std::vector<std::pair<int, int>> coords;
	for (int y = 0; y < width_height; y++) {
		for (int x = 0; x < width_height; x++) {
			if (field_id_[x][y].first == id) {
				coords.emplace_back(std::make_pair(x, y));
			}
		}
	}
	if (coords.empty()) {
		coords.emplace_back(std::make_pair(0, 0));
	}
	return coords;
}

void Fleet::generate_field() {
	int counter = 0;
	bool breaks_in = true,
		left_is_clear = false,
		right_is_clear = false,
		up_is_clear = false,
		down_is_clear = false;
	bool stop = false;
	int x = 0, y = 0, rotation = 0;
	int length = 0, id = 0;

	for (int i = 0; i < ship_vector_.size(); i++) {
		counter = 0;
		stop = false;
		x = 0, y = 0, rotation = 0;
		length = ship_vector_[i].get_type()->get_size(), id = i + 2;
		breaks_in = true,
		left_is_clear = false,
		right_is_clear = false,
		up_is_clear = false,
		down_is_clear = false;
		while (!stop) {
			if (counter > width_height * width_height) {
				std::cout << "=============================================================================" << std::endl;
				std::cout << "Warning! Perhaps the ships cannot be placed on a field of this size.\nRestart the generator by pressing any key or change the fleets or field size." << std::endl;
				std::cout << "=============================================================================" << std::endl << std::endl;
				system("pause");
				std::cout << std::endl;
				clear_fields();
				i = -1;
				break;
			}
			x = rand() % width_height;
			y = rand() % width_height;
			rotation = rand() % 4;
			//TEST YOUR OUTPUT HERE //rotation: 0 - North, 1 - East, 2 - South - 3 - West
			//x = 5; y = 5; rotation = 0;
			if constexpr (DEBUG_MODE) {
				std::cout << "[Generator]Trying to: x = " << x;
				std::cout << "; y = " << y;
				std::cout << "; rotation = " << rotation;
				std::cout << "; id_: " << id;
				std::cout << "; Length: " << length;
				std::cout << "; Default durability: " << ship_vector_[i].get_durability()[0];
				std::cout << "; Status: ";
			}

			std::map<int, int> optimization_map = { {0, -1}, {1, 1}, {2, 1}, {3, -1} };

			const int ot = optimization_map[rotation]; //magic coefficient

			breaks_in = true;
			left_is_clear = false;
			right_is_clear = false;
			up_is_clear = false;
			down_is_clear = false;

			//checking for space on all sides
			if (x) {
				left_is_clear = true;
			}

			if (y) {
				up_is_clear = true;
			}

			if (x < width_height - 1) {
				right_is_clear = true;
			}

			if (y < width_height - 1) {
				down_is_clear = true;
			}
			/////////////////////////////////

			if (rotation == 0 || rotation == 2) {
				//vertical

				if (length > 1) {
					//check for the ability to place the ship
					if (ot > 0) {
						if (y + length >= width_height - 1) {
							breaks_in = false;
						}
					}
					else {
						if (y - length < 0) {
							breaks_in = false;
						}
					}
				}

				if (breaks_in) {
					for (int h = 0; h < length; h++) {
						//check for the ability to place the ship part 2
						if (field_id_[x][y + h * ot].first > 0) {
							breaks_in = false;
						}
					}
				}

				if (breaks_in) {
					ot > 0 ? breaks_in = up_is_clear : breaks_in = down_is_clear;
					if (breaks_in) {
						if (left_is_clear) {
							if (field_id_[x - 1][y - 1 * ot].first == 0) {
								field_id_[x - 1][y - 1 * ot].first = 1;
							}
						}

						if (field_id_[x][y - 1 * ot].first == 0) {
							field_id_[x][y - 1 * ot].first = 1;
						}

						if (right_is_clear) {
							if (field_id_[x + 1][y - 1 * ot].first == 0) {
								field_id_[x + 1][y - 1 * ot].first = 1;
							}
						}
					}

					for (int counter = 0; counter < length; counter++) {
						if (left_is_clear) {
							if (field_id_[x - 1][y + counter * ot].first == 0) {
								field_id_[x - 1][y + counter * ot].first = 1;
							}
						}

						field_id_[x][y + counter * ot].first = id;
						field_id_[x][y + counter * ot].second = counter;

						if (right_is_clear) {
							if (field_id_[x + 1][y + counter * ot].first == 0) {
								field_id_[x + 1][y + counter * ot].first = 1;
							}
						}
					}

					ot > 0 ? breaks_in = down_is_clear : breaks_in = up_is_clear;
					if (breaks_in) {
						if (left_is_clear) {
							if (field_id_[x - 1][y + length * ot].first == 0) {
								field_id_[x - 1][y + length * ot].first = 1;
							}
						}

						if (field_id_[x][y + length * ot].first == 0) {
							field_id_[x][y + length * ot].first = 1;
						}

						if (right_is_clear) {
							if (field_id_[x + 1][y + length * ot].first == 0) {
								field_id_[x + 1][y + length * ot].first = 1;
							}
						}
					}
					if constexpr (DEBUG_MODE) {
						std::cout << "Successfully!" << std::endl;
					}
					stop = true;
				}
			}
			else {
				//horizontal
				if (length > 1) {
					//check for the ability to place the ship
					if (ot > 0) {
						if (x + length >= width_height - 1) {
							breaks_in = false;
						}
					}
					else {
						if (x - length < 0) {
							breaks_in = false;
						}
					}
				}

				if (breaks_in) {
					for (int h = 0; h < length; h++) {
						//check for the ability to place the ship part 2
						if (field_id_[x + h * ot][y].first > 0) {
							breaks_in = false;
						}
					}
				}

				if (breaks_in) {
					ot > 0 ? breaks_in = left_is_clear : breaks_in = right_is_clear;
					if (breaks_in) {
						if (down_is_clear) {
							if (field_id_[x - 1 * ot][y + 1].first == 0) {
								field_id_[x - 1 * ot][y + 1].first = 1;
							}
						}

						if (field_id_[x - 1 * ot][y].first == 0) {
							field_id_[x - 1 * ot][y].first = 1;
						}

						if (up_is_clear) {
							if (field_id_[x - 1 * ot][y - 1].first == 0) {
								field_id_[x - 1 * ot][y - 1].first = 1;
							}
						}
					}
					for (int counter = 0; counter < length; counter++) {
						if (up_is_clear) {
							if (field_id_[x + counter * ot][y - 1].first == 0) {
								field_id_[x + counter * ot][y - 1].first = 1;
							}
						}

						field_id_[x + counter * ot][y].first = id;
						field_id_[x + counter * ot][y].second = counter;

						if (down_is_clear) {
							if (field_id_[x + counter * ot][y + 1].first == 0) {
								field_id_[x + counter * ot][y + 1].first = 1;
							}
						}
					}

					ot > 0 ? breaks_in = right_is_clear : breaks_in = left_is_clear;
					if (breaks_in) {
						if (down_is_clear) {
							if (field_id_[x + length * ot][y + 1].first == 0) {
								field_id_[x + length * ot][y + 1].first = 1;
							}
						}

						if (field_id_[x + length * ot][y].first == 0) {
							field_id_[x + length * ot][y].first = 1;
						}

						if (up_is_clear) {
							if (field_id_[x + length * ot][y - 1].first == 0) {
								field_id_[x + length * ot][y - 1].first = 1;
							}
						}
					}
					if constexpr (DEBUG_MODE) {
						std::cout << "Successfully!" << std::endl;
					}
					stop = true;
				}
			}
			if (DEBUG_MODE && !stop) {
				std::cout << "Failed!" << std::endl;
			}
			counter++;
		}
	}
	std::cout << name_ << " generation complete!" << std::endl << std::endl;
}

void Fleet::clear_fields() {
	for (int y = 0; y < width_height; y++) {
		for (int x = 0; x < width_height; x++) {
			field_war_[x][y] = 0;
			field_id_[x][y].first = 0;
			field_id_[x][y].second = 0;
			field_final_[x][y] = "#";
		}
	}
}

void Fleet::do_action(Fleet& whom, const unsigned& current_ship_id) {
	if constexpr (DEBUG_MODE) { std::cout << "[DO ACTION]order[round] = " << current_ship_id << std::endl; }
	const std::pair <int, int> coordinates = find_ship_and_return_x_y_vector(current_ship_id + 2)[0];
	std::cout << "Your fleet have:\t" << get_health_sum() << " health points" << std::endl; 
	std::cout << "Current position: \t" << int_to_letter(coordinates.first) << " " << coordinates.second << std::endl;
	std::cout << "Current type: \t\t" << ship_vector_[current_ship_id].get_type()->get_name() << ": " << ship_vector_[current_ship_id].get_type()->get_description() << std::endl << std::endl;
	std::cout << "What do you want? (Write command and coordinates)\n\n";
	std::string action;
	while (true) {
		if (ship_vector_.size() > current_ship_id) {
			if (ship_vector_[current_ship_id].get_durability_sum()) {
				ship_vector_[current_ship_id].get_type()->print_commands();
				if (ship_vector_[current_ship_id].get_type()->get_size() == 1) {
					std::cin >> action;
					ha_you_are_small_now(action);
					if (action == "shoot" || action == "s") {
						//Shot
						whom.damage_by_index_player(ship_vector_[current_ship_id]);
						break;
					}
					if (action == "move" || action == "m") {
						small_move_player(coordinates, current_ship_id);
						initialize_field_final();
						break;
					}
					std::cout << "Wrong command!" << std::endl;
					system("pause");
					continue;
				}
				if (ship_vector_[current_ship_id].get_type()->get_size() == 2) {
					std::cin >> action;
					ha_you_are_small_now(action);
					if (action == "shoot" || action == "s") {
						whom.damage_by_index_player(ship_vector_[current_ship_id]);
						break;
					}
					if (action == "repair" || action == "r") {
						ship_vector_[current_ship_id]++;
						std::cout << "Ship repaired!" << std::endl;
						initialize_field_final();
						break;
					}
					std::cout << "Wrong command!" << std::endl;
					system("pause");
					continue;
				}
				if (ship_vector_[current_ship_id].get_type()->get_size() == 3) {
					std::cin >> action;
					ha_you_are_small_now(action);
					if (action == "shoot" || action == "s") {
						//Shot
						whom.heavy_cruiser_attack_player(ship_vector_[current_ship_id].get_type()->get_damage_value());
						break;
					}
					std::cout << "Wrong command!" << std::endl;
					system("pause");
					continue;
				}
				if (ship_vector_[current_ship_id].get_type()->get_size() == 4) {
					whom.aircraft_attack_player(ship_vector_[current_ship_id].get_type()->get_damage_value());
					break;
				}
				if (ship_vector_[current_ship_id].get_type()->get_size() == 5) {
					system("pause");
					whom.nuclear_bomb();
					if (!DEBUG_MODE) system("cls");
					std::cout << "For just a moment, you see how a huge jet of magma erupts from the mouth of a huge monster, blowing away all the ships of the enemy." << std::endl;
					break;
				}
			}
			else {
				std::cout << "This ship is sunk, you miss this turn." << std::endl;
				system("pause");
				if constexpr (!DEBUG_MODE) system("cls");
				return;
			}
		} 
		else {
			std::cout << "This ship sank, you miss this turn." << std::endl;
			system("pause");
			if constexpr (!DEBUG_MODE) system("cls");
			return;
		}
	}
	system("pause");
	if constexpr (!DEBUG_MODE) { system("cls"); }
}

int Fleet::get_health_in_perc() const {
	int result = 0;
	int healths = 0;
	for (auto& i : ship_vector_) {
		healths += (i.get_type()->get_default_durability() * i.get_type()->get_size());
	}
	result = get_health_sum() * 100 / healths;
	return result;
}

void Fleet::do_action_344460(Fleet& whom, Ship damager) {
	std::cout << "What do you want? (Write command and coordinates)\n\n";
	std::string action;
	while (true) {
		std::cout << "-Scan (3x3, no dmg)\n-Shoot\n" << std::endl;
		std::cin >> action;
		ha_you_are_small_now(action);
		if (action == "scan" || action == "sc") {
			whom.heavy_cruiser_attack_player(0);
			whom.initialize_field_final();
			break;
		}
		if (action == "shoot" || action == "sh") {
			whom.damage_by_index_player(damager);
			initialize_field_final();
			break;
		}
		std::cout << "Wrong command!" << std::endl;
		system("pause");
		continue;
	}
	system("pause");
	if constexpr (!DEBUG_MODE) { system("cls"); }
}

int	Fleet::find_undead_small_ship_id() {
	for (int i = 0; i < ship_vector_.size(); i++) {
		if (ship_vector_[i].get_type()->get_size() == 1 && ship_vector_[i].get_durability_sum() > 0) return i;
	}
	return -1;
}

int	Fleet::find_undead_tsundere_ship_id() {
	for (int i = 0; i < ship_vector_.size(); i++) {
		if (ship_vector_[i].get_type()->get_size() == 2 && ship_vector_[i].get_durability_sum() > 0) return i;
	}
	return -1;
}

int	Fleet::find_undead_heavy_cruiser_ship_id() {
	for (int i = 0; i < ship_vector_.size(); i++) {
		if (ship_vector_[i].get_type()->get_size() == 3 && ship_vector_[i].get_durability_sum() > 0) return i;
	}
	return -1;
}

int	Fleet::find_undead_aircraft_carrier_ship_id() {
	for (int i = 0; i < ship_vector_.size(); i++) {
		if (ship_vector_[i].get_type()->get_size() == 4 && ship_vector_[i].get_durability_sum() > 0) return i;
	}
	return -1;
}

void Fleet::klee(const auto& coords) {
	if constexpr (DEBUG_MODE) {
		for (int i = 0; i < coords.size(); i++) {
			std::cout << "[Klee]" << i << ": X = " << coords[i].first << "; Y = " << coords[i].second << std::endl;
		}
		std::cout << std::endl;
	}
	for (auto& i : coords) {
		if (i.first) {
			if (i.second) {
				field_get_vision(i.first - 1, i.second - 1);
			}
			field_get_vision(i.first - 1, i.second);
			if (i.second < width_height - 1) {
				field_get_vision(i.first - 1, i.second + 1);
			}
		}
		if (i.second) {
			field_get_vision(i.first, i.second - 1);
		}
		if (i.second < width_height - 1) {
			field_get_vision(i.first, i.second + 1);
		}
		if (i.first < width_height - 1) {
			if (i.second) {
				field_get_vision(i.first + 1, i.second - 1);
			}
			field_get_vision(i.first + 1, i.second);
			if (i.second < width_height - 1) {
				field_get_vision(i.first + 1, i.second + 1);
			}
		}
	}
}

void Fleet::get_damage(const int dmg, const int x, const int y) {
	const int id = field_id_[x][y].first - 2;
	ship_vector_[id].damage_by_index(dmg, field_id_[x][y].second);
	std::cout << "Hit!" << std::endl;

	std::vector<std::pair<int, int>> coords;

	if (!ship_vector_[id].get_durability_sum()) {
		for (int x = 0; x < width_height; x++) {
			for (int y = 0; y < width_height; y++) {
				if (field_id_[x][y].first == id + 2) {
					coords.emplace_back(std::make_pair(x, y));
				}
			}
		}
		klee(coords);
	}
}

void Fleet::small_move_player(const std::pair<int, int>& start, const int& index) {
	int x = 0, y = 0;
	bool not_idiot = true, negative = false;
	char char_x = ' ';
	std::string str_y;
	while (true) {
		x = 0;
		y = 0;
		not_idiot = true;
		negative = false;
		char_x = ' ';
		str_y.clear();
		std::cin >> char_x >> str_y;

		if constexpr (DEBUG_MODE) std::cout << "[SMALL MOVE PLAYER]Char_X = " << char_x << "; Str_Y = " << str_y << std::endl;

		for (int i = 0; i < str_y.length(); i++) {
			if (str_y[i] >= '0' && str_y[i] <= '9') {
				not_idiot = false;
				y *= 10;
				y += str_y[i] - '0';
			}
			if (str_y[i] == '-') {
				negative = true;
			}
		}

		char_x = std::toupper(char_x);
		x = letter_to_int(char_x);

		if constexpr (DEBUG_MODE) std::cout << "[SMALL MOVE PLAYER]X = " << x << "; Y = " << y << std::endl;

		if (not_idiot) y = letter_to_int(std::toupper(str_y[0]));
		if (negative) y *= -1;

		//Check out of bounds
		if (y > width_height - 1 || y < 0) {
			std::cout << "Captain! Are you trying to steer the ship out of the battlefield?" << std::endl;
			system("pause");
			std::cout << "Write coordinates: ";
			continue;
		}

		if (x > width_height - 1 || x < 0) {
			std::cout << "Captain! Are you trying to steer the ship out of the battlefield?" << std::endl;
			system("pause");
			std::cout << "Write coordinates: ";
			continue;
		}


		if constexpr (DEBUG_MODE) {
			std::cout << "[SMALL MOVE PLAYER]Start X = " << start.first << "; Start Y = " << start.second << std::endl;
			std::cout << "[SMALL MOVE PLAYER]X = " << x << "; Y = " << y << std::endl;
		}


		if (difference_modulus(start.first, x) < 2 && difference_modulus(start.second, y) < 2) {
			field_id_[start.first][start.second].first = 0;
			if (area_is_clear(x, y)) {
				if (start.second) {
					if (start.first) {
						if (area_is_clear(start.first - 1, start.second - 1)) {
							field_id_[start.first - 1][start.second - 1].first = 0;
						}
					}
					if (area_is_clear(start.first, start.second - 1)) {
						field_id_[start.first][start.second - 1].first = 0;
					}
					if (start.first < width_height - 1) {
						if (area_is_clear(start.first + 1, start.second - 1)) {
							field_id_[start.first + 1][start.second - 1].first = 0;
						}
					}
				}
				if (start.first) {
					if (area_is_clear(start.first - 1, start.second)) {
						field_id_[start.first - 1][start.second].first = 0;
					}
				}
				if (start.first < width_height - 1) {
					if (area_is_clear(start.first + 1, start.second)) {
						field_id_[start.first + 1][start.second].first = 0;
					}
				}
				if (start.second < width_height - 1) {
					if (start.first) {
						if (area_is_clear(start.first - 1, start.second + 1)) {
							field_id_[start.first - 1][start.second + 1].first = 0;
						}
					}
					if (area_is_clear(start.first, start.second + 1)) {
						field_id_[start.first][start.second + 1].first = 0;
					}
					if (start.first < width_height - 1) {
						if (area_is_clear(start.first + 1, start.second + 1)) {
							field_id_[start.first + 1][start.second + 1].first = 0;
						}
					}
				}

				if (y) {
					if (x) {
						field_id_[x - 1][y - 1].first = 1;
					}
					field_id_[x][y - 1].first = 1;
					if (x < width_height - 1) {
						//here is magic(on the seed 1618667546, link: https://youtu.be/6ulhygoUrJg)
						field_id_[x + 1][y - 1].first = 1;
					}
				}
				if (x) {
					field_id_[x - 1][y].first = 1;
				}
				if (x < width_height - 1) {
					field_id_[x + 1][y].first = 1;
				}
				if (y < width_height - 1) {
					if (x) {
						field_id_[x - 1][y + 1].first = 1;
					}
					field_id_[x][y + 1].first = 1;
					if (x < width_height - 1) {
						field_id_[x + 1][y + 1].first = 1;
					}
				}
				field_id_[x][y].first = index + 2;
			}
			else {
				field_id_[start.first][start.second].first = index + 2;
				std::cout << "Captain! This square is already taken!" << std::endl;
				std::cout << "Write coordinates: ";
				continue;
			}
		}
		else {
			std::cout << "Captain! This is not a <<Meteor>> for you, a single-decker can only move one square." << std::endl;
			system("pause");
			std::cout << "Write coordinates: ";
			continue;
		}
		break;
	}
	std::cout << "Moved!\n";
}

void Fleet::small_move_bot(const std::pair<int, int>& coordinates, const std::pair<int, int>& start, const int& index) {
	if constexpr (DEBUG_MODE) {
		std::cout << "[SMALL MOVE BOT]Start on: X = " << start.first << "; Start Y = " << start.second << std::endl;
		std::cout << "[SMALL MOVE BOT]Move on: X = " << coordinates.first << "; Y = " << coordinates.second << std::endl;
	}

	field_id_[start.first][start.second].first = 0;
	if (start.second) {
		if (start.first) {
			if (area_is_clear(start.first - 1, start.second - 1)) {
				field_id_[start.first - 1][start.second - 1].first = 0;
			}
		}
		if (area_is_clear(start.first, start.second - 1)) {
			field_id_[start.first][start.second - 1].first = 0;
		}
		if (start.first < width_height) {
			if (area_is_clear(start.first + 1, start.second - 1)) {
				field_id_[start.first + 1][start.second - 1].first = 0;
			}
		}
	}
	if (start.first) {
		if (area_is_clear(start.first - 1, start.second)) {
			field_id_[start.first - 1][start.second].first = 0;
		}
	}
	if (start.first < width_height - 1)	{
		if (area_is_clear(start.first + 1, start.second)) {
			field_id_[start.first + 1][start.second].first = 0;
		}
	}
	if (start.second < width_height - 1) {
		if (start.first) {
			if (area_is_clear(start.first - 1, start.second + 1)) {
				field_id_[start.first - 1][start.second + 1].first = 0;
			}
		}
		if (area_is_clear(start.first, start.second + 1)) {
			field_id_[start.first][start.second + 1].first = 0;
		}
		if (start.first < width_height - 1) {
			if (area_is_clear(start.first + 1, start.second + 1)) {
				field_id_[start.first + 1][start.second + 1].first = 0;
			}
		}
	}
	if (coordinates.second) {
		if (coordinates.first) {
			field_id_[coordinates.first - 1][coordinates.second - 1].first = 1;
		}
		field_id_[coordinates.first][coordinates.second - 1].first = 1;
		if (coordinates.first < width_height) {
			field_id_[coordinates.first + 1][coordinates.second - 1].first = 1;
		}
	}
	if (coordinates.first) {
		field_id_[coordinates.first - 1][coordinates.second].first = 1;
	}
	if (coordinates.first < width_height - 1) {
		field_id_[coordinates.first + 1][coordinates.second].first = 1;
	}
	if (coordinates.second < width_height - 1) {
		if (coordinates.first) {
			field_id_[coordinates.first - 1][coordinates.second + 1].first = 1;
		}

		field_id_[coordinates.first][coordinates.second + 1].first = 1;

		if (coordinates.first < width_height - 1) {
			field_id_[coordinates.first + 1][coordinates.second + 1].first = 1;
		}
	}

	field_id_[coordinates.first][coordinates.second].first = index + 2;
}

bool Fleet::area_is_clear(const int x, const int y)const {
	if (y) {
		if (x) {
			if (field_id_[x - 1][y - 1].first > 1) return false;
		}
		if (field_id_[x][y - 1].first > 1) return false;
		if (x < width_height - 1) {
			if (field_id_[x + 1][y - 1].first > 1) return false;
		}
	}
	if (x) {
		if (field_id_[x - 1][y].first > 1) return false;
	}
	if (x < width_height - 1) {
		if (field_id_[x + 1][y].first > 1) return false;
	}
	if (y < width_height - 1) {
		if (x) {
			if (field_id_[x - 1][y + 1].first > 1) return false;
		}
		if (field_id_[x][y + 1].first > 1) return false;
		if (x < width_height - 1) {
			if (field_id_[x + 1][y + 1].first > 1) return false;
		}
	}
	return true;
}

int Fleet::area_is_clear_shipsweeper(const int x, const int y)const {
	int counter = 0;
	if (y) {
		if (x) {
			if (field_id_[x - 1][y - 1].first == -1) counter++;
		}
		if (field_id_[x][y - 1].first == -1) counter++;
		if (x < width_height - 1) {
			if (field_id_[x + 1][y - 1].first == -1) counter++;
		}
	}
	if (x) {
		if (field_id_[x - 1][y].first == -1) counter++;
	}
	if (x < width_height - 1) {
		if (field_id_[x + 1][y].first == -1) counter++;
	}
	if (y < width_height - 1) {
		if (x) {
			if (field_id_[x - 1][y + 1].first == -1) counter++;
		}
		if (field_id_[x][y + 1].first == -1) counter++;
		if (x < width_height - 1) {
			if (field_id_[x + 1][y + 1].first == -1) counter++;
		}
	}
	return counter;
}