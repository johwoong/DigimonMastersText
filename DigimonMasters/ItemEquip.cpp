#include "pch.h"
#include "ItemEquip.h"

ItemEquip::ItemEquip() : iArmorMin(0), iArmorMax(0), iDsMin(0), iDsMax(0), iSpeed(0), m_regionName("")
{
	
}

ItemEquip::ItemEquip(const ItemEquip& item) : Item(item)
{
	m_itemRegionType = item.m_itemRegionType;
	iArmorMin = item.iArmorMin;
	iArmorMax = item.iArmorMax;
	iDsMin = item.iDsMin;
	iDsMax = item.iDsMax;
	iSpeed = item.iSpeed;
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

void ItemEquip::SetItemStatInfo(int iArmorMin, int iArmorMax, int iDsMin, int iDsMax, int iSpeed)
{
	this->iArmorMin = iArmorMin;
	this->iArmorMax = iArmorMax;
	this->iDsMin = iDsMin;
	this->iDsMax = iDsMax;
	this->iSpeed = iSpeed;
}

bool ItemEquip::Init()
{
	return true;
}

void ItemEquip::Render()
{
	cout << "[������ ����] " << endl;
	cout << "��� �̸� : " << m_tInfo.strName << "\t���� : " << GetItemRegionName() << endl;
	cout << "���� : " << iArmorMin << " ~ " << iArmorMax << "\tDS������ : " << iDsMin << " ~ " << iDsMax << endl;
	cout << "�̵��ӵ� ���� : " << iSpeed << "\t���� : " << m_tInfo.iPrice << endl;
	cout << "�뷮 : " << m_tInfo.iWeight << "\t���� : " << m_tInfo.strDesc << endl;
	cout << endl << endl;
}

Item* ItemEquip::Clone()
{
	return new ItemEquip(*this);
}
