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
    class CDigimon* p_digimon;

private:
    friend class Store;
    friend class MapStart;
public:
    virtual bool Init();
    virtual void Render();
    virtual Item* Clone();
    virtual void Save(class FileStream* pFile);
    virtual void Load(class FileStream* pFile);


public:
    void SetDigimonInfo(
        const string& name,
        int attackMin, int attackMax,
        int armorMin, int armorMax,
        int hpMax, int dsMax,
        int level, int exp, int fat, int speed,
        int attributeType,
        const vector<pair<string, pair<int, int>>>& skills,
        const vector<tuple<string, int, int, int, int>>& evolutions
    );

    class CDigimon* GetDigimon() { return p_digimon; }

};

