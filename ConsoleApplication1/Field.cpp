#include "Field.h"

void Field::small_move(const unsigned int index, const int side)
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