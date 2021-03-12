#pragma once
#include <vector>
#include "ship.h"


class Fleet
{
public:
	Fleet();
	Fleet(const std::string& name);
	Fleet(const std::string& name, const std::vector<ship>& v);
	Fleet(const std::string& name, const std::vector<ship>& v, const bool& side);
	void Print(std::ostream& out)const;
	void Read(std::istream& in);
	void SetName(int index, const std::string name);
	void SetSide(bool side);
	std::vector<ship> GetFleet()const;
	bool AddShipToFleet(const ship& ship);
	bool RemoveShipFromFleet(const ship& ship);
	bool GetSide() const;
	ship GetShipByIndex(int ID)const;
	int GetFleetSize()const;

private:
	std::string name;
	std::vector<ship> fleet;
	bool side;
};