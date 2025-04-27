#include "pch.h"
#include "CEnemyDigimon.h"
#include "Skill.h"
#include "Inventory.h"
#include "Item.h"



CEnemyDigimon::CEnemyDigimon() : iGold(0)
{

}

CEnemyDigimon::CEnemyDigimon(const CEnemyDigimon& enemy) : CDigimon(enemy)
{
	iGold = enemy.iGold;
	m_dropVec = enemy.m_dropVec;
}


CEnemyDigimon::~CEnemyDigimon()
{
	Safe_Delete_VecList(m_dropVec);
}

void CEnemyDigimon::SetGold(int gold)
{
	iGold = gold;
}

void CEnemyDigimon::SetItemList(Item* item)
{
	m_dropVec.push_back(item);
}

void CEnemyDigimon::DropItem()
{
	Item* item = m_dropVec[rand() % m_dropVec.size()]->Clone();
	if (!GET_SINGLE(Inventory)->AddInventory(item))
		cout << "�κ��丮�� �� á���ϴ�!!" << endl;
	else
		cout << item->GetItemInfo().strName << "�� ȹ���Ͽ����ϴ�!!" << endl;
}

CDigimon* CEnemyDigimon::Clone()
{
	return new CEnemyDigimon(*this);
}

