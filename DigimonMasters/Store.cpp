#include "pch.h"
#include "Store.h"
#include "Item.h"
#include "ObjectManager.h"
#include "ItemEquip.h"
#include "ItemEgg.h"
#include "ItemGeneric.h"
#include "Inventory.h"
#include "CPlayer.h"
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
		cout << "******************* ���� ��� *******************" << endl;
		cout << "���� ��� : " << CPlayer::GetGold() << "��" << endl;
		for (int i = 0; i < m_vecItemList.size(); ++i)
		{
			cout << "[" << i + 1 << "] ������ " << endl;
			m_vecItemList[i]->Render();
		}
		cout << "�����Ͻ� �������� ��ȣ�� �Է����ּ���(������ 0��)>>> ";
		int input = Input<int>();
		if (input < 0 || input > m_vecItemList.size())
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
		if (CPlayer::GetGold() < item->GetItemInfo().iPrice)
			cout << "�������� �����մϴ�." << endl;
		else
			cout << "�κ��丮�� �� á���ϴ�!!" << endl;
	}
	else
	{
		CPlayer::MinusGold(item->GetItemInfo().iPrice);
		cout << item->GetItemInfo().strName << "�� " << item->GetItemInfo().iPrice << "���� �����Ͽ����ϴ�!!" << endl;
	}
	system("pause");
}


