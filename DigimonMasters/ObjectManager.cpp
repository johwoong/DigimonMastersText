#include "pch.h"
#include "ObjectManager.h"
#include "CPlayer.h"
#include "CDigimon.h"
DEFINITION_SINGLE(ObjectManager)

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{
}



bool ObjectManager::Init()
{
	CDigimon* pDigimon = (CDigimon*)CreateObject("Digimon", OT_DIGIMON);
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
		pObj = new CDigimon;
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
	unordered_map<string, CObj*>::iterator iter = m_mapObj.find(strKey);

	if (iter == m_mapObj.end())
		return nullptr;

	return iter->second;
}

CObj* ObjectManager::CloneObject(const string& strKey)
{
	return nullptr;
}

CObj* ObjectManager::CloneObject(OBJECT_TYPE eType)
{
	return nullptr;
}
