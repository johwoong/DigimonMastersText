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
	cout << "[아이템 정보] " << endl;
	cout << "장비 이름 : " << m_tInfo.strName << endl;
	cout << "용량 : " << m_tInfo.iWeight << "\t설명 : " << m_tInfo.strDesc << endl;
	cout << endl << endl;
}

Item* ItemEgg::Clone()
{
    return new ItemEgg(*this);
}
