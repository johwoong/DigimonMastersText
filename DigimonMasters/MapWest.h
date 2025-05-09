#pragma once
#include "MapStart.h"
class MapWest : public MapStart
{
private:
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
	virtual void CreateEnemy();
};

