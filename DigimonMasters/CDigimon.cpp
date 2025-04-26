#include "pch.h"
#include "CDigimon.h"
#include "Skill.h"

CDigimon::CDigimon() : m_strDigName(""), m_eType(EV_NONE), m_aType(AT_NONE)
{
	memset(&m_skillVec, 0, sizeof(m_skillVec));
}

CDigimon::CDigimon(const CDigimon& digimon) : CCharacter(digimon)
{
	m_strDigName = digimon.m_strDigName;
	m_eType = digimon.m_eType;
	m_aType = digimon.m_aType;
	m_skillVec = digimon.m_skillVec;
}

CDigimon::~CDigimon()
{ 

}

void CDigimon::SetDigName(string digName)
{
	m_strDigName = digName;
}

void CDigimon::SetEvalutionType(int number)
{
	m_eType = (EVALUTION)number;
}

void CDigimon::SetAttributeType(int number)
{
	m_aType = (ATTRIBUTE)number;
}

void CDigimon::AddSKill(Skill* skill)
{
	if (m_skillVec.size() >= 15)
		return;
	m_skillVec.push_back(skill);
}

void CDigimon::UpdateStat(int iAttack, int iArmor, int iSkillDamage)
{
	m_tInfo.iAttackMin += iAttack;
	m_tInfo.iArmorMax += iAttack;
	m_tInfo.iArmorMin += iArmor;
	m_tInfo.iArmorMax += iArmor;
	GetSkillList()[0]->SetSkillDamage(GetSkillList()[0]->GetSkillDamage() + iSkillDamage);
	GetSkillList()[1]->SetSkillDamage(GetSkillList()[0]->GetSkillDamage() + iSkillDamage);
}



bool CDigimon::Init()
{
	return true;
}

void CDigimon::Render()
{
	cout << "[������ ����]" << endl;
	cout << "�̸� : " << GetDigName() << endl;
	cout << "ü�� : " << m_tInfo.iHp << "\tDS : " << m_tInfo.iDs << endl;
	cout << "���� : " << m_tInfo.iLevel << "\t����ġ : " << m_tInfo.iExp << endl;
	cout << "���ݷ� : " << m_tInfo.iAttackMin << " ~ " << m_tInfo.iAttackMax << endl;
	cout << "���� : " << m_tInfo.iArmorMin << " ~ " << m_tInfo.iArmorMax << endl;
	cout << "��ų 1�� : " << m_skillVec[0]->GetSkillName() << "\t��ų ������ : " << m_skillVec[0]->GetSkillDamage() << endl;
	cout << "��ų 2�� : " << m_skillVec[1]->GetSkillName() << "\t��ų ������ : " << m_skillVec[1]->GetSkillDamage() << endl;
}


CDigimon* CDigimon::Clone()
{
	return new CDigimon(*this);
}
