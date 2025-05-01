#include "pch.h"
#include "CPlayer.h"
#include "Skill.h"
#include "Item.h"
#include "ItemEquip.h"
#include "Inventory.h"

CPlayer::CPlayer() : iTaymer(0), m_strTayName(""), m_tType(T_NONE), p_digimon(nullptr), isDigimon(false), p_skill(nullptr)
{
	memset(&m_equip, 0, sizeof(m_equip));
}

CPlayer::CPlayer(const CPlayer& player) : CCharacter(player)
{
	Safe_Delete_VecList(m_digimonVec);
}

CPlayer::~CPlayer()
{
	SAFE_DELETE(p_digimon);
	SAFE_DELETE(p_skill);
}

bool CPlayer::Init()
{
	return true;
}

void CPlayer::Render()
{
	cout << "[테이머 정보]" << endl;
	cout << "이름 : " << GetName() << "\t테이머 : " << GetTaymerName() << endl;
	cout << "체력 : " << m_tInfo.iHp << "\tDS : " << m_tInfo.iDs << endl;
	cout << "레벨 : " << m_tInfo.iLevel << "\t경험치 : " << m_tInfo.iExp << endl;
	cout << "스킬 : " << GetSkill()->GetSkillName() << "\t패시브 스킬 : " << GetSkill()->GetFasiveSkillName() << endl;
	cout << "이동속도 :" << m_tInfo.iSpeed;
	cout << endl << endl;
	PrintEquip();
}

CPlayer* CPlayer::Clone()
{
	return nullptr;
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
	cout << "현재 가지고 있는 디지몬 : " << m_digimonVec.size() << endl;
	
	for (int i = 0; i < m_digimonVec.size(); ++i)
	{
		cout << "[" << i + 1 << "]" << " 이름 : " << m_digimonVec[i]->GetDigName() << endl;
	}
}



void CPlayer::PrintEquip()
{
	cout << "[캐릭터 장비]" << endl;
	if (m_equip[HEAD] == nullptr)
		cout << "머리 : 없음" << endl;
	else
	{
		cout << "머리 : " << m_equip[HEAD]->GetItemInfo().strName << endl;
		PrintItemStat(m_equip[HEAD]);
	}

	if (m_equip[SHIRT] == nullptr)
		cout << "상의 : 없음" << endl;
	else
	{
		cout << "상의 : " << m_equip[SHIRT]->GetItemInfo().strName << endl;
		PrintItemStat(m_equip[SHIRT]);
	}

	if (m_equip[GLOVE] == nullptr)
		cout << "장갑 : 없음" << endl;
	else
	{
		cout << "장갑 : " << m_equip[GLOVE]->GetItemInfo().strName << endl;
		PrintItemStat(m_equip[GLOVE]);
	}

	if (m_equip[PANT] == nullptr)
		cout << "하의 : 없음" << endl;
	else
	{
		cout << "하의 : " << m_equip[PANT]->GetItemInfo().strName << endl;
		PrintItemStat(m_equip[PANT]);
	}

	if (m_equip[SHOES] == nullptr)
		cout << "신발 : 없음" << endl;
	else
	{
		cout << "신발 : " << m_equip[SHOES]->GetItemInfo().strName << endl;
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
	cout << "[아이템 스탯]" << endl;
	cout << "테이머 DS : +" << pItem->GetItemStat().iDs << endl;
	cout << "디지몬 공격력 : +" << pItem->GetItemStat().iAttack << endl;
	cout << "디지몬 방어력 : +" << pItem->GetItemStat().iArmor << endl;
	cout << "이동속도 +" << pItem->GetItemStat().iSpeed << endl;
	cout << "디지몬 스킬데미지 +" << pItem->GetItemStat().iSkillDamage << endl;
	cout << endl;
}
