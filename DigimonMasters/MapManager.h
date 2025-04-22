#pragma once
class MapManager
{
private:
	vector<class Map*> m_vecMap;
public:
	bool Init();
	void Update();

private:
	bool CreateMap(MAP_TYPE eType);

public:
	DECLARE_SINGLE(MapManager)
};

