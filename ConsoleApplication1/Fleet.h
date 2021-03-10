#pragma once
#include "ship.h"
#include <vector>
class Fleet
{
public:
	Fleet();
	Fleet(const std::vector<ship>& v);
	void Print()const;
	bool AddshipToFleet(const ship& ship);
	bool RemoveshipFromFleet(const ship& ship);
	ship& GetshipByIndex(int index);

private:
	std::vector<ship> fleet;
};

