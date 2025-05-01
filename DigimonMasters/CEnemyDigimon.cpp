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

void CEnemyDigimon::Render()
{
	SetConsoleColor(4);
	cout << "[������ ����]" << endl;
	cout << "�̸� : " << GetDigName() << "\t��ȭ �ܰ� : " << m_strEvName << endl;
	cout << "ü�� : " << m_tInfo.iHp << endl;
	cout << "���� : " << m_tInfo.iLevel << endl;
	cout << "���ݷ� : " << m_tInfo.iAttackMin << " ~ " << m_tInfo.iAttackMax << endl;
	cout << "���� : " << m_tInfo.iArmorMin << " ~ " << m_tInfo.iArmorMax << endl;
	cout << "��ų 1�� : " << m_useSkillVec[0]->GetSkillName() << "\t��ų ������ : " << m_useSkillVec[0]->GetSkillDamage() << endl;
	cout << "��ų 2�� : " << m_useSkillVec[1]->GetSkillName() << "\t��ų ������ : " << m_useSkillVec[1]->GetSkillDamage() << endl;
	ResetConsoleColor();
}

void CEnemyDigimon::Save(FileStream& stream)
{
}

void CEnemyDigimon::Load(FileStream& stream)
{
}

