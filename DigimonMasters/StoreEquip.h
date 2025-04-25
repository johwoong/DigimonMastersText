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


public:
    void ShowHeadList();
    void ShowShirtList();
    void ShowGloveList();
    void ShowShoesList();
    
};

