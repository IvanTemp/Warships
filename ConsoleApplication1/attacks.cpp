#include "fleet.h"
#include "generator.h"
#include "attacks.h"

void Simple_Attack(const bool side, const int x, const int y, const int dmg)
{
	int shipindexfromfield = ReturnFieldID(side, x, y);
	int indexshipdurabtyfromfield = ReturnFieldIndex(side, x, y);
	
}
