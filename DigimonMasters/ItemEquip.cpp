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
		m_regionName = "�Ӹ�";
		break;
	case SHIRT:
		m_regionName = "����";
		break;
	case GLOVE:
		m_regionName = "�尩";
		break;
	case PANT:
		m_regionName = "����";
		break;
	case SHOES:
		m_regionName = "�Ź�";
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
	cout << "[������ ����] " << endl;
	cout << "��� �̸� : " << m_tInfo.strName << "\t���� : " << GetItemRegionName() << endl;
	cout << "��ų ������ ������ : "  << m_itemStat.iSkillDamage << endl;
	cout << "���� ������ : " << m_itemStat.iArmor << "\tDS������ : " << m_itemStat.iDs << endl;
	cout << "�̵��ӵ� ���� : " << m_itemStat.iSpeed << "\t���� : " << m_tInfo.iPrice << endl;
	cout << "�뷮 : " << m_tInfo.iWeight << "\t���� : " << m_tInfo.strDesc << endl;
	cout << endl << endl;
}

Item* ItemEquip::Clone()
{
	return new ItemEquip(*this);
}
