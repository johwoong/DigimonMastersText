#pragma once
#include "CDigimon.h"
class Item;
class CEnemyDigimon :
    public CDigimon
{
private:
    CEnemyDigimon();
    CEnemyDigimon(const CEnemyDigimon& enemy);
    ~CEnemyDigimon();

private:
    int iGold;
    vector<Item*> m_dropVec;

private:
    friend class ObjectManager;

public:
    void SetGold(int gold);
    void SetItemList(Item* item);
    void DropItem();
public:
    virtual CDigimon* Clone();
    virtual void Render();
};

