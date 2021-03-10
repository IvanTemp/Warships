#include <string>
#include <algorithm>
#include "Fleet.h"

Fleet::Fleet()
{
}

Fleet::Fleet(const std::vector<ship>& v):fleet(v)
{
}

void Fleet::Print() const
{
	for (const auto& x : fleet)
	{
		x.Print();
	}
}

bool Fleet::AddshipToFleet(const ship& ship)
{
	for (const auto& x : fleet)
	{
		if(ship.IsEqual(ship))
			return false;
	}
	fleet.push_back(ship);
	return true;
}

bool Fleet::RemoveshipFromFleet(const ship& ship)
{
	fleet.erase(std::remove(fleet.begin(), fleet.end(), ship));
	return true;
}

ship& Fleet::GetshipByIndex(int index)
{
	// TODO: вставьте здесь оператор return
}
