#pragma once
#include "Store.h"
class StoreEgg :
    public Store
{
private:
    StoreEgg();
    ~StoreEgg();

private:
    friend class StoreManager;
public:
    virtual void Update();
    virtual int OutputMenu();
};

