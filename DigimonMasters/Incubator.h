#pragma once
#include "ItemEgg.h"
class Incubator
{
	DECLARE_SINGLE(Incubator)

private:
	ItemEgg* m_egg; // 디지몬 알
	int iStage ; // 현재 단계
	vector<Item*> m_eggItem_vec;
	bool isHatch; // 부화가능여부
public:
	void SetEggVec();
	int OutputMenu();
	void HatchDigimon(); // 디지몬 부화
	void DeleteEgg(); // 디지몬 알 해제
	void CreateDigimon(); // 디지몬 생성
private:
	friend class MapDart;
	friend class CGame;
	
public:
	bool Init();
	void Update();
	void Save(class FileStream* pFile);
	void Load(class FileStream* pFile);
 };

