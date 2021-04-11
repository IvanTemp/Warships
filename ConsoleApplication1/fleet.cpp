#include <string>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <iostream>
#include "Fleet.h"
#include "Generator.h"
#include "Field.h"

std::vector <std::pair <unsigned int, unsigned int>> bots_memory; //BOT Repository Of Detected Cells

int Fleet::count_ = 0;

Fleet::Fleet(const std::string& nm) :name_(nm), side_(count_++) {}

Fleet::Fleet(const std::string& nm, const std::vector<Ship>& v) : name_(nm), ship_vector_(v), side_(count_++) {}

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
		Ship newShip;
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

std::vector<Ship> Fleet::get_ship_vector() const
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

bool Fleet::add_ship_to_fleet(const Ship& shp)
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

bool Fleet::remove_ship_from_fleet(const Ship& shp)
{
	//�������� �� ������
	int len = ship_vector_.size();
	if (ship_vector_.begin() == ship_vector_.end())
		return false;
	//������� �������� �������� ���������������
	bool flag = 0;
	for (int i = 0; i < ship_vector_.size(); i++)
	{
		if (ship_vector_[i] == shp)
		{
			//���� ��������
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

Ship Fleet::get_ship_by_index(const unsigned int id)const {
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

void Fleet::damage_by_index_bot(const int dmg, const int difficulty, Field field) {
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
			if (field.return_field_war_value(side_, x, y) == 0) { // II)Protection against shooting at empty cells
				if (attempts) {
					if (field.return_field_id_value(side_, x, y) < 2) {
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

	const char strx = field.int_to_letter(x);

	if (field.return_field_id_value(side_, x, y) > 1) {
		field.get_damage(side_, x, y, dmg, ship_vector_);
	}
	else {
		std::cout << "The enemy missed! X = " << strx << "; Y = " << y << std::endl;
	}
	field.field_get_vision(x, y, side_);
}

void Fleet::damage_by_index_bot_v2(unsigned int id, int dmg, const int difficulty) {
	srand(time(nullptr));
	std::string type = ship_vector_[id].get_type()->get_name();
}

void Fleet::damage_by_index_player(Ship sheep, Field field) {
	std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
	int x = 0, y = -1;
	unsigned int dmg = sheep.get_type()->get_damage_value();
	std::string alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char charx;
	std::cin >> charx >> y;
	if (DEBUG_MODE) std::cout << "[DEBUG INFO]X = " << charx << "; Y = " << y << std::endl;

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

	if (DEBUG_MODE) { std::cout << "[DEBUG INFO]int X = " << x << " Y = " << y << std::endl; }

	if (field.return_field_id_value(side_, x, y) > 1)
	{
		if (ship_vector_[field.return_field_id_value(side_, x, y) - 2].get_durability()[field.return_field_index_value(side_, x, y)])
		{
			if (ship_vector_[field.return_field_id_value(side_, x, y) - 2].get_type()->get_name() == "Small" && sheep.get_type()->get_name() == "Tsundere")
			{
				dmg = Small_Durability;
			}
			else if (ship_vector_[field.return_field_id_value(side_, x, y) - 2].get_type()->get_name() == "Aircraft Carrier" && sheep.get_type()->get_name() == "Small")
			{
				dmg *= 2;
			}
			field.get_damage(side_, x, y, dmg, ship_vector_);
		}
		else {
			std::cout << "Why did you shoot at an already sunk ship?" << std::endl;
		}
	}
	else {
		std::cout << "Miss! X = " << alf[x] << "; Y = " << y << std::endl;
	}
	field.field_get_vision(x, y, side_);
}

void Fleet::aircraft_attack(const bool angle, const int dmg, Field field)
{
	std::cout << "Where are we going to shoot? (Write X and Y coordinates): ";
	int x = 0, y = -1;
	std::string alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char char_x = ' ';
	std::cin >> char_x >> y;
	if (DEBUG_MODE) std::cout << "[DEBUG INFO]X = " << char_x << "; Y = " << y << std::endl;

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

	if (DEBUG_MODE) { std::cout << "[DEBUG INFO]int X = " << x << " Y = " << y << std::endl; }

	if (angle == 1) // horizontal
	{
		x--;;
		const int temp_x = x + 3;
		for (; x < temp_x; x++) {
			if (x < 0 || x >= width_height) {
				std::cout << "Captain! You shot out of bounds!" << std::endl;
				return;
			}
			if (field.return_field_id_value(side_, x, y) > 1) {
				if (ship_vector_[field.return_field_id_value(side_, x, y) - 2].get_durability()[field.return_field_index_value(side_, x, y)]) {
					field.get_damage(side_, x, y, dmg, ship_vector_);
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
			if (field.return_field_id_value(side_, x, y) > 1) {
				if (ship_vector_[field.return_field_id_value(side_, x, y) - 2].get_durability()[field.return_field_index_value(side_, x, y)]) {
					field.get_damage(side_, x, y, dmg, ship_vector_);
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
	field.field_get_vision(x, y, side_);
}

void Fleet::heavy_cruiser_attack(const int dmg, Field field)
{
	int x = 0, y = -1;
	std::string alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char char_x;
	std::cin >> char_x >> y;
	if (DEBUG_MODE) std::cout << "[DEBUG INFO]X = " << char_x << "; Y = " << y << std::endl;

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

	if (DEBUG_MODE) { std::cout << "[DEBUG INFO]int X = " << x << " Y = " << y << std::endl; }
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
					if (field.return_field_id_value(side_, x, y) > 1) {
						if (ship_vector_[field.return_field_id_value(side_, x, y) - 2].get_durability()[field.return_field_index_value(side_, x, y)]) {
							field.get_damage(side_, x, y, dmg, ship_vector_);
						}
						else {
							std::cout << "Why did you shoot at an already sunk ship?" << std::endl;
						}
					}
					else {
						std::cout << "Miss! X = " << alf[x] << "; Y = " << y << std::endl;
					}
					field.field_get_vision(x, y, side_);
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

Fleet& Fleet::operator+=(const Ship& ship)
{
	add_ship_to_fleet(ship);
	return *this;
}

Fleet& Fleet::operator-=(const Ship& ship)
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

std::string Fleet::return_field_final(const unsigned& x, const unsigned& y) const
{
	return field_final_[x][y];
}

unsigned int Fleet::return_field_id(const unsigned& x, const unsigned& y)const
{
	return field_id_[x][y].first;
}

unsigned int Fleet::return_field_index(const unsigned& x, const unsigned& y)const
{
	return field_id_[x][y].second;
}

bool Fleet::return_field_war(const unsigned& x, const unsigned& y)const
{
	return field_war_[x][y];
}

void Fleet::initialize_field_final(const Fleet& fleet)
{
	for (unsigned int y = 0; y < width_height; y++)
	{
		for (unsigned int x = 0; x < width_height; x++)
		{
			if (field_id_[x][y].first > 1)
			{
				field_final_[x][y] = std::to_string(
					fleet.get_ship_by_index(field_id_[x][y].first - 2).get_durability()[field_id_[x][y].second]);
			}
			else if (field_war_[x][y])
			{
				field_final_[x][y] = "X";
			}
			else
			{
				field_final_[x][y] = " ";
			}
		}
	}
}

void Fleet::output_field_final(const Fleet& fleet2)const //������� ������ ��������� ����, ��������� ����� �������
{
	std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::map<int, std::string> SideToName = { {0, name_}, {1, fleet2.name_} };
	std::cout << "\tSide: " << name_ << "\t\tSide: " << fleet2.name_ << std::endl;
	std::cout << "\t ||";
	for (unsigned int x = 0; x < width_height; x++)
	{
		std::cout << letters[x] << "|";
	}
	std::cout << "\t\t   ";
	for (unsigned int x = 0; x < width_height; x++)
	{
		std::cout << letters[x] << "|";
	}
	std::cout << std::endl;
	for (unsigned int y = 0; y < width_height; y++)
	{
		std::cout << "\t" << y << "||";
		for (unsigned int x = 0; x < width_height; x++)
		{
			std::cout << field_final_[x][y] << "|";
		}
		std::cout << "\t\t" << y << "||";
		for (unsigned int x = 0; x < width_height; x++)
		{
			if (fleet2.field_war_[x][y])
			{
				if (fleet2.field_id_[x][y].first > 1) { std::cout << field_final_[x][y] << "|"; }
				else { std::cout << " |"; }
			}
			else
			{
				std::cout << "#" << "|";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Fleet::output_field_id_indexes()const
{
	//DEBUG FUNC
	std::cout << "id[" << side_ << "](NOT FOR USER): \n\n";
	for (unsigned int y = 0; y < width_height; y++)
	{
		std::cout << "         |";
		for (unsigned int x = 0; x < width_height; x++)
		{
			std::cout << field_id_[x][y].first << "|";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl << std::endl;
}

void Fleet::output_field_war()const
{
	//DEBUG FUNC
	std::cout << "War[" << side_ << "](NOT FOR USER): \n\n";
	for (unsigned int y = 0; y < width_height; y++)
	{
		std::cout << "         |";
		for (unsigned int x = 0; x < width_height; x++)
		{
			std::cout << field_war_[x][y] << "|";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Fleet::field_get_vision(const unsigned int x, const unsigned int y)
{
	field_war_[x][y] = true;
}

std::pair<unsigned int, unsigned int> Fleet::return_x_y(const unsigned int &id)const
{
	unsigned int start_x = 0, start_y = 0;
	for (unsigned int y = 0; y < width_height; y++)
	{
		for (unsigned int x = 0; x < width_height; x++)
		{
			if (field_id_[x][y].first == id)
			{
				start_x = x;
				start_y = y;
				return std::make_pair(start_x, start_y);
			}
		}
	}
	return std::make_pair(start_x, start_y);
}

void Fleet::generate_fleet()
{
	for (auto& sheep : get_ship_vector()) {
		bool stop = false;
		int x = 0, y = 0, rotation = 0;
		const int length = sheep.get_type()->get_size(), id = sheep.get_id();
		bool breaks_in = true,
			left_is_clear = false,
			right_is_clear = false,
			up_is_clear = false,
			down_is_clear = false;
		while (!stop)
		{
			x = rand() % width_height;
			y = rand() % width_height;
			rotation = rand() % 4;
			//TEST YOUR OUTPUT HERE //rotation: 0 - North, 1 - East, 2 - South - 3 - West
			//x = 5; y = 5; rotation = 0;
			if constexpr (DEBUG_MODE)
			{
				std::cout << "[Generator]Trying to: x = " << x;
				std::cout << "; y = " << y;
				std::cout << "; rotation = " << rotation;
				std::cout << "; id_: " << id;
				std::cout << "; Length: " << length;
				std::cout << "; Default durability: " << sheep.get_durability()[0];
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
			if (x)
			{
				left_is_clear = true;
			}

			if (y)
			{
				up_is_clear = true;
			}

			if (x < width_height - 1)
			{
				right_is_clear = true;
			}

			if (y < width_height - 1)
			{
				down_is_clear = true;
			}
			/////////////////////////////////

			if (rotation == 0 || rotation == 2)
			{
				//vertical

				if (length > 1)
				{
					//check for the ability to place the ship
					if (ot > 0)
					{
						if (y + length >= width_height - 1)
						{
							breaks_in = false;
						}
					}
					else
					{
						if (y - length < 0)
						{
							breaks_in = false;
						}
					}
				}

				if (breaks_in)
				{
					for (unsigned int h = 0; h < length; h++)
					{
						//check for the ability to place the ship part 2
						if (field_id_[x][y + h * ot].first > 0)
						{
							breaks_in = false;
						}
					}
				}

				if (breaks_in)
				{
					ot > 0 ? breaks_in = up_is_clear : breaks_in = down_is_clear;
					if (breaks_in)
					{
						if (left_is_clear)
						{
							if (field_id_[x - 1][y - 1 * ot].first == 0)
							{
								field_id_[x - 1][y - 1 * ot].first = 1;
							}
						}

						if (field_id_[x][y - 1 * ot].first == 0)
						{
							field_id_[x][y - 1 * ot].first = 1;
						}

						if (right_is_clear)
						{
							if (field_id_[x + 1][y - 1 * ot].first == 0)
							{
								field_id_[x + 1][y - 1 * ot].first = 1;
							}
						}
					}

					for (int counter = 0; counter < length; counter++)
					{
						if (left_is_clear)
						{
							if (field_id_[x - 1][y + counter * ot].first == 0)
							{
								field_id_[x - 1][y + counter * ot].first = 1;
							}
						}

						field_id_[x][y + counter * ot].first = id;
						field_id_[x][y + counter * ot].second = counter;

						if (right_is_clear)
						{
							if (field_id_[x + 1][y + counter * ot].first == 0)
							{
								field_id_[x + 1][y + counter * ot].first = 1;
							}
						}
					}

					ot > 0 ? breaks_in = down_is_clear : breaks_in = up_is_clear;
					if (breaks_in)
					{
						if (left_is_clear)
						{
							if (field_id_[x - 1][y + length * ot].first == 0)
							{
								field_id_[x - 1][y + length * ot].first = 1;
							}
						}

						if (field_id_[x][y + length * ot].first == 0)
						{
							field_id_[x][y + length * ot].first = 1;
						}

						if (right_is_clear)
						{
							if (field_id_[x + 1][y + length * ot].first == 0)
							{
								field_id_[x + 1][y + length * ot].first = 1;
							}
						}
					}
					if constexpr (DEBUG_MODE)
					{
						std::cout << "Successfully!" << std::endl;
					}
					stop = true;
				}
			}
			else
			{
				//horizontal
				if (length > 1)
				{
					//check for the ability to place the ship
					if (ot > 0)
					{
						if (x + length >= width_height - 1)
						{
							breaks_in = false;
						}
					}
					else
					{
						if (x - length < 0)
						{
							breaks_in = false;
						}
					}
				}

				if (breaks_in)
				{
					for (unsigned int h = 0; h < length; h++)
					{
						//check for the ability to place the ship part 2
						if (field_id_[x + h * ot][y].first > 0)
						{
							breaks_in = false;
						}
					}
				}

				if (breaks_in)
				{
					ot > 0 ? breaks_in = left_is_clear : breaks_in = right_is_clear;
					if (breaks_in)
					{
						if (down_is_clear)
						{
							if (field_id_[x - 1 * ot][y + 1].first == 0)
							{
								field_id_[x - 1 * ot][y + 1].first = 1;
							}
						}

						if (field_id_[x - 1 * ot][y].first == 0)
						{
							field_id_[x - 1 * ot][y].first = 1;
						}

						if (up_is_clear)
						{
							if (field_id_[x - 1 * ot][y - 1].first == 0)
							{
								field_id_[x - 1 * ot][y - 1].first = 1;
							}
						}
					}
					for (int counter = 0; counter < length; counter++)
					{
						if (up_is_clear)
						{
							if (field_id_[x + counter * ot][y - 1].first == 0)
							{
								field_id_[x + counter * ot][y - 1].first = 1;
							}
						}

						field_id_[x + counter * ot][y].first = id;
						field_id_[x + counter * ot][y].second = counter;

						if (down_is_clear)
						{
							if (field_id_[x + counter * ot][y + 1].first == 0)
							{
								field_id_[x + counter * ot][y + 1].first = 1;
							}
						}
					}

					ot > 0 ? breaks_in = right_is_clear : breaks_in = left_is_clear;
					if (breaks_in)
					{
						if (down_is_clear)
						{
							if (field_id_[x + length * ot][y + 1].first == 0)
							{
								field_id_[x + length * ot][y + 1].first = 1;
							}
						}

						if (field_id_[x + length * ot][y].first == 0)
						{
							field_id_[x + length * ot][y].first = 1;
						}

						if (up_is_clear)
						{
							if (field_id_[x + length * ot][y - 1].first == 0)
							{
								field_id_[x + length * ot][y - 1].first = 1;
							}
						}
					}
					if constexpr (DEBUG_MODE)
					{
						std::cout << "Successfully!" << std::endl;
					}
					stop = true;
				}
			}
			if (DEBUG_MODE && !stop)
			{
				std::cout << "Failed!" << std::endl;
			}
		}
	}
}

void Fleet::do_action(Fleet& whose, Fleet& whom, const std::vector<unsigned int>& order, const int& round)
{
	if constexpr (DEBUG_MODE) { std::cout << "[DEBUG INFO]order[round] = " << order[round] << std::endl; }
	std::cout << "Current position: " << int_to_letter(return_x_y(order[round] + 2).first) << " " <<
		return_x_y(order[round] + 2).second << std::endl;
	std::cout << "Current type: " << whose.get_ship_by_index(order[round]).get_type()->get_name() << std::endl;
	std::cout << "What do you want?\n\n";
	std::string action;
	while (true)
	{
		if (whose.get_ship_by_index(order[round]).get_durability_sum())
		{
			if (whose.get_ship_by_index(order[round]).get_type()->get_name() == "Small")
			{
				//single-deck abilities
				std::cout << "-Shoot\n-Move\n" << std::endl;
				std::cin >> action;
				ha_you_are_small_now(action);
				if (action == "shoot")
				{
					//Shot
					whom.damage_by_index_player(whose.get_ship_by_index(order[round]));
					break;
				}
				if (action == "move")
				{
					small_move(order[round], whose.get_side());
					initialize_field_final(whose);
					break;
				}
				std::cout << "Wrong command!" << std::endl;
				system("pause");
				continue;
			}
			if (whose.get_ship_by_index(order[round]).get_type()->get_name() == "Tsundere")
			{
				std::cout << "-Shoot\n-Repair\n" << std::endl;
				std::cin >> action;
				ha_you_are_small_now(action);
				if (action == "shoot")
				{
					whom.damage_by_index_player(whose.get_ship_by_index(order[round]));
					break;
				}
				if (action == "repair")
				{
					whose.get_ship_by_index(order[round])++;
					std::cout << "Ship repaired!" << std::endl;
					initialize_field_final(whose);
					break;
				}
				std::cout << "Wrong command!" << std::endl;
				system("pause");
				continue;
			}
			if (whose.get_ship_by_index(order[round]).get_type()->get_name() == "Heavy Cruiser")
			{
				//Shot
				std::cout << "Point the center where to shoot (Write X and Y coordinates): ";
				whom.heavy_cruiser_attack(whose.get_ship_by_index(order[round]).get_type()->get_damage_value());
				break;
			}
			if (whose.get_ship_by_index(order[round]).get_type()->get_name() == "Aircraft Carrier")
			{
				ha_you_are_small_now(action);
				std::cout << "Specify the type of attack (1x3 or 3x1): \n" << std::endl;
				std::cin >> action;
				ha_you_are_small_now(action);
				if (action == "1x3" || action == "1")
				{
					whom.aircraft_attack(true, whose.get_ship_by_index(order[round]).get_type()->get_damage_value());
					break;
				}
				if (action == "3x1" || action == "3")
				{
					whom.aircraft_attack(false, whose.get_ship_by_index(order[round]).get_type()->get_damage_value());
					break;
				}
				std::cout << "Wrong command!" << std::endl;
				system("pause");
			}
		}
		else
		{
			std::cout << "This ship is sunk, you miss this turn." << std::endl;
			return;
		}
	}
	system("pause");
	if constexpr (!DEBUG_MODE) { system("cls"); }
}

void Fleet::get_damage(const unsigned int index, const int dmg, const unsigned int x, const unsigned int y)
{
	std::string alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	ship_vector_[index].damage_by_index(dmg, index);
	std::cout << "Dodge this! You are hit!" << std::endl;
	std::cout << "You hit him in " << alf[x] << " " << y << std::endl;

	std::vector<std::pair<unsigned int, unsigned int>> coords;

	if (!ship_vector_[index].get_durability_sum())
	{
		for (int x = 0; x < width_height; x++)
		{
			for (int y = 0; y < width_height; y++)
			{
				if (field_id_[x][y].first == index + 2)
				{
					coords.emplace_back(std::make_pair(x, y));
				}
			}
		}
		ship_vector_[index].klee(coords);
	}
}