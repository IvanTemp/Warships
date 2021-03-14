#include <string>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <iostream>
#include "Fleet.h"
#include "generator.h"

int Fleet::count = 0;


Fleet::Fleet(const std::string& nm):name(nm), side(count++)
{
}

Fleet::Fleet(const std::string& nm, const std::vector<ship>& v): name(nm), fleet(v), side(count++)
{
}

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


void Fleet::DmgToInd(const int x, const int y, const int dmg)
{
	if (ReturnFieldID(side, x, y) > 1)
	{
		int Index = ReturnFieldID(side, x, y) - 2;
		int DurabtyIndex = ReturnFieldIndex(side, x, y);
		fleet[Index].DmgtoInd(dmg, DurabtyIndex);
		if (DEBUG_MODE)
		{
			std::cout << "Fleet: " << name;
			std::cout << "; new durability =";
			for (int i = 0; i < fleet[Index].GetDurability().size(); i++)
			{
				std::cout << " " << fleet[Index].GetDurability()[i];
			}
			std::cout << std::endl;
		}
		Field_Get_Vision(x, y, !side);
		Field_Refresh_Durability(fleet, side);
	}
}

void Fleet::ConsDmgToInd()
{
	int x = 0, y = 0, dmg = 0;
	std::string alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char stry;
	std::cin >> x >> stry >> dmg;
	for (int i = 0; i < alf.size(); i++)
	{
		if (alf[i] == stry)
		{
			y = i;
			break;
		}
	}
	if (ReturnFieldID(side, x, y) > 1)
	{
		int Index = ReturnFieldID(side, x, y) - 2;
		int DurabtyIndex = ReturnFieldIndex(side, x, y);
		fleet[Index].DmgtoInd(dmg, DurabtyIndex);
		if (DEBUG_MODE)
		{
			std::cout << "Fleet: " << name;
			std::cout << "Ship name: " << fleet[Index].GetName();
			std::cout << "; new durability =";
			for (int i = 0; i < fleet[Index].GetDurability().size(); i++)
			{
				std::cout << " " << fleet[Index].GetDurability()[i];
			}
			std::cout << std::endl;
		}
		Field_Get_Vision(x, y, !side);
		Field_Refresh_Durability(fleet, side);
	}
	else
	{
		std::cout << "Miss! X = " << x << "; Y = "<< y << std::endl;
	}
}


