#pragma once
class Map
{
public:
	Map();
	virtual ~Map();

protected:
	string strMapName;

public:
	virtual bool Init() = 0;
	virtual void Update() = 0;
public:
	virtual int OutputMap();
};

