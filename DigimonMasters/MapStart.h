#pragma once
#include "Map.h"
class CPlayer;
class CDigimon;
class CEnemyDigimon;
class MapStart : public Map
{
private:
	MapStart();
	~MapStart();

private:
	vector<class CEnemyDigimon*> m_enemyVec;
	int digimonCount;
private:
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

