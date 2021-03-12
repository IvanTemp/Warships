#include <string>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include "Fleet.h"

Fleet::Fleet()
{
}

Fleet::Fleet(const std::string& nm):name(nm)
{
}

Fleet::Fleet(const std::string& nm, const std::vector<ship>& v): name(nm), fleet(v)
{
}

Fleet::Fleet(const std::string& name, const std::vector<ship>& v, const bool& side)
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
	for (int i = 0; i < count[0] - '0'; i++)
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

void Fleet::SetSide(bool s) {
	side = s;
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
	//�������� �� ������
	int len = fleet.size();
	if (fleet.begin() == fleet.end())
		return false;
	//������� �������� �������� ���������������
	bool flag = 0;
	for (int i = 0; i < fleet.size(); i++)
	{
		if (fleet[i] == shp)
		{
			//���� ��������
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

ship Fleet::GetShipByIndex(int ID)const {
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

int Fleet::GetFleetSize() const {
	return fleet.size();
}


