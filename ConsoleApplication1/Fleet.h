#pragma once
#include <vector>
#include "ship.h"

class Fleet
{
public:
	Fleet();
	Fleet(const std::string& name);
	Fleet(const std::string& name, const std::vector<ship>& v);
	void Print(std::ostream& out)const;
	void Read(std::istream& in);
	void SetName(int index, const std::string name);
	std::vector<ship> GetFleet()const;
	bool AddshipToFleet(const ship& ship);
	bool RemoveshipFromFleet(const ship& ship);
	ship& GetshipByIndex(int index);

private:
	std::string name;
	std::vector<ship> fleet;
};