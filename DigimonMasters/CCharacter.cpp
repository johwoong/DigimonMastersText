#include "pch.h"
#include "CCharacter.h"

CCharacter::CCharacter()
{
}

CCharacter::~CCharacter()
{
}


CCharacter::CCharacter(const CCharacter& character) : CObj(character)
{
}


void CCharacter::SetCharacterInfo(int iAttackMin, int iAttackMax, int iArmorMin, int iArmorMax, int iHpmax, int iDsMax, int iLevel, int iExp)
{
	m_tInfo.iAttackMin = iAttackMin;
	m_tInfo.iAttackMax = iAttackMax;
	m_tInfo.iArmorMin = iArmorMin;
	m_tInfo.iArmorMax = iArmorMax;
	m_tInfo.iHpMax = iHpmax;
	m_tInfo.iHp = m_tInfo.iHpMax;
	m_tInfo.iDsMax = iDsMax;
	m_tInfo.iDs = m_tInfo.iDsMax;
	m_tInfo.iLevel = iLevel;
	m_tInfo.iExp = iExp;
}

bool CCharacter::Init()
{
	return true;
}

void CCharacter::Render()
{

}
