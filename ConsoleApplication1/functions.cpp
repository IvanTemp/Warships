#include "functions.h"

#define achievement_file "achievements.db"

void output_achievement_info(const std::vector<std::pair<std::string, bool>>& achievements)
{
	int counter = 0;
	for (int i = 0; i < achievements.size(); i++) if (achievements[i].second) counter++;
	if (achievements[4].second)
	{
		std::cout << "Achievements[" << counter << "/" << achievements.size() << "]: " << std::endl;
		for (int i = 0; i < 5; i++) 
		{ 
			std::cout << i + 1 << ") ";
			achievements[i].second ? std::cout << "+ " : std::cout << "- ";
			std::cout << achievements[i].first << "\n";
		}
	}
	else
	{
		std::cout << "Achievements[" << counter << "/" << achievements.size() - 1 << "]: " << std::endl;
		for (int i = 0; i < 4; i++)
		{
			std::cout << i + 1 << ") ";
			achievements[i].second ? std::cout << "+ " : std::cout << "- ";
			std::cout << achievements[i].first << "\n";
		}
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
	achievement_array.emplace_back(std::make_pair("Win a PVP match", 0));
	achievement_array.emplace_back(std::make_pair("Win a mission with code 344460", 0));
	/////////////////////////////
	std::ofstream aqua(
		achievement_file, std::ios::in | std::ios::out | std::ios::app | std::ios::binary | std::ios::ate);
	aqua.close();
	std::ifstream achievement_in(achievement_file);
	std::string str;
	getline(achievement_in, str);
	for (int i = 0; i < str.size(); i++)
	{
		str[i] == '1' ? achievement_array[i].second = true : achievement_array[i].second = false;
	}
	achievement_in.close();
	std::ofstream achievement_out(achievement_file);
	for (auto& i : achievement_array)
	{
		achievement_out << i.second;
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
	for (unsigned int i = 0; i < str.size(); i++)
	{
		str[i] = std::tolower(str[i]);
	}
}

char int_to_letter(const int i)
{
	std::string alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return alf[i];
}

int letter_to_int(const char chr)
{
	std::string alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (int i = 0; i < alf.length(); i++) if (alf[i] == chr) return i;
	return 50;
}

std::vector<unsigned int> first_order(const size_t count)
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