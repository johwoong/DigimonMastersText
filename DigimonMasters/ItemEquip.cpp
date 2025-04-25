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
	cout << "[아이템 정보] " << endl;
	cout << "장비 이름 : " << m_tInfo.strName << "\t부위 : " << GetItemRegionName() << endl;
	cout << "방어력 : " << iArmorMin << " ~ " << iArmorMax << "\tDS증가량 : " << iDsMin << " ~ " << iDsMax << endl;
	cout << "이동속도 증가 : " << iSpeed << "\t가격 : " << m_tInfo.iPrice << endl;
	cout << "용량 : " << m_tInfo.iWeight << "\t설명 : " << m_tInfo.strDesc << endl;
	cout << endl << endl;
}

Item* ItemEquip::Clone()
{
	return new ItemEquip(*this);
}
