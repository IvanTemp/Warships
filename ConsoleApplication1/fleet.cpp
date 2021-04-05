#include <string>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <iostream>
#include "fleet.h"
#include "generator.h"


std::vector <std::pair <unsigned int, unsigned int>> bots_memory; //BOT Repository Of Detected Cells

int Fleet::count_ = 0;

Fleet::Fleet(const std::string& nm) :name_(nm), side_(count_++) {}

Fleet::Fleet(const std::string& nm, const std::vector<ship>& v) : name_(nm), ship_vector_(v), side_(count_++) {}

void Fleet::print(std::ostream& out) const
{
	out << "=====Fleet " << name_ << "=====" << std::endl;
	if (ship_vector_.size())
	{
		for (const auto& x : ship_vector_)
		{
			x.print(out);
		}
	}
	else
	{
		out << "Fleet is empty" << std::endl;
	}
}

void Fleet::read(std::istream& in)
{
	getline(in, name_);
	std::string count = "";
	getline(in, count);
	for (int i = 0; i < stoi(count); i++)
	{
		ship newShip;
		newShip.read(in);
		add_ship_to_fleet(newShip);
	}
}

void Fleet::set_name(int index, const std::string nm)
{
	ship_vector_.at(index).set_name(nm);
}

std::string Fleet::get_name() const
{
	return name_;
}

std::vector<ship> Fleet::get_ship_vector() const
{
	return ship_vector_;
}

unsigned int Fleet::get_health() const
{
	unsigned int hp = 0;
	for (int i = 0; i < ship_vector_.size(); i++)
	{
		for (int j = 0; j < ship_vector_[i].get_durability().size(); j++)
		{
			hp += ship_vector_[i].get_durability()[j];
		}
	}
	return hp;
}

bool Fleet::add_ship_to_fleet(const ship& shp)
{
	for (int i = 0; i < ship_vector_.size(); i++)
	{
		if (ship_vector_[i] == shp)
		{
			std::cout << "Ship is already added" << std::endl;
			return false;
		}
	}
	ship_vector_.push_back(shp);
	return true;
}

bool Fleet::remove_ship_from_fleet(const ship& shp)
{
	//Проверка на пустой
	int len = ship_vector_.size();
	if (ship_vector_.begin() == ship_vector_.end())
		return false;
	//Добавим проверку удаления несуществующего
	bool flag = 0;
	for (int i = 0; i < ship_vector_.size(); i++)
	{
		if (ship_vector_[i] == shp)
		{
			//Само удаление
			ship_vector_.erase(std::remove(ship_vector_.begin(), ship_vector_.end(), shp));
			flag = 1;
			std::cout << "One ship removed!" << std::endl;
			return (len > ship_vector_.size());
		}
	}
	if (!flag)
	{
		std::cout << "No ship to delete" << std::endl;
		return false;
	}
}

bool Fleet::get_side()const {
	return side_;
}

ship Fleet::get_ship_by_index(const unsigned int id)const {
	return ship_vector_.at(id);
	//try
	//{
	//	return ship_vector_.at(index);
	//}
	//catch (std::out_of_range)
	//{
	//	std::cout << "Index out of range" << std::endl;
	//	throw;
	//}
}

void Fleet::damage_by_index_bot(const int dmg, const int difficulty) {
	srand(time(nullptr));
	int x = 0, y = 0;
	//Gura AI(c). All rights not reserved.
	bool GwSUtPaLT = true; //Gura was still unable to plant a large tree
	unsigned int attempts = difficulty;
	while (GwSUtPaLT) {
		x = rand() % width_height, y = rand() % width_height;
		if (DEBUG_MODE) std::cout << "[DEBUG INFO]Trying to: x = " << x << "; y = " << y << std::endl;

		if (bots_memory.size()) { //I)Finishing off found ships
			x = bots_memory[0].first, y = bots_memory[0].second;
			bots_memory.erase(bots_memory.begin());
			GwSUtPaLT = false;
		}
		else {
			if (return_field_war_value(side_, x, y) == 0) { // II)Protection against shooting at empty cells
				if (attempts) {
					if (return_field_id_value(side_, x, y) < 2) {
						if (difficulty < 2) {
							attempts--;
						}
					}
					else {
						GwSUtPaLT = false;
					}
				}
				else {
					GwSUtPaLT = false;
				}
			}
		}
	}
	if (DEBUG_MODE) std::cout << "[DEBUG INFO]Gura AI(c) decided that: x = " << x << "; y = " << y << std::endl;

	const char strx = int_to_letter(x);

	if (return_field_id_value(side_, x, y) > 1) {
		get_damage(side_, x, y, dmg, ship_vector_);
	}
	else {
		std::cout << "The enemy missed! X = " << strx << "; Y = " << y << std::endl;
	}
	field_get_vision(x, y, side_);
}

void Fleet::damage_by_index_bot_v2(unsigned int id, int dmg, const int difficulty) {
	srand(time(nullptr));
	std::string type = ship_vector_[id].get_type()->get_name();
}

void Fleet::damage_by_index_player(const ship sheep) {
	extern GameInformation game_info();
	std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
	int x = 0, y = -1;
	unsigned int dmg = sheep.get_type()->get_damage_value();
	std::string alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char charx;
	std::cin >> charx >> y;
	if (game_info().get_debug_mode()) std::cout << "[DEBUG INFO]X = " << charx << "; Y = " << y << std::endl;

	if (y > width_height) {
		std::cout << "Captain! You shot out of bounds!" << std::endl;
		return;
	}

	charx = std::toupper(charx);
	for (int i = 0; i < width_height; i++) {
		if (alf[i] == charx) {
			x = i;
			break;
		}
		if (i == width_height - 1) {
			std::cout << "Captain! You shot out of bounds!" << std::endl;
			return;
		}
	}

	if (game_info().get_debug_mode()) { std::cout << "[DEBUG INFO]int X = " << x << " Y = " << y << std::endl; }

	if (game_info().return_field_id()[side_][x][y].first > 1) 
	{
		if (ship_vector_[game_info().return_field_id()[side_][x][y].first - 2].get_durability()[game_info().return_field_id()[side_][x][y].second])
		{
			if (ship_vector_[game_info().return_field_id()[side_][x][y].first - 2].get_type()->get_name() == "Small" && sheep.get_type()->get_name() == "Tsundere")
			{
				dmg = Small_Durability;
			}
			else if (ship_vector_[game_info().return_field_id()[side_][x][y].first - 2].get_type()->get_name() == "Aircraft Carrier" && sheep.get_type()->get_name() == "Small")
			{
				dmg *= 2;
			}
			get_damage(side_, x, y, dmg, ship_vector_);
		}
		else {
			std::cout << "Why did you shoot at an already sunk ship?" << std::endl;
		}
	}
	else {
		std::cout << "Miss! X = " << alf[x] << "; Y = " << y << std::endl;
	}
	game_info().field_get_vision(x, y, side_);
}

void Fleet::aircraft_attack(const bool angle, const int dmg)
{
	extern GameInformation game_info();
	std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
	int x = 0, y = -1;
	std::string alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char char_x = ' ';
	std::cin >> char_x >> y;
	if (game_info().get_debug_mode()) std::cout << "[DEBUG INFO]X = " << char_x << "; Y = " << y << std::endl;

	if (y > width_height) {
		std::cout << "Captain! You shot out of bounds!" << std::endl;
		return;
	}

	char_x = std::toupper(char_x);
	for (int i = 0; i < width_height; i++) {
		if (alf[i] == char_x) {
			x = i;
			break;
		}
		if (i == width_height - 1) {
			std::cout << "Captain! You shot out of bounds!" << std::endl;
			return;
		}
	}

	if (game_info().get_debug_mode()) { std::cout << "[DEBUG INFO]int X = " << x << " Y = " << y << std::endl; }

	if (angle == 1) // horizontal
	{
		x--;;
		const int temp_x = x + 3;
		for (; x < temp_x; x++) {
			if (x < 0 || x >= width_height) {
				std::cout << "Captain! You shot out of bounds!" << std::endl;
				return;
			}
			if (game_info().return_field_id()[side_][x][y].first > 1) {
				if (ship_vector_[game_info().return_field_id()[side_][x][y].first - 2].get_durability()[game_info().return_field_id()[side_][x][y].second]) {
					get_damage(side_, x, y, dmg, ship_vector_);
				}
				else {
					std::cout << "Why did you shoot at an already sunk ship?" << std::endl;
				}
			}
			else {
				std::cout << "Miss! X = " << alf[x] << "; Y = " << y << std::endl;
			}
		}
	}
	else // vertical
	{
		y--;
		int temp_y = y + 3;
		for (y; y < temp_y; y++) {
			if (y < 0 or y >= width_height) {
				std::cout << "Captain! You shot out of bounds!" << std::endl;
				return;
			}
			if (game_info().return_field_id()[side_][x][y].first > 1) {
				if (ship_vector_[game_info().return_field_id()[side_][x][y].first - 2].get_durability()[game_info().return_field_id()[side_][x][y].second]) {
					get_damage(side_, x, y, dmg, ship_vector_);
				}
				else {
					std::cout << "Why did you shoot at an already sunk ship?" << std::endl;
				}
			}
			else {
				std::cout << "Miss! X = " << alf[x] << "; Y = " << y << std::endl;
			}
		}
	}
	game_info().field_get_vision(x, y, side_);
}

void Fleet::heavy_cruiser_attack(const int dmg)
{
	extern GameInformation game_info();
	int x = 0, y = -1;
	std::string alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char char_x;
	std::cin >> char_x >> y;
	if (game_info().get_debug_mode()) std::cout << "[DEBUG INFO]X = " << char_x << "; Y = " << y << std::endl;

	if (y > width_height) {
		std::cout << "Captain! You shot out of bounds!" << std::endl;
		return;
	}

	char_x = std::toupper(char_x);
	for (int i = 0; i < width_height; i++) {
		if (alf[i] == char_x) {
			x = i;
			break;
		}
		if (i == width_height - 1) {
			std::cout << "Captain! You shot out of bounds!" << std::endl;
			return;
		}
	}

	if (game_info().get_debug_mode()) { std::cout << "[DEBUG INFO]int X = " << x << " Y = " << y << std::endl; }
	x--;
	y--;
	int temp_x = x + 3, temp_y = y + 3;
	for (x; x < temp_x; x++)
	{
		for (y = temp_y - 3; y < temp_y; y++)
		{
			if (x < 0 || x >= width_height)
			{
				std::cout << "Captain! You shot out of bounds!" << std::endl;
			}
			else
			{
				if (y < 0 || y > width_height)
				{
					std::cout << "Captain! You shot out of bounds!" << std::endl;
				}
				else
				{
					if (game_info().return_field_id()[side_][x][y].first > 1) {
						if (ship_vector_[game_info().return_field_id()[side_][x][y].first - 2].get_durability()[game_info().return_field_id()[side_][x][y].second]) {
							get_damage(side_, x, y, dmg, ship_vector_);
						}
						else {
							std::cout << "Why did you shoot at an already sunk ship?" << std::endl;
						}
					}
					else {
						std::cout << "Miss! X = " << alf[x] << "; Y = " << y << std::endl;
					}
					game_info().field_get_vision(x, y, side_);
				}
			}
		}


	}
}

void Fleet::nuclear_bomb() { //test func
	for (int i = 0; i < ship_vector_.size(); i++) {
		ship_vector_[i].nuclear_bomb();
	}
}

Fleet& Fleet::operator+=(const ship& ship)
{
	add_ship_to_fleet(ship);
	return *this;
}

Fleet& Fleet::operator-=(const ship& ship)
{
	remove_ship_from_fleet(ship);
	return *this;
}

std::istream& operator>>(std::istream& in, Fleet& shp)
{
	shp.read(in);
	return in;
}

std::ostream& operator<<(std::ostream& out, const Fleet& shp)
{
	shp.print(out);
	return out;
}