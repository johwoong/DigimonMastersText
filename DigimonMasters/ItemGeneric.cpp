#include "pch.h"
#include "ItemGeneric.h"
#include "FileStream.h"

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
	cout << "������ �̸� : " << m_tInfo.strName << endl;
	cout << "�뷮 : " << m_tInfo.iWeight << "\t���� : " << m_tInfo.strDesc << endl;
	cout << endl << endl;
}

Item* ItemGeneric::Clone()
{
	return new ItemGeneric(*this);
}

void ItemGeneric::Save(FileStream* pFile)
{
	Item::Save(pFile);
	pFile->Write(&item_Kind, sizeof(item_Kind));
}

void ItemGeneric::Load(FileStream* pFile)
{
	Item::Load(pFile);
	pFile->Read(&item_Kind, sizeof(item_Kind));
}
