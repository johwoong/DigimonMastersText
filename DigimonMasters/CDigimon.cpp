#include "pch.h"
#include "CDigimon.h"
#include "Skill.h"
#include "CPlayer.h"
#include "ObjectManager.h"
#include "FileStream.h"

CDigimon::CDigimon() : m_strDigName(""), m_aType(AT_NONE), m_eType(EV_GROW), m_strEvName("성장기"), iDigSize(3), isDie(0)
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
	iDigSize = digimon.iDigSize;
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
			cout << "테이머의 DS가 부족합니다...." << endl;
			system("pause");
			return;
		}
		SetOriginInfo();
		system("cls");
		cout << m_strDigName << "이 " << m_evInfo[0].strName << "으로 진화합니다..." << endl;
		cout << "3" << endl;
		Sleep(1000);
		cout << "2" << endl;
		Sleep(1000);
		cout << "1" << endl;
		Sleep(1000);
		pPlayer->MinusDs(100);
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
		SetOriginInfo();
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
		SetOriginInfo();
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
		SetOriginInfo();
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

void CDigimon::MaxHp()
{
	m_tInfo.iHp = m_tInfo.iHpMax;
}

void CDigimon::MinusDs(int value)
{
	m_tInfo.iDs -= value;
}

void CDigimon::Unevolve(int number)
{
	if (m_eType == EV_GROW)
	{
		cout << "이미 진화가 해제된 상태입니다." << endl;
		system("pause");
		return;
	}
	system("cls");
	cout << "진화가 해제되었습니다." << endl;
	m_eType = EV_GROW;
	m_strDigName = m_originInfo.strName;
	m_strEvName = "성장기";
	m_tInfo.iHpMax = m_originInfo.iHpMax;
	m_tInfo.iHp = m_originInfo.iHp;
	m_tInfo.iDsMax = m_originInfo.iDsMax;
	m_tInfo.iDs = m_originInfo.iDs;
	m_tInfo.iAttackMax = m_originInfo.iAttackMax;
	m_tInfo.iAttackMin = m_originInfo.iAttackMin;
	m_tInfo.iArmorMax = m_originInfo.iArmorMax;
	m_tInfo.iArmorMin = m_originInfo.iArmorMin;
	UpdateSkill();
	if (number == 0)
	{
		system("pause");
	}
}



bool CDigimon::Init()
{
	return true;
}

void CDigimon::Render()
{
	SetConsoleColor(14);
	cout << "[디지몬 정보]" << endl;
	cout << "크기 : " << GetDigionSize() << "성" << endl;
	cout << "이름 : " << GetDigName() << "\t진화 단계 : " << m_strEvName << endl;
	cout << "체력 : " << m_tInfo.iHp << "\tDS : " << m_tInfo.iDs << endl;
	cout << "레벨 : " << m_tInfo.iLevel << "\t경험치 : " << m_tInfo.iExp << endl;
	cout << "공격력 : " << m_tInfo.iAttackMin << " ~ " << m_tInfo.iAttackMax << endl;
	cout << "방어력 : " << m_tInfo.iArmorMin << " ~ " << m_tInfo.iArmorMax << endl;
	cout << "스킬 1번 : " << m_useSkillVec[0]->GetSkillName() << "\t스킬 데미지 : " << m_useSkillVec[0]->GetSkillDamage() << endl;
	cout << "스킬 2번 : " << m_useSkillVec[1]->GetSkillName() << "\t스킬 데미지 : " << m_useSkillVec[1]->GetSkillDamage() << endl << endl;
	ResetConsoleColor();
}


CDigimon* CDigimon::Clone()
{
	return new CDigimon(*this);
}

void CDigimon::Save(FileStream* pFile)
{
	CCharacter::Save(pFile);
	int skillCount = m_skillVec.size();
	pFile->Write(&skillCount, sizeof(int)); // 스킬 개수 저장

	for (int i = 0; i < skillCount; ++i)
	{
		m_skillVec[i]->Save(pFile);
	}

	int evCount = m_evInfo.size();
	pFile->Write(&evCount, sizeof(4));

	for (int i = 0; i < evCount; ++i)
	{
		pFile->Write(&m_evInfo[i], sizeof(m_evInfo));
	}

	pFile->Write(&m_originInfo, sizeof(m_originInfo));

	// 진화이름 저장
	int iLength = m_strEvName.length();
	pFile->Write(&iLength, 4);
	pFile->Write((void*)m_strEvName.c_str(), iLength);

	// 디지몬 이름 저장
	iLength = m_strDigName.length();
	pFile->Write(&iLength, 4);
	pFile->Write((void*)m_strDigName.c_str(), iLength);


	pFile->Write(&m_aType, sizeof(m_aType));
	pFile->Write(&m_eType, sizeof(m_eType));

	skillCount = m_useSkillVec.size(); // 사용 스킬 개수 저장
	pFile->Write(&skillCount, sizeof(int));

	for (int i = 0; i < skillCount; ++i)
	{
		m_useSkillVec[i]->Save(pFile);
	}

	pFile->Write(&isDie, sizeof(isDie));
	pFile->Write(&iDigSize, sizeof(iDigSize));
}

void CDigimon::Load(FileStream* pFile)
{
	CCharacter::Load(pFile);
	// 1. 스킬
	int skillCount = 0;
	pFile->Read(&skillCount, sizeof(int));
	for (int i = 0; i < skillCount; ++i)
	{
		Skill* pSkill = new Skill();
		pSkill->Load(pFile);
		m_skillVec.push_back(pSkill);
	}

	// 2. 진화 정보 수 + 리스트
	int evCount = 0;
	pFile->Read(&evCount, sizeof(int));
	m_evInfo.resize(evCount); 
	for (int i = 0; i < evCount; ++i)
	{
		pFile->Read(&m_evInfo[i], sizeof(m_evInfo)); 
	}

	// 3. 오리진 정보
	pFile->Read(&m_originInfo, sizeof(m_originInfo));

	// 4. 진화 이름
	int iLength = 0;
	pFile->Read(&iLength, 4);
	std::string temp;
	temp.resize(iLength);
	pFile->Read(&temp[0], iLength);
	m_strEvName = temp;

	// 5. 디지몬 이름
	pFile->Read(&iLength, 4);
	temp.resize(iLength);
	pFile->Read(&temp[0], iLength);
	m_strDigName = temp;

	// 6. 타입 정보
	pFile->Read(&m_aType, sizeof(m_aType));
	pFile->Read(&m_eType, sizeof(m_eType));

	// 7. 사용 스킬
	pFile->Read(&skillCount, sizeof(int));
	for (int i = 0; i < skillCount; ++i)
	{
		Skill* pSkill = new Skill();
		pSkill->Load(pFile);
		m_useSkillVec.push_back(pSkill);
	}

	// 8. 상태 정보
	pFile->Read(&isDie, sizeof(isDie));
	pFile->Read(&iDigSize, sizeof(iDigSize));
}

