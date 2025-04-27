#include "pch.h"
#include "CDigimon.h"
#include "Skill.h"

CDigimon::CDigimon() : m_strDigName(""), m_aType(AT_NONE), m_eType(EV_GROW), m_strEvName("성장기")
{

}

CDigimon::CDigimon(const CDigimon& digimon) : CCharacter(digimon)
{
	m_strDigName = digimon.m_strDigName;
	m_strEvName = digimon.m_strEvName;
	m_eType = digimon.m_eType;
	m_aType = digimon.m_aType;
	m_skillVec = digimon.m_skillVec;
	m_useSkillVec = digimon.m_useSkillVec;
	m_evInfo = digimon.m_evInfo;
}

CDigimon::~CDigimon()
{ 
	Safe_Delete_VecList(m_skillVec);
	Safe_Delete_VecList(m_useSkillVec);
}



void CDigimon::SetDigName(string digName)
{
	m_strDigName = digName;
}


void CDigimon::SetAttributeType(int number)
{
	m_aType = (ATTRIBUTE)number;
}

void CDigimon::SetEvaultionType(int number)
{
	m_eType = (EVALUTION)number;
}

void CDigimon::AddSKill(Skill* skill)
{
	if (m_skillVec.size() >= 15)
		return;
	m_skillVec.push_back(skill);
}

void CDigimon::UpdateStat(int iAttack, int iArmor, int iSkillDamage, int iSkillDamage2)
{
	m_tInfo.iAttackMin += iAttack;
	m_tInfo.iArmorMax += iAttack;
	m_tInfo.iArmorMin += iArmor;
	m_tInfo.iArmorMax += iArmor;
	GetUseSkillList()[0]->SetSkillDamage(GetUseSkillList()[0]->GetSkillDamage() + iSkillDamage);
	GetUseSkillList()[1]->SetSkillDamage(GetUseSkillList()[1]->GetSkillDamage() + iSkillDamage2);
}

void CDigimon::SetEvaultionList(string strName, int iHp, int iDs, int iAttack, int iArmor)
{
	EVINFO info;
	info.strName = strName;
	info.iHp = iHp;
	info.iDs = iDs;
	info.iAttack = iAttack;
	info.iArmor = iArmor;
	m_evInfo.push_back(info);
}

void CDigimon::Ev_Maturity()
{
	if (m_eType == EV_GROW)
	{
		system("cls");
		cout << m_strDigName << "이 " << m_evInfo[0].strName << "으로 진화합니다..." << endl;
		cout << "3" << endl;
		Sleep(1000);
		cout << "2" << endl;
		Sleep(1000);
		cout << "1" << endl;
		Sleep(1000);
		m_eType = EV_MATURITY;
		m_strDigName = m_evInfo[0].strName;
		m_strEvName = "성숙기";
		m_tInfo.iHpMax += m_evInfo[0].iHp;
		m_tInfo.iHp = m_tInfo.iHpMax;
		m_tInfo.iDsMax = m_evInfo[0].iDs;
		m_tInfo.iDs = m_tInfo.iDsMax;
		m_tInfo.iAttackMax += m_evInfo[0].iAttack;
		m_tInfo.iAttackMin += m_evInfo[0].iAttack;
		m_tInfo.iArmorMax += m_evInfo[0].iArmor;
		m_tInfo.iArmorMin += m_evInfo[0].iArmor;
		UpdateSkill();
	}
	else
		cout << "진화 할 수 없습니다..." << endl; system("pause"); return;
}

void CDigimon::Ev_Integer()
{
	if (m_eType == EV_GROW || m_eType == EV_MATURITY)
	{
		system("cls");
		cout << m_strDigName << "이 " << m_evInfo[1].strName << "  으로 진화합니다..." << endl;
		cout << "3" << endl;
		Sleep(1000);
		cout << "2" << endl;
		Sleep(1000);
		cout << "1" << endl;
		Sleep(1000);
		m_eType = EV_INTEGER;
		m_strDigName = m_evInfo[1].strName;
		m_strEvName = "완전체";
		m_tInfo.iHpMax += m_evInfo[1].iHp;
		m_tInfo.iHp = m_tInfo.iHpMax;
		m_tInfo.iDsMax = m_evInfo[1].iDs;
		m_tInfo.iDs = m_tInfo.iDsMax;
		m_tInfo.iAttackMax += m_evInfo[1].iAttack;
		m_tInfo.iAttackMin += m_evInfo[1].iAttack;
		m_tInfo.iArmorMax += m_evInfo[1].iArmor;
		m_tInfo.iArmorMin += m_evInfo[1].iArmor;
		UpdateSkill();
	}
	else
		cout << "진화 할 수 없습니다..." << endl; system("pause"); return;
}

void CDigimon::Ev_Ultimat()
{
	if (m_eType == EV_GROW || m_eType == EV_MATURITY || m_eType == EV_INTEGER)
	{
		system("cls");
		cout << m_strDigName << "이 " << m_evInfo[2].strName << "  으로 진화합니다..." << endl;
		cout << "3" << endl;
		Sleep(1000);
		cout << "2" << endl;
		Sleep(1000);
		cout << "1" << endl;
		Sleep(1000);
		m_eType = EV_ULTIMATE;
		m_strDigName = m_evInfo[2].strName;
		m_strEvName = "궁극체";
		m_tInfo.iHpMax += m_evInfo[2].iHp;
		m_tInfo.iHp = m_tInfo.iHpMax;
		m_tInfo.iDsMax = m_evInfo[2].iDs;
		m_tInfo.iDs = m_tInfo.iDsMax;
		m_tInfo.iAttackMax += m_evInfo[2].iAttack;
		m_tInfo.iAttackMin += m_evInfo[2].iAttack;
		m_tInfo.iArmorMax += m_evInfo[2].iArmor;
		m_tInfo.iArmorMin += m_evInfo[2].iArmor;
		UpdateSkill();
	}
	else
		cout << "진화 할 수 없습니다..." << endl; system("pause"); return;
}

void CDigimon::EV_Super()
{
	if (m_eType == EV_SUPERULTIMATE)
	{
		cout << "진화 할 수 없습니다..." << endl; system("pause"); return;
	}
	else
	{
		system("cls");
		cout << m_strDigName << "이 " << m_evInfo[3].strName << "으로 진화합니다..." << endl;
		cout << "3" << endl;
		Sleep(1000);
		cout << "2" << endl;
		Sleep(1000);
		cout << "1" << endl;
		Sleep(1000);
		m_eType = EV_SUPERULTIMATE;
		m_strDigName = m_evInfo[3].strName;
		m_strEvName = "초궁극체";
		m_tInfo.iHpMax += m_evInfo[3].iHp;
		m_tInfo.iHp = m_tInfo.iHpMax;
		m_tInfo.iDsMax = m_evInfo[3].iDs;
		m_tInfo.iDs = m_tInfo.iDsMax;
		m_tInfo.iAttackMax += m_evInfo[3].iAttack;
		m_tInfo.iAttackMin += m_evInfo[3].iAttack;
		m_tInfo.iArmorMax += m_evInfo[3].iArmor;
		m_tInfo.iArmorMin += m_evInfo[3].iArmor;
		UpdateSkill();
	}
}

void CDigimon::UpdateSkill()
{
	switch (m_eType)
	{
	case EV_GROW:
		m_useSkillVec.clear();
		m_useSkillVec.push_back(m_skillVec[0]);
		m_useSkillVec.push_back(m_skillVec[1]);
		break;
	case EV_MATURITY:
		m_useSkillVec.clear();
		m_useSkillVec.push_back(m_skillVec[2]);
		m_useSkillVec.push_back(m_skillVec[3]);
		break;
	case EV_INTEGER:
		m_useSkillVec.clear();
		m_useSkillVec.push_back(m_skillVec[4]);
		m_useSkillVec.push_back(m_skillVec[5]);
		break;
	case EV_ULTIMATE:
		m_useSkillVec.clear();
		m_useSkillVec.push_back(m_skillVec[6]);
		m_useSkillVec.push_back(m_skillVec[7]);
		break;
	case EV_SUPERULTIMATE:
		m_useSkillVec.clear();
		m_useSkillVec.push_back(m_skillVec[8]);
		m_useSkillVec.push_back(m_skillVec[9]);
		break;
	}
}

void CDigimon::UpdateEnemySkill()
{
	m_useSkillVec.push_back(m_skillVec[0]);
	m_useSkillVec.push_back(m_skillVec[1]);
}





bool CDigimon::Init()
{
	return true;
}

void CDigimon::Render()
{
	cout << "[디지몬 정보]" << endl;
	cout << "이름 : " << GetDigName() << "\t진화 단계 : " << m_strEvName << endl;
	cout << "체력 : " << m_tInfo.iHp << "\tDS : " << m_tInfo.iDs << endl;
	cout << "레벨 : " << m_tInfo.iLevel << "\t경험치 : " << m_tInfo.iExp << endl;
	cout << "공격력 : " << m_tInfo.iAttackMin << " ~ " << m_tInfo.iAttackMax << endl;
	cout << "방어력 : " << m_tInfo.iArmorMin << " ~ " << m_tInfo.iArmorMax << endl;
	cout << "스킬 1번 : " << m_useSkillVec[0]->GetSkillName() << "\t스킬 데미지 : " << m_useSkillVec[0]->GetSkillDamage() << endl;
	cout << "스킬 2번 : " << m_useSkillVec[1]->GetSkillName() << "\t스킬 데미지 : " << m_useSkillVec[1]->GetSkillDamage() << endl;
}


CDigimon* CDigimon::Clone()
{
	return new CDigimon(*this);
}
