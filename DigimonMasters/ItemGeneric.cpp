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
	cout << "[������ ����] " << endl;
	cout << "��� �̸� : " << m_tInfo.strName << endl;
	cout << "�뷮 : " << m_tInfo.iWeight << "\t���� : " << m_tInfo.strDesc << endl;
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
