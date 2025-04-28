#pragma once
#include "Map.h"
class MapDart :
    public Map
{
	enum MEUU
	{
		MENU_NONE,
		MENU_TALK,
		MENU_STORE,
		MENU_INVENTORY,
		MENU_STATUS,
		MENU_DIGIMONSTATIUS,
		MENU_INCUBATOR,
		MENU_EXIT,
	};

private:
    MapDart();
    ~MapDart();

private:
    friend class MapManager;
public:
    virtual bool Init();
    virtual void Update();

private:
	int OutputMenu();
	void SelectDigimon();
	virtual int OutputMap();

public:
	virtual void Battle();
};

