#pragma once
#include "Map.h"
#include "ObjectManager.h"
#include "Inventory.h"
#include "StoreManager.h"
#include "CPlayer.h"
#include "CEnemyDigimon.h"
#include "Skill.h"
#include "ItemEgg.h"
#include "ItemGeneric.h"
class CPlayer;
class CDigimon;
class CEnemyDigimon;
class MapStart : public Map
{
protected:
	MapStart();
	virtual ~MapStart();

protected:
	vector<class CEnemyDigimon*> m_enemyVec;
	int digimonCount;
protected:
	friend class MapManager;

public:
	virtual bool Init();
	virtual void Update();
public:
	virtual int OutputMap();
	virtual void Battle();
	virtual void CreateEnemy();
public:
	void Render();
	int OutputBattleMenu();
	int OutputEvoutuionMenu();
	void GenericAttack(CPlayer* player, CEnemyDigimon* digimon);
	void SkillAttack(CPlayer* player, CEnemyDigimon* digimon, int num);



};

