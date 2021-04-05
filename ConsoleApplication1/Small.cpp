#include "Small.h"
#include "GameInformation.h"

void Small::print() const
{
    std::cout << name_;
}

int Small::get_size() const
{
    return size_;
}

int Small::get_damage_value() const
{
    return damage_;
}

std::string Small::get_name() const
{
    return name_;
}

int Small::get_default_durability() const
{
    return default_durability_;
}

bool Small::area_is_clear(const bool side, const unsigned int x, const unsigned int y) {
	extern GameInformation game_info();
	if (y)
	{
		if (x)
		{
			if (game_info().return_field_id()[side][x - 1][y - 1].first > 1) return false;
		}
		if (game_info().return_field_id()[side][x][y - 1].first > 1) return false;
		if (x < width_height - 1)
		{
			if (game_info().return_field_id()[side][x + 1][y - 1].first > 1) return false;
		}
	}
	if (x)
	{
		if (game_info().return_field_id()[side][x - 1][y].first > 1) return false;
	}
	if (x < width_height - 1)
	{
		if (game_info().return_field_id()[side][x + 1][y].first > 1) return false;
	}
	if (y < width_height - 1)
	{
		if (x)
		{
			if (game_info().return_field_id()[side][x - 1][y + 1].first > 1) return false;
		}
		if (game_info().return_field_id()[side][x][y + 1].first > 1) return false;
		if (x < width_height - 1)
		{
			if (game_info().return_field_id()[side][x + 1][y + 1].first > 1) return false;
		}
	}
	return true;
}

void Small::move_small(const unsigned int index, const int side) {
	extern GameInformation game_info();
	int x = 0, y = -1;
	std::cout << "Where are we going? (Write X and Y coordinates): ";
	std::string alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char strx;
	std::cin >> strx >> y;
	if (game_info().get_debug_mode()) std::cout << "[Move small]X = " << strx << "; Y = " << y << std::endl;

	if (y > width_height)
	{
		std::cout << "Captain! Are you trying to steer the ship out of the battlefield?\n" << std::endl;
		system("pause");
		move_small(index, side);
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
			move_small(index, side);
			return;
		}
	}

	std::pair<unsigned int, unsigned int> start = coordinates_;

	if (game_info().get_debug_mode())
	{
		std::cout << "[Move small]Start X = " << start.first << "; Start Y = " << start.second << std::endl;
		std::cout << "[Move small]X = " << x << "; Y = " << y << std::endl;
		std::cout << "[Move small]shift: " << start.first - x << " " << start.second - y << " " << std::endl;
	}

	if ((start.first - x <= 1 || start.first - x >= UINT_MAX - 1) && (start.second - y <= 1 || start.second - y >=
		UINT_MAX - 1))
	{
		game_info().return_field_id()[side][start.first][start.second].first = 0;
		if (area_is_clear(side, x, y))
		{
			if (start.second)
			{
				if (start.first)
				{
					if (area_is_clear(side, start.first - 1, start.second - 1))
						game_info().return_field_id()[side][start.first - 1][start.second - 1].first = 0;
				}
				if (area_is_clear(side, start.first, start.second - 1))
					game_info().return_field_id()[side][start.first][start.second - 1].
					first = 0;
				if (start.first < width_height)
				{
					if (area_is_clear(side, start.first + 1, start.second - 1))
						game_info().return_field_id()[side][start.first + 1][start.
						second - 1].first = 0;
				}
			}
			if (start.first)
			{
				if (area_is_clear(side, start.first - 1, start.second))
					game_info().return_field_id()[side][start.first - 1][start.second].
					first = 0;
			}
			if (start.first < width_height - 1)
			{
				if (area_is_clear(side, start.first + 1, start.second))
					game_info().return_field_id()[side][start.first + 1][start.second].
					first = 0;
			}
			if (start.second < width_height - 1)
			{
				if (start.first)
				{
					if (area_is_clear(side, start.first - 1, start.second + 1))
						game_info().return_field_id()[side][start.first - 1][start.second + 1].first = 0;
				}
				if (area_is_clear(side, start.first, start.second + 1))
					game_info().return_field_id()[side][start.first][start.second + 1].
					first = 0;
				if (start.first < width_height - 1)
				{
					if (area_is_clear(side, start.first + 1, start.second + 1))
						game_info().return_field_id()[side][start.first + 1][start.second + 1].first = 0;
				}
			}

			if (y)
			{
				if (x)
				{
					game_info().return_field_id()[side][x - 1][y - 1].first = 1;
				}
				game_info().return_field_id()[side][x][y - 1].first = 1;
				if (x < width_height)
				{
					game_info().return_field_id()[side][x + 1][y - 1].first = 1;
				}
			}
			if (x)
			{
				game_info().return_field_id()[side][x - 1][y].first = 1;
			}
			if (x < width_height - 1)
			{
				game_info().return_field_id()[side][x + 1][y].first = 1;
			}
			if (y < width_height - 1)
			{
				if (x)
				{
					game_info().return_field_id()[side][x - 1][y + 1].first = 1;
				}
				game_info().return_field_id()[side][x][y + 1].first = 1;
				if (x < width_height - 1)
				{
					game_info().return_field_id()[side][x + 1][y + 1].first = 1;
				}
			}

			game_info().return_field_id()[side][x][y].first = index + 2;
		}
		else
		{
			game_info().return_field_id()[side][start.first][start.second].first = index + 2;
			std::cout << "Captain! This square is already taken!\n" << std::endl;
			system("pause");
			move_small(index, side);
			return;
		}
	}
	else
	{
		game_info().return_field_id()[side][start.first][start.second].first = index + 2;
		std::cout << "Captain! This is not a <<Meteor>> for you, a single-decker can only move_small one square.\n" <<
			std::endl;
		system("pause");
		move_small(index, side);
		return;
	}
	std::cout << "Complete!\n\n";
}