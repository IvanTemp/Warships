#pragma once
#include "ship.h"


class Fleet
{
public:
	Fleet() : side(count++) {};
	Fleet(const std::string& name);
	Fleet(const std::string& name, const std::vector<ship>& v);
	void Print(std::ostream& out)const;
	void Read(std::istream& in);
	void SetName(int index, const std::string name);
	std::string GetName()const;
	std::vector<ship> GetFleet()const;
	bool AddShipToFleet(const ship& ship);
	bool RemoveShipFromFleet(const ship& ship);
	bool GetSide() const;
	ship GetShipByIndex(const int ID)const;
	void DmgToInd(const int x, const int y, const int dmg);

private:
	static int count;
	std::string name;
	std::vector<ship> fleet;
	const bool side;
};