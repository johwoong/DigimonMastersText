#include "pch.h"
#include "Item.h"
#include "FileStream.h"

Item::Item()
{
}

Item::Item(const Item& item)
{
	m_tInfo = item.m_tInfo;
}

Item::~Item()
{

}

bool Item::Init()
{
	return true;
}

void Item::Render()
{
}

Item* Item::Clone()
{
	return new Item(*this);
}

void Item::SetItemInfo(ITEM_TYPE itemType, string strName, int iPrice, int iWeight, string strDesc)
{
	m_tInfo.eType = itemType;
	m_tInfo.strName = strName;
	m_tInfo.iPrice = iPrice;
	m_tInfo.iWeight = iWeight;
	m_tInfo.strDesc = strDesc;
}

void Item::Save(FileStream* pFile)
{
	CObj::Save(pFile);
	pFile->Write(&m_tInfo, sizeof(m_tInfo));
}

void Item::Load(FileStream* pFile)
{
	CObj::Load(pFile);
	pFile->Read(&m_tInfo, sizeof(m_tInfo));
}


