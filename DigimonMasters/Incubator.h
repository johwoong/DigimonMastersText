#pragma once
#include "ItemEgg.h"
class Incubator
{
	DECLARE_SINGLE(Incubator)

private:
	ItemEgg* m_egg; // ������ ��
	int iStage ; // ���� �ܰ�
	vector<Item*> m_eggItem_vec;
	bool isHatch; // ��ȭ���ɿ���
public:
	void SetEggVec();
	int OutputMenu();
	void HatchDigimon(); // ������ ��ȭ
	void DeleteEgg(); // ������ �� ����
	void CreateDigimon(); // ������ ����
private:
	friend class MapDart;
	friend class CGame;
	
public:
	bool Init();
	void Update();
	void Save(class FileStream* pFile);
	void Load(class FileStream* pFile);
 };

