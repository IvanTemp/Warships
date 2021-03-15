#include <string>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <iostream>
#include "Fleet.h"
#include "generator.h"

std::vector <std::pair <unsigned int, unsigned int>> BOTRoDC; //BOT Repository Of Detected Cells

int Fleet::count = 0;

Fleet::Fleet(const std::string& nm):name(nm), side(count++) {}

Fleet::Fleet(const std::string& nm, const std::vector<ship>& v): name(nm), fleet(v), side(count++) {}

void Fleet::Print(std::ostream& out) const
{
	out << "=====Fleet " << name << "=====" << std::endl;
	if (fleet.size())
	{
		for (const auto& x : fleet)
		{
			x.Print(out);
		}
	}
	else
	{
		out << "Fleet is empty" << std::endl;
	}
}

void Fleet::Read(std::istream& in)
{
	getline(in,name);
	std::string count = "";
	getline(in,count);
	for (int i = 0; i < stoi(count); i++)
	{
		ship newShip;
		newShip.Read(in);
		AddShipToFleet(newShip);
	}
}

void Fleet::SetName(int index,const std::string nm)
{
	fleet.at(index).SetName(nm);
}

std::string Fleet::GetName() const
{
	return name;
}

std::vector<ship> Fleet::GetFleet() const
{
	return fleet;
}

unsigned int Fleet::GetHealth() const
{
	unsigned int hp = 0;
	for (int i = 0; i < fleet.size(); i++)
	{
		for (int j = 0; j < fleet[0].GetDurability().size(); j++)
		{
			hp += fleet[0].GetDurability()[j];
		}
	}
	return hp;
}

bool Fleet::AddShipToFleet(const ship& shp)
{
	for (int i = 0; i < fleet.size(); i++)
	{
		if (fleet[i] == shp)
		{
			std::cout << "Ship is already added" << std::endl;
			return false;
		}
	}
	fleet.push_back(shp);
	return true;
}

bool Fleet::RemoveShipFromFleet(const ship& shp)
{
	//Ïðîâåðêà íà ïóñòîé
	int len = fleet.size();
	if (fleet.begin() == fleet.end())
		return false;
	//Äîáàâèì ïðîâåðêó óäàëåíèÿ íåñóùåñòâóþùåãî
	bool flag = 0;
	for (int i = 0; i < fleet.size(); i++)
	{
		if (fleet[i] == shp)
		{
			//Ñàìî óäàëåíèå
			fleet.erase(std::remove(fleet.begin(), fleet.end(), shp));
			flag = 1;
			std::cout << "One ship removed!" << std::endl;
			return (len > fleet.size());
		}
	}
	if (!flag)
	{
		std::cout << "No ship to delete" << std::endl;
		return false;
	}
}

bool Fleet::GetSide()const {
	return side;
}

ship Fleet::GetShipByIndex(const int ID)const {
	return fleet.at(ID);
	//try
	//{
	//	return fleet.at(index);
	//}
	//catch (std::out_of_range)
	//{
	//	std::cout << "Index out of range" << std::endl;
	//	throw;
	//}
}


void Fleet::ConsDmgToIndBot(const int dmg, const int difficulty) {
	srand(time(0));
	int x = 0, y = 0;
	if (difficulty != 2) {
		//Gura AI(c). All rights reserved.
		bool GwSUtPaLT = true; //Gura was still unable to plant a large tree
		while (GwSUtPaLT) {
			x = -1 + rand() % width_height + 1, y = -1 + rand() % width_height + 1;
			if (DEBUG_MODE) std::cout << "[DEBUG INFO]Trying to: x = " << x << "; y = " << y << std::endl;
			if (BOTRoDC.size()) {
				x = BOTRoDC[0].first, y = BOTRoDC[0].second;
				BOTRoDC.erase(BOTRoDC.begin());
				GwSUtPaLT = false; // :)
			} else {
				if (ReturnFieldWar(side, x, y) == 0 || ReturnFieldDurability(side, x, y) > 0) { break; } // II)Protection against shooting at empty cells
			}
			if (DEBUG_MODE) std::cout << "[DEBUG INFO]Gura(c) decided that: x = " << x << "; y = " << y << std::endl;
		}
	}

	NUCLEAR_BOMB(side);

	std::string alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ", strx = "";
	strx = alf[x];

	if (ReturnFieldID(side, x, y) > 1)
	{
		int Index = ReturnFieldID(side, x, y) - 2;
		int DurabtyIndex = ReturnFieldIndex(1, x, y);
		int drbltSum = 0;
		fleet[Index].DmgtoInd(dmg, DurabtyIndex);
		std::cout << "The enemy hit your ship in " << strx << " " << y << std::endl;
		if (ReturnFieldDurability(side, x, y) > 1) { BOTRoDC.push_back({ x, y }); } //Memorizing an unfinished cell
		if (DEBUG_MODE) {
			std::cout << "[DEBUG INFO]Fleet: " << name;
			std::cout << "; Ship name: " << fleet[Index].GetName();
			std::cout << "; new durability =";
			for (int i = 0; i < fleet[Index].GetDurability().size(); i++) {
				std::cout << " " << fleet[Index].GetDurability()[i];
			}
			std::cout << std::endl;
		}
		for (int i = 0; i < fleet[Index].GetDurability().size(); i++) {
			drbltSum += fleet[Index].GetDurability()[i];
		}
		if (!drbltSum) {
			std::cout << "Captain! Your ship has been sunk!" << std::endl;
			//ÑÞÄÀ ÊÎÄ ÎÒÊÐÛÒÈß ÊËÅÒÎÊ ÏÎÑËÅ ÏÎÒÎÏËÅÍÈß ÊÎÐÀÁËß
		}
	}
	else
	{
		std::cout << "The enemy missed! X = " << strx << "; Y = " << y << std::endl;
	}
	Field_Get_Vision(x, y, side);
}

void Fleet::ConsDmgToIndPlayer(const int dmg)
{
	int x = 0, y = -1;
	bool notDumbUser = true;
	std::string alf = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
	char strx;
	std::cin >> strx >> y;

	if (y > width_height) {
		std::cout << "Captain! You shot out of bounds!" << std::endl;
		notDumbUser = false;
		return;
	}
	for (int i = 0; i < width_height * 2; i++)
	{
		if (alf[i] == strx) {
			x = i / 2;
			break;
		}
		if (i == width_height * 2 - 1) {
			std::cout << "Captain! You shot out of bounds!" << std::endl;
			notDumbUser = false;
			break;
		}
	}
	if (DEBUG_MODE) { std::cout << "X = " << x << " Y = " << y << std::endl; }
	if (notDumbUser) {
		if (ReturnFieldID(side, x, y) > 1)
		{
			int Index = ReturnFieldID(side, x, y) - 2;
			int DurabtyIndex = ReturnFieldIndex(side, x, y);
			fleet[Index].DmgtoInd(dmg, DurabtyIndex);
			std::cout << "Dodge this! You are hit!" << std::endl;
			if (DEBUG_MODE) {
				std::cout << "[DEBUG INFO]Fleet: " << name;
				std::cout << "; Ship name: " << fleet[Index].GetName();
				std::cout << "; new durability =";
				for (int i = 0; i < fleet[Index].GetDurability().size(); i++)
				{
					std::cout << " " << fleet[Index].GetDurability()[i];
				}
				std::cout << std::endl;
			}
		}
		else
		{
			std::cout << "Miss! X = " << strx << "; Y = " << y << std::endl;
		}
		Field_Get_Vision(x, y, side);
	}
}


