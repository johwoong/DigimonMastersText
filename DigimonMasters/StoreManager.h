#pragma once
class StoreManager
{
	DECLARE_SINGLE(StoreManager)
public:
	bool Init();
	void Update(class Map* currentMap);

public:
	int OutputMenu();
};

