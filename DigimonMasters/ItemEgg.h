#pragma once
#include "Item.h"
class ItemEgg :
    public Item
{
private:
    ItemEgg();
    ItemEgg(const ItemEgg& item);
    ~ItemEgg();

private:
    friend class Store;
    friend class MapStart;

public:
    virtual bool Init();
    virtual void Render();
    virtual Item* Clone();
};

