#pragma once
#include "pch.h"
class Item;
class Inventory
{
	DECLARE_SINGLE(Inventory)


private:
	vector<Item*> m_Item_vec;

	int iWeight;
public:
	bool AddInventory(Item* item);
	void PrintItemList();
	int SelectOption();
	void UseItem();
	void ThrowItem();
	void DeleteItem(Item* item); // 외부에서 해당 아이템 삭제
	void EquipItem();
	void UnEquipItem();
	const vector<Item*> GetItemVec() const { return m_Item_vec; }
public:
	int GetWeight() { return iWeight; }
	void SetWeight(int value) { iWeight = value; }
public:
	bool Init();
	void Update();

};

