#pragma once
#include "CObj.h"
class Item : public CObj
{
protected:
	Item();
	Item(const Item& item);
public:
	virtual ~Item();

protected:
	ITEMINFO	m_tInfo;
	
private:
	friend class ObjectManager;
	friend class CPlayer;
	friend class Inventory;

public:
	virtual bool Init();
	virtual void Render();
	virtual Item* Clone();

public:
	void SetItemInfo(ITEM_TYPE itemType, string strName, int iPrice, int iWeight, string strDesc);
	ITEMINFO GetItemInfo() { return m_tInfo; }
};

