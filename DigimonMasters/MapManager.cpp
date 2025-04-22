#include "pch.h"
#include "MapManager.h"
#include "MapDart.h"

DEFINITION_SINGLE(MapManager)

MapManager::MapManager()
{

}

MapManager::~MapManager()
{
	Safe_Delete_VecList(m_vecMap);
}

bool MapManager::Init()
{
	if (!CreateMap(MT_DART))
		return false;
	return true;
}

void MapManager::Update()
{
	m_vecMap[0]->Update();
}

bool MapManager::CreateMap(MAP_TYPE eType)
{
	Map* pMap = nullptr;
	switch (eType)
	{
	case MT_DART:
		pMap = new MapDart;
		break;
	case MT_START:
		break;
	case MT_SNOW:
		break;
	case MT_SAND:
		break;
	}

	if (!pMap->Init())
	{
		SAFE_DELETE(pMap);
		return false;
	}

	m_vecMap.push_back(pMap);
	return true;
}
