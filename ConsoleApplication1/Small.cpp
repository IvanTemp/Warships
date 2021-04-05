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

bool area_is_clear(const bool side, const unsigned int x, const unsigned int y) {
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

void Small::move_small(const unsigned int index, const unsigned int start_x, const unsigned int start_y, const int side) const {
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
		move_small(index, start_x, start_y, side);
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
			move_small(index, start_x, start_y, side);
			return;
		}
	}

	if (game_info().get_debug_mode())
	{
		std::cout << "[Move small]Start X = " << start_x << "; Start Y = " << start_y << std::endl;
		std::cout << "[Move small]X = " << x << "; Y = " << y << std::endl;
		std::cout << "[Move small]shift: " << start_x - x << " " << start_y - y << " " << std::endl;
	}

	if ((start_x - x <= 1 || start_x - x >= UINT_MAX - 1) && (start_y - y <= 1 || start_y - y >= UINT_MAX - 1))
	{
		game_info().set_field_id(side, start_x, start_y, 0);
		if (area_is_clear(side, x, y))
		{
			if (start_y)
			{
				if (start_x)
				{
					if (area_is_clear(side, start_x - 1, start_y - 1))
						game_info().set_field_id(side, start_x - 1, start_y - 1, 0);
				}
				if (area_is_clear(side, start_x, start_y - 1))
					game_info().set_field_id(side, start_x, start_y - 1,0);
				if (start_x < width_height)
				{
					if (area_is_clear(side, start_x + 1, start_y - 1))
						game_info().set_field_id(side, start_x + 1, start_y - 1, 0);
				}
			}
			if (start_x)
			{
				if (area_is_clear(side, start_x - 1, start_y))
					game_info().set_field_id(side, start_x - 1, start_y, 0);
			}
			if (start_x < width_height - 1)
			{
				if (area_is_clear(side, start_x + 1, start_y))
					game_info().set_field_id(side, start_x + 1, start_y, 0);
			}
			if (start_y < width_height - 1)
			{
				if (start_x)
				{
					if (area_is_clear(side, start_x - 1, start_y + 1))
						game_info().set_field_id(side, start_x - 1, start_y + 1, 0);
				}
				if (area_is_clear(side, start_x, start_y + 1))
					game_info().set_field_id(side, start_x, start_y + 1, 0);
				if (start_x < width_height - 1)
				{
					if (area_is_clear(side, start_x + 1, start_y + 1))
						game_info().set_field_id(side, start_x + 1, start_y + 1, 0);
				}
			}

			if (y)
			{
				if (x)
				{
					game_info().set_field_id(side, x - 1, y - 1, 1);
				}
				game_info().set_field_id(side, x, y - 1, 1);
				if (x < width_height)
				{
					game_info().set_field_id(side, x + 1, y - 1, 1);
				}
			}
			if (x)
			{
				game_info().set_field_id(side, x - 1, y, 1);
			}
			if (x < width_height - 1)
			{
				game_info().set_field_id(side, x + 1, y, 1);
			}
			if (y < width_height - 1)
			{
				if (x)
				{
					game_info().set_field_id(side, x - 1, y + 1, 1);
				}
				game_info().set_field_id(side, x, y + 1, 1);
				if (x < width_height - 1)
				{
					game_info().set_field_id(side, x + 1, y + 1, 1);
				}
			}

			game_info().set_field_id(side, x, y, index + 2);
		}
		else
		{
			game_info().set_field_id(side, start_x, start_y, index + 2);
			std::cout << "Captain! This square is already taken!\n" << std::endl;
			system("pause");
			move_small(index, start_x, start_y, side);
			return;
		}
	}
	else
	{
		game_info().set_field_id(side, start_x, start_y, index + 2);
		std::cout << "Captain! This is not a <<Meteor>> for you, a single-decker can only move_small one square.\n" <<
			std::endl;
		system("pause");
		move_small(index, start_x, start_y, side);
		return;
	}
	std::cout << "Complete!\n\n";
}