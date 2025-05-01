#pragma once
#include "Item.h"
class ItemEquip :
    public Item
{

private:
    ITEM_REGION m_itemRegionType;
    string m_regionName;
    ITEMSTAT m_itemStat;

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
    void SetItemStatInfo(int iAttack, int iArmor, int iDs, int iSpeed, int iSkillDamage);
    ITEMSTAT GetItemStat() { return m_itemStat; }
public:
    virtual bool Init();
    virtual void Render();
    virtual Item* Clone();


};

