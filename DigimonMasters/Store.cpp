#include "pch.h"
#include "Store.h"
#include "Item.h"
#include "ObjectManager.h"
#include "ItemEquip.h"
#include "ItemEgg.h"
#include "ItemGeneric.h"
#include "Inventory.h"
Store::Store()
{

}

Store::~Store()
{
	Safe_Delete_VecList(m_vecItemList);
}

void Store::ShowList()
{
	while (true)
	{
		system("cls");
		cout << "******************* 상점 목록 *******************" << endl;
		for (int i = 0; i < m_vecItemList.size(); ++i)
		{
			cout << "[" << i + 1 << "] 아이템 " << endl;
			m_vecItemList[i]->Render();
		}
		cout << "구매하실 아이템의 번호를 입력해주세요(나가기 0번)>>> ";
		int input = Input<int>();
		if (input < 0 || input > m_vecItemList.size() + 1)
			continue;
		if (input == 0)
			return;
		Item* item = m_vecItemList[input - 1]->Clone();
		AddInventoryInItem(item);
	}
}

Item* Store::CreateItem(string pName, ITEM_TYPE eType, int iPrice, int iWeight, string Desc)
{
	Item* pItem = nullptr;
	switch (eType)
	{
	case IT_EQ:
		pItem = new ItemEquip;
		break;
	case IT_EGG:
		pItem = new ItemEgg;
		break;
	case IT_GENERIC:
		pItem = new ItemGeneric;
	}
	if (!pItem)
	{
		SAFE_DELETE(pItem);
		return nullptr;
	}
	pItem->SetItemInfo(eType, pName, iPrice, iWeight, Desc);
	m_vecItemList.push_back(pItem);
	return pItem;
}

void Store::AddInventoryInItem(Item* item)
{
	if (!GET_SINGLE(Inventory)->AddInventory(item))
	{
		cout << "인벤토리가 꽉 찼습니다!!" << endl;
	}
	else
		cout << item->GetItemInfo().strName << "을 구매하였습니다!!" << endl;
	system("pause");
}


