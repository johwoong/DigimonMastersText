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
	cout << "아이템 개수 : " << m_Item_vec.size() << "\t용량 : " << iWeight << endl;
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
	cout << "****************[인벤토리]****************" << endl;
	PrintItemList();
	system("pause");
}
