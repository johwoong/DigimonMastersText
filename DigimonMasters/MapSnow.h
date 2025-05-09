#pragma once
#include "MapStart.h"
class CPlayer;
class MapSnow :
    public MapStart
{
private:
private:
	MapSnow();
	~MapSnow();

private:
	friend class MapManager;

public:
	virtual bool Init();
	virtual void Update();
public:
	virtual int OutputMap();
	virtual void CreateEnemy();
};

