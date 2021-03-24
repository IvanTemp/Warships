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
		for (int j = 0; j < fleet[i].GetDurability().size(); j++)
		{
			hp += fleet[i].GetDurability()[j];
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
	//Проверка на пустой
	int len = fleet.size();
	if (fleet.begin() == fleet.end())
		return false;
	//Добавим проверку удаления несуществующего
	bool flag = 0;
	for (int i = 0; i < fleet.size(); i++)
	{
		if (fleet[i] == shp)
		{
			//Само удаление
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
	//Gura AI(c). All rights not reserved.
	bool GwSUtPaLT = true; //Gura was still unable to plant a large tree
	unsigned int attempts = difficulty;
	while (GwSUtPaLT) {
		x = rand() % width_height, y = rand() % width_height;
		if (DEBUG_MODE) std::cout << "[DEBUG INFO]Trying to: x = " << x << "; y = " << y << std::endl;

		if (BOTRoDC.size()) { //I)Finishing off found ships
			x = BOTRoDC[0].first, y = BOTRoDC[0].second;
			BOTRoDC.erase(BOTRoDC.begin());
			GwSUtPaLT = false;
		}
		else {
			if (ReturnFieldWar(side, x, y) == 0) { // II)Protection against shooting at empty cells
				if (attempts) {
					if (ReturnFieldID(side, x, y) < 2) {
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

	char strx = IntToLetter(x);

	if (ReturnFieldID(side, x, y) > 1) {
		GetDamage(side, x, y, dmg, fleet);
	}
	else {
		std::cout << "The enemy missed! X = " << strx << "; Y = " << y << std::endl;
	}
	Field_Get_Vision(x, y, side);
}

void Fleet::ConsDmgToIndPlayer(const int dmg) {
	int x = 0, y = -1;
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

	if (ReturnFieldID(side, x, y) > 1) {
		if (fleet[ReturnFieldID(side, x, y) - 2].GetDurability()[ReturnFieldIndex(side, x, y)]) {
			GetDamage(side, x, y, dmg, fleet);
		}
		else {
			std::cout << "Why did you shoot at an already sunk ship?" << std::endl;
		}
	}
	else {
		std::cout << "Miss! X = " << alf[x] << "; Y = " << y << std::endl;
	}
		Field_Get_Vision(x, y, side);
}

void Fleet::NUCLEAR_BOMB() {
	for (int i = 0; i < fleet.size(); i++) {
		fleet[i].NUCLEAR_BOMB();
	}
}


