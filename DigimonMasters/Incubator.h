#pragma once
#include "ItemEgg.h"
class Incubator
{
private:
	Incubator();
	~Incubator();

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
	
public:
	bool Init();
	void Update();
 };

