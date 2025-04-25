#pragma once
#include "Store.h"
class StoreGeneric :
    public Store
{
private:
    StoreGeneric();
    ~StoreGeneric();

private:
    friend class StoreManager;
public:
    virtual void Update();
    virtual int OutputMenu();
};

