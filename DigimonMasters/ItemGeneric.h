#pragma once
#include "Item.h"
class ItemGeneric :
    public Item
{
private:
    enum IT_KIND
    {
        IT_POSION,
        IT_MATERIAL,
    };


private:
    ItemGeneric();
    ItemGeneric(const ItemGeneric& item);
    ~ItemGeneric();

private:
    IT_KIND item_Kind;

private:
    friend class Store;
    friend class MapStart;
    friend class Inventory;

public:
    virtual bool Init();
    virtual void Render();
    virtual Item* Clone();
    virtual void Save(class FileStream* pFile);
    virtual void Load(class FileStream* pFile);

public:
    void SetItemKind(IT_KIND kind) { item_Kind = kind; }
    IT_KIND GetItemKind() const { return item_Kind; }
};

