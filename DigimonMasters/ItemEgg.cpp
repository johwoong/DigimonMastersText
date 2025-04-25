#include "pch.h"
#include "ItemEgg.h"

ItemEgg::ItemEgg()
{
	
}

ItemEgg::ItemEgg(const ItemEgg& item) : Item(item)
{

}

ItemEgg::~ItemEgg()
{
}

bool ItemEgg::Init()
{
    return true;
}

void ItemEgg::Render()
{
	cout << "[������ ����] " << endl;
	cout << "��� �̸� : " << m_tInfo.strName << endl;
	cout << "�뷮 : " << m_tInfo.iWeight << "\t���� : " << m_tInfo.strDesc << endl;
	cout << endl << endl;
}

Item* ItemEgg::Clone()
{
    return new ItemEgg(*this);
}
