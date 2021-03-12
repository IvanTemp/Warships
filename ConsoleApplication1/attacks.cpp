//#include <iostream>
//#include "fleet.h"
//#include "generator.h"
//#include "attacks.h"
//
////void Simple_Attack(const Fleet& fleet, const int x, const int y, const int dmg) {
////	int ID = ReturnFieldID(fleet.GetSide(), x, y);
////	fleet.GetShipByIndex(ID - 2).GetDamage(dmg, ReturnFieldIndex(fleet.GetSide(), x, y));
////	std::cout << "TEST: " << fleet.GetShipByIndex(ID - 2).GetDurability()[ReturnFieldIndex(fleet.GetSide(), x, y)] << std::endl;
////	Field_Refresh_Durability(fleet.GetShipByIndex(ID - 2), fleet.GetSide());
////}
//
//void Attack(Fleet flet, const int x, const int y, const int dmg)
//{
//	int Index = -2 + ReturnFieldID(flet.GetSide(), x, y);
//	int DurabtyIndex = ReturnFieldIndex(flet.GetSide(), x ,y);
//	flet.DmgToInd(Index, DurabtyIndex, dmg);
//	Field_Refresh_Durability(flet.GetShipByIndex(Index), flet.GetSide());
//}
//
//void Heal(Fleet flet, const int x, const int y, const int dmg)
//{
//	int Index = -2 + ReturnFieldID(flet.GetSide(), x, y);
//	int DurabtyIndex = ReturnFieldIndex(flet.GetSide(), x, y);
//	flet.DmgToInd(Index, DurabtyIndex, (-1)*dmg);
//	Field_Refresh_Durability(flet.GetShipByIndex(Index), flet.GetSide());
//}
