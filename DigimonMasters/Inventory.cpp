#include "pch.h"
#include "Inventory.h"
#include "Item.h"

DEFINITION_SINGLE(Inventory)

Inventory::Inventory() : iWeight(10)
{

}

Inventory::~Inventory()
{
	Safe_Delete_VecList(m_Item_vec);
}

bool Inventory::AddInventory(Item* item)
{
	if (m_Item_vec.size() >= iWeight)
		return false;
	m_Item_vec.push_back(item);
	return true;
}

void Inventory::PrintItemList()
{
	cout << "������ ���� : " << m_Item_vec.size() << "\t�뷮 : " << iWeight << endl;
	for (int i = 0; i < m_Item_vec.size(); ++i)
	{
		m_Item_vec[i]->Render();
	}
}

bool Inventory::Init()
{
	return true;
}

void Inventory::Update()
{
	system("cls");
	cout << "****************[�κ��丮]****************" << endl;
	PrintItemList();
	system("pause");
}
