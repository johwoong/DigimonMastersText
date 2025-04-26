#include "pch.h"
#include "ItemEquip.h"

ItemEquip::ItemEquip() : m_regionName("")
{
	memset(&m_itemStat, 0, sizeof(m_itemStat));
}

ItemEquip::ItemEquip(const ItemEquip& item) : Item(item)
{
	m_itemRegionType = item.m_itemRegionType;
	m_itemStat = item.m_itemStat;
	m_regionName = item.m_regionName;
}

ItemEquip::~ItemEquip()
{

}

void ItemEquip::SetItemRegion(ITEM_REGION eType)
{
	m_itemRegionType = eType;
	switch (m_itemRegionType)
	{
	case HEAD:
		m_regionName = "머리";
		break;
	case SHIRT:
		m_regionName = "상의";
		break;
	case GLOVE:
		m_regionName = "장갑";
		break;
	case PANT:
		m_regionName = "하의";
		break;
	case SHOES:
		m_regionName = "신발";
		break;
	}
}

void ItemEquip::SetItemStatInfo(int iAttack, int iArmor, int iDs, int iSpeed, int iSkillDamage)
{
	m_itemStat.iAttack = iAttack;
	m_itemStat.iArmor = iArmor;
	m_itemStat.iDs = iDs;
	m_itemStat.iSpeed = iSpeed;
	m_itemStat.iSkillDamage = iSkillDamage;
}


bool ItemEquip::Init()
{
	return true;
}

void ItemEquip::Render()
{
	cout << "[아이템 정보] " << endl;
	cout << "장비 이름 : " << m_tInfo.strName << "\t부위 : " << GetItemRegionName() << endl;
	cout << "스킬 데미지 증가량 : "  << m_itemStat.iSkillDamage << endl;
	cout << "방어력 증가량 : " << m_itemStat.iArmor << "\tDS증가량 : " << m_itemStat.iDs << endl;
	cout << "이동속도 증가 : " << m_itemStat.iSpeed << "\t가격 : " << m_tInfo.iPrice << endl;
	cout << "용량 : " << m_tInfo.iWeight << "\t설명 : " << m_tInfo.strDesc << endl;
	cout << endl << endl;
}

Item* ItemEquip::Clone()
{
	return new ItemEquip(*this);
}
