/*#include <iostream>
#include <locale>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include "Generator.h"
#include "Fleet.h"

std::string field_final[2][width_height][width_height] = {"#", "#", "#"}; //The field seen by the player and the AI
std::pair<unsigned int, unsigned int> field_id[2][width_height][width_height] = {(std::make_pair(0, 0))};
//The field with id_(.first) and indexes(.second)
bool field_war[2][width_height][width_height] = {(false), (false), (false)}; //The field with fog of war

void output_achievement_info(const std::vector<std::pair<std::string, bool>>& achievements)
{
	std::cout << "Achievements: " << std::endl;
	for (unsigned int i = 0; i < achievements.size(); i++)
	{
		std::cout << i + 1 << ")" << achievements[i].first << ": ";
		achievements[i].second ? std::cout << "Received\n" : std::cout << "Not received\n";
	}
	std::cout << std::endl;
}

std::vector<std::pair<std::string, bool>> read_achievements()
{
	std::vector<std::pair<std::string, bool>> achievement_array;
	//Place your achievements here
	achievement_array.emplace_back(std::make_pair("Win a PVE match on Normal difficulty", 0));
	achievement_array.emplace_back(std::make_pair("Win a PVE match on Hard difficulty", 0));
	achievement_array.emplace_back(std::make_pair("Try to win a PVE match on Impossible difficulty", 0));
	achievement_array.emplace_back(std::make_pair("Play PVP match", 0));
	/////////////////////////////
	std::ofstream nekostil(
		achievement_file, std::ios::in | std::ios::out | std::ios::app | std::ios::binary | std::ios::ate);
	nekostil.close();
	std::ifstream achivIn(achievement_file);
	std::string str;
	getline(achivIn, str);
	for (int i = 0; i < str.length(); i++)
	{
		str[i] == '1' ? achievement_array[i].second = true : achievement_array[i].second = false;
	}
	achivIn.close();
	std::ofstream achivOut(achievement_file);
	for (int i = 0; i < achievement_array.size(); i++)
	{
		achivOut << achievement_array[i].second;
	}
	achivOut.close();
	return achievement_array;
}

void give_achievement(std::vector<std::pair<std::string, bool>>& achievement_array, const int& num)
{
	achievement_array[num].second = true;
	std::ofstream out(achievement_file);
	for (unsigned int i = 0; i < achievement_array.size(); i++)
	{
		out << achievement_array[i].second;
	}
	out.close();
}

void do_action(Fleet& whose, Fleet& whom, const std::vector<unsigned int>& order, const int& round)
{
	if constexpr (DEBUG_MODE) { std::cout << "[DEBUG INFO]order[round] = " << order[round] << std::endl; }
	std::cout << "Current position: " << int_to_letter(return_x_y(order[round] + 2, whose.get_side()).first) << " " <<
		return_x_y(order[round] + 2, whose.get_side()).second << std::endl;
	std::cout << "Current BasicType: " << whose.get_ship_by_index(order[round]).get_type()->get_name() << std::endl;
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
				std::cout << "Specify the BasicType of attack (1x3 or 3x1): \n" << std::endl;
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
			std::cout << "This ship is sunk, you miss this turn." << std::endl; // -а в смысле пропуск хода? -Да
			return;
		}
	}
	system("pause");
	if constexpr (!DEBUG_MODE) { system("cls"); }
}

unsigned int return_field_id_value(const bool& side, const int& x, const int& y)
{
	return field_id[side][x][y].first;
}

unsigned int return_field_index_value(const bool& side, const int& x, const int& y)
{
	return field_id[side][x][y].second;
}

bool return_field_war_value(const bool& side, const int& x, const int& y)
{
	return field_war[side][x][y];
}

void ha_you_are_small_now(std::string& str)
{
	std::string small = "abcdefghijklmnopqrstuvwxyz";
	std::string big = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (int i = 0; i < str.length(); i++)
	{
		for (int j = 0; j < big.length(); j++)
		{
			if (str[i] == big[j])
				str[i] = small[j];
		}
	}
}

void initialize_field_final(const Fleet& fleet)
{
	for (unsigned int y = 0; y < width_height; y++)
	{
		for (unsigned int x = 0; x < width_height; x++)
		{
			if (field_id[fleet.get_side()][x][y].first > 1)
			{
				field_final[fleet.get_side()][x][y] = std::to_string(
					fleet.get_ship_by_index(field_id[fleet.get_side()][x][y].first - 2).get_durability()[field_id[fleet.
						get_side()][x][y].second]);
			}
			else if (field_war[fleet.get_side()][x][y])
			{
				field_final[fleet.get_side()][x][y] = "X";
			}
			else
			{
				field_final[fleet.get_side()][x][y] = " ";
			}
		}
	}
}

void output_field_final(const bool& side, const std::string& name1, const std::string& name2)
{
	std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::map<int, std::string> SideToName = {{0, name1}, {1, name2}};
	std::cout << "\tSide: " << SideToName[side] << "\t\tSide: " << SideToName[!side] << std::endl;
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
			std::cout << field_final[side][x][y] << "|";
		}
		std::cout << "\t\t" << y << "||";
		for (unsigned int x = 0; x < width_height; x++)
		{
			if (field_war[!side][x][y])
			{
				if (field_id[!side][x][y].first > 1) { std::cout << field_final[!side][x][y] << "|"; }
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

void output_field_id_indexes(const bool side)
{
	//DEBUG FUNC
	std::cout << "id_[" << side << "](NOT FOR USER): \n\n";
	for (unsigned int y = 0; y < width_height; y++)
	{
		std::cout << "         |";
		for (unsigned int x = 0; x < width_height; x++)
		{
			std::cout << field_id[side][x][y].first << "|";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl << std::endl;
	std::cout << "Indexes[" << side << "](NOT FOR USER): \n\n";
	for (unsigned int y = 0; y < width_height; y++)
	{
		std::cout << "         |";
		for (unsigned int x = 0; x < width_height; x++)
		{
			std::cout << field_id[side][x][y].second << "|";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void output_field_war(const bool side)
{
	//DEBUG FUNC
	std::cout << "War[" << side << "](NOT FOR USER): \n\n";
	for (unsigned int y = 0; y < width_height; y++)
	{
		std::cout << "         |";
		for (unsigned int x = 0; x < width_height; x++)
		{
			std::cout << field_war[side][x][y] << "|";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void field_get_vision(const unsigned int x, const unsigned int y, const bool side)
{
	field_war[side][x][y] = true;
}

void generate_ship(const Ship& sheep, const bool side)
{
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

		std::map<int, int> optimization_map = {{0, -1}, {1, 1}, {2, 1}, {3, -1}};

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
					if (field_id[side][x][y + h * ot].first > 0)
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
						if (field_id[side][x - 1][y - 1 * ot].first == 0)
						{
							field_id[side][x - 1][y - 1 * ot].first = 1;
						}
					}

					if (field_id[side][x][y - 1 * ot].first == 0)
					{
						field_id[side][x][y - 1 * ot].first = 1;
					}

					if (right_is_clear)
					{
						if (field_id[side][x + 1][y - 1 * ot].first == 0)
						{
							field_id[side][x + 1][y - 1 * ot].first = 1;
						}
					}
				}

				for (int counter = 0; counter < length; counter++)
				{
					if (left_is_clear)
					{
						if (field_id[side][x - 1][y + counter * ot].first == 0)
						{
							field_id[side][x - 1][y + counter * ot].first = 1;
						}
					}

					field_id[side][x][y + counter * ot].first = id;
					field_id[side][x][y + counter * ot].second = counter;

					if (right_is_clear)
					{
						if (field_id[side][x + 1][y + counter * ot].first == 0)
						{
							field_id[side][x + 1][y + counter * ot].first = 1;
						}
					}
				}

				ot > 0 ? breaks_in = down_is_clear : breaks_in = up_is_clear;
				if (breaks_in)
				{
					if (left_is_clear)
					{
						if (field_id[side][x - 1][y + length * ot].first == 0)
						{
							field_id[side][x - 1][y + length * ot].first = 1;
						}
					}

					if (field_id[side][x][y + length * ot].first == 0)
					{
						field_id[side][x][y + length * ot].first = 1;
					}

					if (right_is_clear)
					{
						if (field_id[side][x + 1][y + length * ot].first == 0)
						{
							field_id[side][x + 1][y + length * ot].first = 1;
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
					if (field_id[side][x + h * ot][y].first > 0)
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
						if (field_id[side][x - 1 * ot][y + 1].first == 0)
						{
							field_id[side][x - 1 * ot][y + 1].first = 1;
						}
					}

					if (field_id[side][x - 1 * ot][y].first == 0)
					{
						field_id[side][x - 1 * ot][y].first = 1;
					}

					if (up_is_clear)
					{
						if (field_id[side][x - 1 * ot][y - 1].first == 0)
						{
							field_id[side][x - 1 * ot][y - 1].first = 1;
						}
					}
				}
				for (int counter = 0; counter < length; counter++)
				{
					if (up_is_clear)
					{
						if (field_id[side][x + counter * ot][y - 1].first == 0)
						{
							field_id[side][x + counter * ot][y - 1].first = 1;
						}
					}

					field_id[side][x + counter * ot][y].first = id;
					field_id[side][x + counter * ot][y].second = counter;

					if (down_is_clear)
					{
						if (field_id[side][x + counter * ot][y + 1].first == 0)
						{
							field_id[side][x + counter * ot][y + 1].first = 1;
						}
					}
				}

				ot > 0 ? breaks_in = right_is_clear : breaks_in = left_is_clear;
				if (breaks_in)
				{
					if (down_is_clear)
					{
						if (field_id[side][x + length * ot][y + 1].first == 0)
						{
							field_id[side][x + length * ot][y + 1].first = 1;
						}
					}

					if (field_id[side][x + length * ot][y].first == 0)
					{
						field_id[side][x + length * ot][y].first = 1;
					}

					if (up_is_clear)
					{
						if (field_id[side][x + length * ot][y - 1].first == 0)
						{
							field_id[side][x + length * ot][y - 1].first = 1;
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

std::vector<unsigned int> first_order(Fleet& fleet1, Fleet& fleet2)
{
	std::vector<unsigned int> orderList;
	bool buleidu = true; //if index hasn't already been

	const unsigned int max = std::max(fleet1.get_ship_vector().size(), fleet2.get_ship_vector().size());

	for (unsigned int i = 0; i < max; i++)
	{
		buleidu = true;
		const unsigned int random_index = rand() % max;
		for (int j = 0; j < orderList.size(); j++)
		{
			if (random_index == orderList[j])
			{
				buleidu = false;
			}
		}
		if (buleidu)
		{
			orderList.emplace_back(random_index);
		}
		else
		{
			i--;
		}
	}

	if constexpr (DEBUG_MODE)
	{
		std::cout << "[DEBUG INFO]Indexes order list:";
		for (int i = 0; i < orderList.size(); i++)
		{
			std::cout << " " << orderList[i];
		}
		std::cout << std::endl << std::endl;
	}

	return orderList;
}

std::pair<unsigned int, unsigned int> return_x_y(const unsigned int id, const int side)
{
	unsigned int start_x = 0, start_y = 0;
	for (unsigned int y = 0; y < width_height; y++)
	{
		for (unsigned int x = 0; x < width_height; x++)
		{
			if (field_id[side][x][y].first == id)
			{
				start_x = x;
				start_y = y;
				return std::make_pair(start_x, start_y);
			}
		}
	}
	return std::make_pair(start_x, start_y);
}

char int_to_letter(const int i)
{
	std::string alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return alf[i];
}

bool area_is_clear(const bool side, const unsigned int x, const unsigned int y)
{
	if (y)
	{
		if (x)
		{
			if (field_id[side][x - 1][y - 1].first > 1) return false;
		}
		if (field_id[side][x][y - 1].first > 1) return false;
		if (x < width_height - 1)
		{
			if (field_id[side][x + 1][y - 1].first > 1) return false;
		}
	}
	if (x)
	{
		if (field_id[side][x - 1][y].first > 1) return false;
	}
	if (x < width_height - 1)
	{
		if (field_id[side][x + 1][y].first > 1) return false;
	}
	if (y < width_height - 1)
	{
		if (x)
		{
			if (field_id[side][x - 1][y + 1].first > 1) return false;
		}
		if (field_id[side][x][y + 1].first > 1) return false;
		if (x < width_height - 1)
		{
			if (field_id[side][x + 1][y + 1].first > 1) return false;
		}
	}
	return true;
}

void small_move(const unsigned int index, const int side)
{
	int x = 0, y = -1;
	std::cout << "Where are we going? (Write X and Y coordinates): ";
	std::string alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char strx;
	std::cin >> strx >> y;
	if constexpr (DEBUG_MODE) std::cout << "[Move small]X = " << strx << "; Y = " << y << std::endl;

	if (y > width_height)
	{
		std::cout << "Captain! Are you trying to steer the ship out of the battlefield?\n" << std::endl;
		system("pause");
		small_move(index, side);
		return;
	}
	strx = std::toupper(strx);
	for (unsigned int i = 0; i < width_height; i++)
	{
		if (alf[i] == strx)
		{
			x = i;
			break;
		}
		if (i == width_height - 1)
		{
			std::cout << "Captain! Are you trying to steer the ship out of the battlefield?\n" << std::endl;
			system("pause");
			small_move(index, side);
			return;
		}
	}

	std::pair<unsigned int, unsigned int> start = return_x_y(index + 2, side);

	if constexpr (DEBUG_MODE)
	{
		std::cout << "[Move small]Start X = " << start.first << "; Start Y = " << start.second << std::endl;
		std::cout << "[Move small]X = " << x << "; Y = " << y << std::endl;
		std::cout << "[Move small]shift: " << start.first - x << " " << start.second - y << " " << std::endl;
	}

	if ((start.first - x <= 1 || start.first - x >= UINT_MAX - 1) && (start.second - y <= 1 || start.second - y >=
		UINT_MAX - 1))
	{
		field_id[side][start.first][start.second].first = 0;
		if (area_is_clear(side, x, y))
		{
			if (start.second)
			{
				if (start.first)
				{
					if (area_is_clear(side, start.first - 1, start.second - 1))
						field_id[side][start.first - 1][start.
							second - 1].first = 0;
				}
				if (area_is_clear(side, start.first, start.second - 1))
					field_id[side][start.first][start.second - 1].
						first = 0;
				if (start.first < width_height)
				{
					if (area_is_clear(side, start.first + 1, start.second - 1))
						field_id[side][start.first + 1][start.
							second - 1].first = 0;
				}
			}
			if (start.first)
			{
				if (area_is_clear(side, start.first - 1, start.second))
					field_id[side][start.first - 1][start.second].
						first = 0;
			}
			if (start.first < width_height - 1)
			{
				if (area_is_clear(side, start.first + 1, start.second))
					field_id[side][start.first + 1][start.second].
						first = 0;
			}
			if (start.second < width_height - 1)
			{
				if (start.first)
				{
					if (area_is_clear(side, start.first - 1, start.second + 1))
						field_id[side][start.first - 1][start.
							second + 1].first = 0;
				}
				if (area_is_clear(side, start.first, start.second + 1))
					field_id[side][start.first][start.second + 1].
						first = 0;
				if (start.first < width_height - 1)
				{
					if (area_is_clear(side, start.first + 1, start.second + 1))
						field_id[side][start.first + 1][start.
							second + 1].first = 0;
				}
			}

			if (y)
			{
				if (x)
				{
					field_id[side][x - 1][y - 1].first = 1;
				}
				field_id[side][x][y - 1].first = 1;
				if (x < width_height)
				{
					field_id[side][x + 1][y - 1].first = 1;
				}
			}
			if (x)
			{
				field_id[side][x - 1][y].first = 1;
			}
			if (x < width_height - 1)
			{
				field_id[side][x + 1][y].first = 1;
			}
			if (y < width_height - 1)
			{
				if (x)
				{
					field_id[side][x - 1][y + 1].first = 1;
				}
				field_id[side][x][y + 1].first = 1;
				if (x < width_height - 1)
				{
					field_id[side][x + 1][y + 1].first = 1;
				}
			}

			field_id[side][x][y].first = index + 2;
		}
		else
		{
			field_id[side][start.first][start.second].first = index + 2;
			std::cout << "Captain! This square is already taken!\n" << std::endl;
			system("pause");
			small_move(index, side);
			return;
		}
	}
	else
	{
		field_id[side][start.first][start.second].first = index + 2;
		std::cout << "Captain! This is not a <<Meteor>> for you, a single-decker can only move one square.\n" <<
			std::endl;
		system("pause");
		small_move(index, side);
		return;
	}
	std::cout << "Complete!\n\n";
}

void get_damage(const bool side, const unsigned int x, const unsigned int y, const int dmg, std::vector<Ship>& fleet)
{
	std::string alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int index = field_id[side][x][y].first - 2;
	fleet[index].damage_by_index(dmg, field_id[side][x][y].second);
	std::cout << "Dodge this! You are hit!" << std::endl;
	std::cout << "You hit him in " << alf[x] << " " << y << std::endl;

	std::vector<std::pair<unsigned int, unsigned int>> coords;

	if constexpr (DEBUG_MODE)
	{
		std::cout << "[DEBUG INFO]Ship name: " << fleet[index].get_name();
		std::cout << "; new durability =";

		for (int i = 0; i < fleet[index].get_durability().size(); i++)
		{
			std::cout << " " << fleet[index].get_durability()[i];
		}

		std::cout << std::endl;
	}

	if (!fleet[index].get_durability_sum())
	{
		for (int x = 0; x < width_height; x++)
		{
			for (int y = 0; y < width_height; y++)
			{
				if (return_field_id_value(side, x, y) == index + 2)
				{
					coords.emplace_back(std::make_pair(x, y));
				}
			}
		}
		fleet[index].klee(coords, side);
	}
}
*/