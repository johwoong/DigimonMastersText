#pragma once
#include "Map.h"
class CPlayer;
class MapSnow :
    public Map
{
private:
private:
	MapSnow();
	~MapSnow();

private:
	vector<class CDigimon*> m_enemyVec;
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
	void GenericAttack(CPlayer* player, CDigimon* digimon);
	void SkillAttack(CPlayer* player, CDigimon* digimon, int num);
};

