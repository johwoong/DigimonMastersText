#pragma once
#include "pch.h"
class Store
{
protected:
	Store();
	virtual ~Store();

protected:
	vector<class Item*> m_vecItemList;

private:
	friend class MapStart;

public:
	virtual void ShowList();
public:
	virtual void Update() = 0;
	virtual int OutputMenu() = 0;
public:
	class Item* CreateItem(string pName, ITEM_TYPE eType, int iPrice, int iWeight, string Desc);
	void AddInventoryInItem(class Item* item);

};

