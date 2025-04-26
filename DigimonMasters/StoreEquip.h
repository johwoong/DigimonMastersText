#pragma once
#include "Store.h"
class StoreEquip :
    public Store
{
private:
    StoreEquip();
    ~StoreEquip();

private:
    friend class StoreManager;
public:
    virtual void Update();
    virtual int OutputMenu();

private:
    int iHead;
    int iShirt;
    int iGlove;
    int iPant;
    int iShoes;
public:
    void ShowHeadList();
    void ShowShirtList();
    void ShowGloveList();
    void ShowPantList();
    void ShowShoesList();
    
};

