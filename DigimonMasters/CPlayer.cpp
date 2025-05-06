#include "pch.h"
#include "CPlayer.h"
#include "Skill.h"
#include "Item.h"
#include "ItemEquip.h"
#include "ItemEquip.h"
#include "Inventory.h"
#include "FileStream.h"

CPlayer::CPlayer() : iTaymer(0), m_strTayName(""), m_tType(T_NONE), p_digimon(nullptr), isDigimon(false), p_skill(nullptr)
{
	memset(&m_equip, 0, sizeof(m_equip));
}

CPlayer::CPlayer(const CPlayer& player) : CCharacter(player)
{
	iTaymer = player.iTaymer;
	m_strTayName = player.m_strTayName;
	m_tType = player.m_tType;
	p_digimon = player.p_digimon;
	isDigimon = player.isDigimon;
	p_skill = player.p_skill;
}

CPlayer::~CPlayer()
{
	SAFE_DELETE(p_digimon);
	SAFE_DELETE(p_skill);
	Safe_Delete_VecList(m_digimonVec);
}

bool CPlayer::Init()
{
	return true;
}

void CPlayer::Render()
{
	cout << "[���̸� ����]" << endl;
	cout << "�̸� : " << GetName() << "\t���̸� : " << GetTaymerName() << endl;
	cout << "ü�� : " << m_tInfo.iHp << "\tDS : " << m_tInfo.iDs << endl;
	cout << "���� : " << m_tInfo.iLevel << "\t����ġ : " << m_tInfo.iExp << endl;
	cout << "��ų : " << GetSkill()->GetSkillName() << "\t�нú� ��ų : " << GetSkill()->GetFasiveSkillName() << endl;
	cout << "�̵��ӵ� :" << m_tInfo.iSpeed;
	cout << endl << endl;
	PrintEquip();
}

CPlayer* CPlayer::Clone()
{
	return nullptr;
}

void CPlayer::Save(FileStream* pFile)
{
	CCharacter::Save(pFile);

	pFile->Write(&iTaymer, 4);

	// ���̸��̸� ����
	int iLength = m_strTayName.length();
	pFile->Write(&iLength, 4);
	pFile->Write((void*)m_strTayName.c_str(), iLength);

	pFile->Write(&m_tType, sizeof(m_tType));


	// ��� ������ ���� ����
	int digimonCount = m_digimonVec.size();
	pFile->Write(&digimonCount, sizeof(int));
	for (int i = 0; i < digimonCount; ++i)
	{
		m_digimonVec[i]->Save(pFile);
	}

	// ���� ������ ���� ����
	bool hasCurrentDigimon = (p_digimon != nullptr);
	pFile->Write(&hasCurrentDigimon, sizeof(bool));
	if (hasCurrentDigimon)
		p_digimon->Save(pFile);



	pFile->Write(&isDigimon, sizeof(isDigimon));


	// ��ų ���� ����
	bool hasSkill = (p_skill != nullptr);
	pFile->Write(&hasSkill, sizeof(bool));
	if (hasSkill)
		p_skill->Save(pFile);




	// ���� ������ ���� ����
	for (int i = 0; i < 5; i++)
	{
		bool hasItem = (m_equip[i] != nullptr);
		pFile->Write(&hasItem, sizeof(bool));  // ������ ���� ���� ����

		if (hasItem)
		{
			m_equip[i]->Save(pFile);  // ���� ������ ����
		}
	}


}

void CPlayer::Load(FileStream* pFile)
{
	CCharacter::Load(pFile);
	pFile->Read(&iTaymer, 4);

	int iLength = 0;
	pFile->Read(&iLength, 4);
	char* pName = new char[iLength + 1];
	memset(pName, 0, iLength + 1);
	pFile->Read(pName, iLength);
	pName[iLength] = 0;
	m_strTayName = pName;   // ���̸� �̸� ��������

	pFile->Read(&m_tType, sizeof(m_tType));

	int digimonCount = 0;
	pFile->Read(&digimonCount, sizeof(int));
	for (int i = 0; i < digimonCount; ++i) // ��� ������ ���� �б�
	{
		CDigimon* pDigimon = new CDigimon();
		pDigimon->Load(pFile);
		m_digimonVec.push_back(pDigimon);
	}



	// ���� ������ ���� �б�
	bool hasCurrentDigimon = false;
	pFile->Read(&hasCurrentDigimon, sizeof(bool));
	if (hasCurrentDigimon) {
		if (p_digimon == nullptr)
			p_digimon = new CDigimon;
		p_digimon->Load(pFile);
	}


	pFile->Read(&isDigimon, sizeof(isDigimon));



	// ���� ��ų ���� �б�
	bool hasSkill = false;
	pFile->Read(&hasSkill, sizeof(bool));

	if (hasSkill) {
		if (p_skill == nullptr)
			p_skill = new Skill;
		p_skill->Load(pFile);
	}




	for (int i = 0; i < 5; ++i)
	{
		bool hasItem = false;
		pFile->Read(&hasItem, sizeof(bool));  // ������ ���� ���� Ȯ��

		if (hasItem)
		{
			m_equip[i] = new ItemEquip();  // ��ü ����
			m_equip[i]->Load(pFile);       // ���� �ҷ�����
		}
		else
		{
			m_equip[i] = nullptr;  // ���� ��� �ʱ�ȭ
		}
	}
}

void CPlayer::SetDigimon(CDigimon* digimon)
{
	p_digimon = new CDigimon;
	p_digimon = digimon->Clone();
}

void CPlayer::SetSkill(Skill* skill)
{
	p_skill = skill;
}

void CPlayer::MinusDs(int value)
{
	m_tInfo.iDs -= value;
}

void CPlayer::SetDigimonVector(CDigimon* digimon)
{
	m_digimonVec.push_back(digimon);
}

void CPlayer::RenderDigimonList()
{
	for (int i = 0; i < m_digimonVec.size(); ++i)
	{
		m_digimonVec[i]->Render();
	}
}

void CPlayer::ChangeDigimon(int index)
{
	if (p_digimon->GetEvoulutionType() != 0)
	{
		p_digimon->Unevolve(1);
	}
	m_digimonVec.push_back(p_digimon);
	p_digimon = m_digimonVec[index];
	m_digimonVec.erase(m_digimonVec.begin() + (index));
}

void CPlayer::PrintHasDigimon()
{
	cout << "���� ������ �ִ� ������ : " << m_digimonVec.size() << endl;
	
	for (int i = 0; i < m_digimonVec.size(); ++i)
	{
		cout << "[" << i + 1 << "]" << " �̸� : " << m_digimonVec[i]->GetDigName() << endl;
	}
}



void CPlayer::PrintEquip()
{
	cout << "[ĳ���� ���]" << endl;
	if (m_equip[HEAD] == nullptr)
		cout << "�Ӹ� : ����" << endl;
	else
	{
		cout << "�Ӹ� : " << m_equip[HEAD]->GetItemInfo().strName << endl;
		PrintItemStat(m_equip[HEAD]);
	}

	if (m_equip[SHIRT] == nullptr)
		cout << "���� : ����" << endl;
	else
	{
		cout << "���� : " << m_equip[SHIRT]->GetItemInfo().strName << endl;
		PrintItemStat(m_equip[SHIRT]);
	}

	if (m_equip[GLOVE] == nullptr)
		cout << "�尩 : ����" << endl;
	else
	{
		cout << "�尩 : " << m_equip[GLOVE]->GetItemInfo().strName << endl;
		PrintItemStat(m_equip[GLOVE]);
	}

	if (m_equip[PANT] == nullptr)
		cout << "���� : ����" << endl;
	else
	{
		cout << "���� : " << m_equip[PANT]->GetItemInfo().strName << endl;
		PrintItemStat(m_equip[PANT]);
	}

	if (m_equip[SHOES] == nullptr)
		cout << "�Ź� : ����" << endl;
	else
	{
		cout << "�Ź� : " << m_equip[SHOES]->GetItemInfo().strName << endl;
		PrintItemStat(m_equip[SHOES]);
	}
}

void CPlayer::Equip(Item* item)
{
	ItemEquip* pItem = (ItemEquip*)item;
	switch (pItem->GetItemRegion())
	{
	case HEAD:
		if (m_equip[HEAD] == nullptr)
		{
			m_equip[HEAD] = pItem;
			ApplyEquip(m_equip[HEAD]);
		}
		else
		{
			GET_SINGLE(Inventory)->AddInventory(m_equip[HEAD]);
			m_equip[HEAD] = pItem;
			ApplyEquip(m_equip[HEAD]);
		}
		break;
	case SHIRT:
		if (m_equip[SHIRT] == nullptr)
		{
			m_equip[SHIRT] = pItem;
			ApplyEquip(m_equip[SHIRT]);
		}
		else
		{
			GET_SINGLE(Inventory)->AddInventory(m_equip[SHIRT]);
			m_equip[SHIRT] = pItem;
			ApplyEquip(m_equip[SHIRT]);
		}
		break;
	case GLOVE:
		if (m_equip[GLOVE] == nullptr)
		{
			m_equip[GLOVE] = pItem;
			ApplyEquip(m_equip[GLOVE]);
		}
		else
		{
			GET_SINGLE(Inventory)->AddInventory(m_equip[GLOVE]);
			m_equip[GLOVE] = pItem;
			ApplyEquip(m_equip[GLOVE]);
		}
		break;
	case PANT:
		if (m_equip[PANT] == nullptr)
		{
			m_equip[PANT] = pItem;
			ApplyEquip(m_equip[PANT]);
		}
		else
		{
			GET_SINGLE(Inventory)->AddInventory(m_equip[PANT]);
			m_equip[PANT] = pItem;
			ApplyEquip(m_equip[PANT]);
		}
		break;
	case SHOES:
		if (m_equip[SHOES] == nullptr)
		{
			m_equip[SHOES] = pItem;
			ApplyEquip(m_equip[SHOES]);
		}
		else
		{
			GET_SINGLE(Inventory)->AddInventory(m_equip[SHOES]);
			m_equip[SHOES] = pItem;
			ApplyEquip(m_equip[SHOES]);
		}
		break;
	}
}

void CPlayer::UnEquip(ITEM_REGION eType)
{
	switch (eType)
	{
	case HEAD:
		GET_SINGLE(Inventory)->AddInventory(m_equip[HEAD]);
		m_equip[HEAD] = nullptr;
		break;
	case SHIRT:
		GET_SINGLE(Inventory)->AddInventory(m_equip[SHIRT]);
		m_equip[SHIRT] = nullptr;
		break;
	case GLOVE:
		GET_SINGLE(Inventory)->AddInventory(m_equip[GLOVE]);
		m_equip[GLOVE] = nullptr;
		break;
	case PANT:
		GET_SINGLE(Inventory)->AddInventory(m_equip[PANT]);
		m_equip[PANT] = nullptr;
		break;
	case SHOES:
		GET_SINGLE(Inventory)->AddInventory(m_equip[SHOES]);
		m_equip[SHOES] = nullptr;
		break;
	}
}

void CPlayer::ApplyEquip(Item* item)
{
	ItemEquip* pItem = (ItemEquip*)item;
	m_tInfo.iSpeed += pItem->GetItemStat().iSpeed;
	m_tInfo.iDs += pItem->GetItemStat().iDs;
	if (p_digimon == nullptr)
	{
		return;
	}
	else
		p_digimon->UpdateStat(pItem->GetItemStat().iAttack, pItem->GetItemStat().iArmor, pItem->GetItemStat().iSkillDamage, pItem->GetItemStat().iSkillDamage);
}


void CPlayer::PrintItemStat(Item* item)
{
	ItemEquip* pItem = (ItemEquip*)item;
	cout << "[������ ����]" << endl;
	cout << "���̸� DS : +" << pItem->GetItemStat().iDs << endl;
	cout << "������ ���ݷ� : +" << pItem->GetItemStat().iAttack << endl;
	cout << "������ ���� : +" << pItem->GetItemStat().iArmor << endl;
	cout << "�̵��ӵ� +" << pItem->GetItemStat().iSpeed << endl;
	cout << "������ ��ų������ +" << pItem->GetItemStat().iSkillDamage << endl;
	cout << endl;
}

