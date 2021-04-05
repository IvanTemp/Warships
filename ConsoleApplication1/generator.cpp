#include <iostream>
#include <locale>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include "generator.h"
#include "fleet.h"
#include "ship.h"

void generate_ship(ship& sheep, const bool side)
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

				sheep.set_coordinates(std::make_pair(x, y));

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

				sheep.set_coordinates(std::make_pair(x, y));

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

void get_damage(const bool side, const unsigned int x, const unsigned int y, const int dmg, std::vector<ship>& fleet)
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
		fleet[index].detonate_the_ship(coords, side);
	}
}