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

public:
    virtual bool Init();
    virtual void Render();
    virtual Item* Clone();

public:
    void SetItemKind(IT_KIND kind) { item_Kind = kind; }
    IT_KIND GetItemKind() const { return item_Kind; }
public:
    virtual void Save(class FileStream& stream);
    virtual void Load(class FileStream& stream);
};

