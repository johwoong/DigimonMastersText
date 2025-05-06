#pragma once
#include "pch.h"
class Item;
class Inventory
{
	DECLARE_SINGLE(Inventory)

private:
	enum ITEM_CLASS_TYPE
	{
		ICT_BASE,
		ICT_EGG,
		ICT_EQUIP,
		ICT_GENERIC
	};

private:
	vector<Item*> m_Item_vec;

	int iWeight;
public:
	bool AddInventory(Item* item);
	void PrintItemList();
	int SelectOption();
	void UseItem();
	void ThrowItem();
	void DeleteItem(Item* item); // �ܺο��� �ش� ������ ����
	void EquipItem();
	void UnEquipItem();
	const vector<Item*> GetItemVec() const { return m_Item_vec; }
public:
	int GetWeight() { return iWeight; }
	void SetWeight(int value) { iWeight = value; }
public:
	bool Init();
	void Update();
	void Save(class FileStream* pFile);
	void Load(class FileStream* pFile);
};

