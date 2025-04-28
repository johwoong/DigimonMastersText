#include "pch.h"
#include "CDigimon.h"
#include "Skill.h"
#include "CPlayer.h"
#include "ObjectManager.h"

CDigimon::CDigimon() : m_strDigName(""), m_aType(AT_NONE), m_eType(EV_GROW), m_strEvName("�����"), isDie(0)
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



void CDigimon::SetOriginInfo()
{
	m_originInfo.strName = m_strDigName;
	m_originInfo.iAttackMax = m_tInfo.iAttackMax;
	m_originInfo.iAttackMin = m_tInfo.iAttackMin;
	m_originInfo.iArmorMax = m_tInfo.iArmorMax;
	m_originInfo.iArmorMin = m_tInfo.iArmorMin;
	m_originInfo.iDsMax = m_tInfo.iDsMax;
	m_originInfo.iDs = m_tInfo.iDs;
	m_originInfo.iHpMax = m_tInfo.iHpMax;
	m_originInfo.iHp = m_tInfo.iHp;
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
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(ObjectManager)->FindObject("Player");
	if (m_eType == EV_GROW)
	{
		if (pPlayer->GetCharacterInfo().iDs < 100)
		{
			pPlayer->Render();
			cout << "���̸��� DS�� �����մϴ�...." << endl;
			system("pause");
			return;
		}
		SetOriginInfo();
		system("cls");
		cout << m_strDigName << "�� " << m_evInfo[0].strName << "���� ��ȭ�մϴ�..." << endl;
		cout << "3" << endl;
		Sleep(1000);
		cout << "2" << endl;
		Sleep(1000);
		cout << "1" << endl;
		Sleep(1000);
		pPlayer->MinusDs(100);
		m_eType = EV_MATURITY;
		m_strDigName = m_evInfo[0].strName;
		m_strEvName = "������";
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
		cout << "��ȭ �� �� �����ϴ�..." << endl; system("pause"); return;
}

void CDigimon::Ev_Integer()
{
	if (m_eType == EV_GROW || m_eType == EV_MATURITY)
	{
		SetOriginInfo();
		system("cls");
		cout << m_strDigName << "�� " << m_evInfo[1].strName << "  ���� ��ȭ�մϴ�..." << endl;
		cout << "3" << endl;
		Sleep(1000);
		cout << "2" << endl;
		Sleep(1000);
		cout << "1" << endl;
		Sleep(1000);
		m_eType = EV_INTEGER;
		m_strDigName = m_evInfo[1].strName;
		m_strEvName = "����ü";
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
		cout << "��ȭ �� �� �����ϴ�..." << endl; system("pause"); return;
}

void CDigimon::Ev_Ultimat()
{
	if (m_eType == EV_GROW || m_eType == EV_MATURITY || m_eType == EV_INTEGER)
	{
		SetOriginInfo();
		system("cls");
		cout << m_strDigName << "�� " << m_evInfo[2].strName << "  ���� ��ȭ�մϴ�..." << endl;
		cout << "3" << endl;
		Sleep(1000);
		cout << "2" << endl;
		Sleep(1000);
		cout << "1" << endl;
		Sleep(1000);
		m_eType = EV_ULTIMATE;
		m_strDigName = m_evInfo[2].strName;
		m_strEvName = "�ñ�ü";
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
		cout << "��ȭ �� �� �����ϴ�..." << endl; system("pause"); return;
}

void CDigimon::EV_Super()
{
	if (m_eType == EV_SUPERULTIMATE)
	{
		cout << "��ȭ �� �� �����ϴ�..." << endl; system("pause"); return;
	}
	else
	{
		SetOriginInfo();
		system("cls");
		cout << m_strDigName << "�� " << m_evInfo[3].strName << "���� ��ȭ�մϴ�..." << endl;
		cout << "3" << endl;
		Sleep(1000);
		cout << "2" << endl;
		Sleep(1000);
		cout << "1" << endl;
		Sleep(1000);
		m_eType = EV_SUPERULTIMATE;
		m_strDigName = m_evInfo[3].strName;
		m_strEvName = "�ʱñ�ü";
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

void CDigimon::MaxHp()
{
	m_tInfo.iHp = m_tInfo.iHpMax;
}

void CDigimon::MinusDs(int value)
{
	m_tInfo.iDs -= value;
}

void CDigimon::Unevolve()
{
	system("cls");
	cout << "��ȭ�� �����Ǿ����ϴ�." << endl;
	m_eType = EV_GROW;
	m_strDigName = m_originInfo.strName;
	m_strEvName = "�����";
	m_tInfo.iHpMax = m_originInfo.iHpMax;
	m_tInfo.iHp = m_originInfo.iHp;
	m_tInfo.iDsMax = m_originInfo.iDsMax;
	m_tInfo.iDs = m_originInfo.iDs;
	m_tInfo.iAttackMax = m_originInfo.iAttackMax;
	m_tInfo.iAttackMin = m_originInfo.iAttackMin;
	m_tInfo.iArmorMax = m_originInfo.iArmorMax;
	m_tInfo.iArmorMin = m_originInfo.iArmorMin;
	UpdateSkill();
	system("pause");
}



bool CDigimon::Init()
{
	return true;
}

void CDigimon::Render()
{
	cout << "[������ ����]" << endl;
	cout << "�̸� : " << GetDigName() << "\t��ȭ �ܰ� : " << m_strEvName << endl;
	cout << "ü�� : " << m_tInfo.iHp << "\tDS : " << m_tInfo.iDs << endl;
	cout << "���� : " << m_tInfo.iLevel << "\t����ġ : " << m_tInfo.iExp << endl;
	cout << "���ݷ� : " << m_tInfo.iAttackMin << " ~ " << m_tInfo.iAttackMax << endl;
	cout << "���� : " << m_tInfo.iArmorMin << " ~ " << m_tInfo.iArmorMax << endl;
	cout << "��ų 1�� : " << m_useSkillVec[0]->GetSkillName() << "\t��ų ������ : " << m_useSkillVec[0]->GetSkillDamage() << endl;
	cout << "��ų 2�� : " << m_useSkillVec[1]->GetSkillName() << "\t��ų ������ : " << m_useSkillVec[1]->GetSkillDamage() << endl;
}


CDigimon* CDigimon::Clone()
{
	return new CDigimon(*this);
}
