#include "functions.h"

#define achievement_file "achievements.db"

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
	std::ofstream aqua(
		achievement_file, std::ios::in | std::ios::out | std::ios::app | std::ios::binary | std::ios::ate);
	aqua.close();
	std::ifstream achievement_in(achievement_file);
	std::string str;
	getline(achievement_in, str);
	for (int i = 0; i < str.length(); i++)
	{
		str[i] == '1' ? achievement_array[i].second = true : achievement_array[i].second = false;
	}
	achievement_in.close();
	std::ofstream achievement_out(achievement_file);
	for (int i = 0; i < achievement_array.size(); i++)
	{
		achievement_out << achievement_array[i].second;
	}
	achievement_out.close();
	return achievement_array;
}

void give_achievement(std::vector<std::pair<std::string, bool>>& achievement_array, const int& num)
{
	achievement_array[num].second = true;
	std::ofstream out(achievement_file);
	for (auto & value : achievement_array)
	{
		out << value.second;
	}
	out.close();
}

void ha_you_are_small_now(std::string& str)
{
	for (int i = 0; i < str.length(); i++)
	{
		str[i] = std::toupper(str[i]);
	}
}

char int_to_letter(const int i)
{
	std::string alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return alf[i];
}

std::vector<unsigned int> first_order(const unsigned int count)
{
	std::vector<unsigned int> order_list;
	bool buleidu = true; //if index hasn't already been
	for (unsigned int i = 0; i < count; i++)
	{
		buleidu = true;
		const unsigned int random_index = rand() % count;
		for (auto& j : order_list)
		{
			if (random_index == j)
			{
				buleidu = false;
			}
		}
		buleidu ? order_list.emplace_back(random_index) : i--;
	}
	return order_list;
}

bool area_is_clear(auto& field, const bool side, const unsigned int x, const unsigned int y)
{
	if (y)
	{
		if (x)
		{
			if (field[x - 1][y - 1].first > 1) return false;
		}
		if (field[x][y - 1].first > 1) return false;
		if (x < field.size() - 1)
		{
			if (field[x + 1][y - 1].first > 1) return false;
		}
	}
	if (x)
	{
		if (field[x - 1][y].first > 1) return false;
	}
	if (x < field.size() - 1)
	{
		if (field[x + 1][y].first > 1) return false;
	}
	if (y < field.size() - 1)
	{
		if (x)
		{
			if (field[x - 1][y + 1].first > 1) return false;
		}
		if (field[x][y + 1].first > 1) return false;
		if (x < field.size() - 1)
		{
			if (field[x + 1][y + 1].first > 1) return false;
		}
	}
	return true;
}