#include "pch.h"
#include "ObjectManager.h"
#include "CPlayer.h"
#include "CDigimon.h"
#include "Item.h"

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
	pDigimon = (CDigimon*)CreateObject("EnemyDigimon", OT_ENEMYDIGIMON);
	Item* item = (Item*)CreateObject("Item", OT_ITEM);
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
		pObj = new CDigimon;
		break;
	case OT_ITEM:
		pObj = new Item;
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
	CObj* pOrigin = FindObject(strKey);

	if (!pOrigin)
		return nullptr;
	return pOrigin->Clone();
}

CObj* ObjectManager::CloneObject(OBJECT_TYPE eType)
{
	return nullptr;
}
