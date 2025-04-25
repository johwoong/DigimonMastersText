#pragma once
#include "Item.h"
class ItemEquip :
    public Item
{

private:
    int iArmorMin;
    int iArmorMax;
    int iDsMin;
    int iDsMax;
    int iSpeed;
    ITEM_REGION m_itemRegionType;
    string m_regionName;

private:
    ItemEquip();
    ItemEquip(const ItemEquip& item);
    ~ItemEquip();

private:
    friend class Store;


public:
    void SetItemRegion(ITEM_REGION eType);
    ITEM_REGION GetItemRegion() { return m_itemRegionType; }
    string GetItemRegionName() { return m_regionName; }
    void SetItemStatInfo(int iArmorMin, int iArmorMax, int iDsMin, int iDsMax, int iSpeed);
 
public:
    virtual bool Init();
    virtual void Render();
    virtual Item* Clone();

};

