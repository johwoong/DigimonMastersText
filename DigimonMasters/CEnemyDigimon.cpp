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
		cout << "인벤토리가 꽉 찼습니다!!" << endl;
	else
		cout << item->GetItemInfo().strName << "을 획득하였습니다!!" << endl;
}

CDigimon* CEnemyDigimon::Clone()
{
	return new CEnemyDigimon(*this);
}

void CEnemyDigimon::Render()
{
	SetConsoleColor(4);
	cout << "[디지몬 정보]" << endl;
	cout << "이름 : " << GetDigName() << "\t진화 단계 : " << m_strEvName << endl;
	cout << "체력 : " << m_tInfo.iHp << endl;
	cout << "레벨 : " << m_tInfo.iLevel << endl;
	cout << "공격력 : " << m_tInfo.iAttackMin << " ~ " << m_tInfo.iAttackMax << endl;
	cout << "방어력 : " << m_tInfo.iArmorMin << " ~ " << m_tInfo.iArmorMax << endl;
	cout << "스킬 1번 : " << m_useSkillVec[0]->GetSkillName() << "\t스킬 데미지 : " << m_useSkillVec[0]->GetSkillDamage() << endl;
	cout << "스킬 2번 : " << m_useSkillVec[1]->GetSkillName() << "\t스킬 데미지 : " << m_useSkillVec[1]->GetSkillDamage() << endl;
	ResetConsoleColor();
}

void CEnemyDigimon::Save(FileStream& stream)
{
}

void CEnemyDigimon::Load(FileStream& stream)
{
}

