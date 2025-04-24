#pragma once
#include "Map.h"
class MapWest : public Map
{
private:
	MapWest();
	~MapWest();


private:
	friend class MapManager;

public:
	virtual bool Init();
	virtual void Update();
public:
	virtual int OutputMap();
	virtual void Battle();
};

