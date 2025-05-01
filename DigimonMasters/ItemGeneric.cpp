#include "pch.h"
#include "ItemGeneric.h"

ItemGeneric::ItemGeneric()
{
}

ItemGeneric::ItemGeneric(const ItemGeneric& item) : Item(item)
{

}

ItemGeneric::~ItemGeneric()
{
}

bool ItemGeneric::Init()
{
	return true;
}

void ItemGeneric::Render()
{
	cout << "[아이템 정보] " << endl;
	cout << "장비 이름 : " << m_tInfo.strName << endl;
	cout << "용량 : " << m_tInfo.iWeight << "\t설명 : " << m_tInfo.strDesc << endl;
	cout << endl << endl;
}

Item* ItemGeneric::Clone()
{
	return new ItemGeneric(*this);
}

void ItemGeneric::Save(FileStream& stream)
{
}

void ItemGeneric::Load(FileStream& stream)
{
}
