#include "pch.h"
#include "ObjectManager.h"
#include "CPlayer.h"
DEFINITION_SINGLE(ObjectManager)

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{
}



bool ObjectManager::Init()
{
	return true;
}

CObj* ObjectManager::CreateObject(const string& strKey, OBJECT_TYPE eType)
{
	CObj* pObj = nullptr;
	switch (eType)
	{
	case OT_PLAYER:
		pObj = new CPlayer;
		break;
	case OT_DIGIMON:
		break;
	case OT_ENEMYDIGIMON:
		break;
	case OT_NPC:
		break;
	}

	if (!pObj->Init())
	{
		SAFE_DELETE(pObj);
		return nullptr;
	}
	
	m_mapObj.insert(make_pair(strKey, pObj));
	return pObj;
}

CObj* ObjectManager::FindObject(const string& strKey)
{
	return nullptr;
}

CObj* ObjectManager::CloneObject(const string& strKey)
{
	return nullptr;
}

CObj* ObjectManager::CloneObject(OBJECT_TYPE eType)
{
	return nullptr;
}
