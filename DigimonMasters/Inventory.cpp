#include "pch.h"
#include "Inventory.h"
#include "Item.h"
#include "ObjectManager.h"
#include "CPlayer.h"
#include "ItemEquip.h"

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
		cout << endl << endl;
		cout << "[아이템 번호 : " << i + 1 << "]" << endl;
		m_Item_vec[i]->Render();
	}
}

int Inventory::SelectOption()
{
	while (true)
	{
		cout << "1. 방어구 장착" << endl;
		cout << "2. 아이템 사용" << endl;
		cout << "3. 아이템 삭제" << endl;
		cout << "4. 뒤로가기" << endl;
		cout << "옵션을 선택해주세요 : ";
		int input = Input<int>();
		if (input < 0 || input > 4)
			continue;
		return input;
	}
}

void Inventory::UseItem()
{
	if (m_Item_vec.size() == 0)
	{
		cout << "사용할 아이템이 존재하지 않습니다...." << endl;
		system("pause");
		return;
	}
}

void Inventory::ThrowItem()
{
	if (m_Item_vec.size() == 0)
	{
		cout << "인벤토리에 아이템이 존재하지 않습니다...." << endl;
		system("pause");
		return;
	} 
	while (true)
	{
		cout << "버릴 아이템을 선택해주세요 : ";
		int input = Input<int>();
		if (input < 0 || input > m_Item_vec.size() + 1)
			continue;
		Item* item = m_Item_vec[input - 1];
		m_Item_vec.erase(m_Item_vec.begin() + (input - 1));
		iWeight--;
		return;
	}
}

void Inventory::EquipItem()
{
	while (true)
	{
		cout << "장착할 아이템을 선택해주세요 : ";
		int input = Input<int>();
		if (input < 0 || input > m_Item_vec.size() + 1)
			continue;
		ItemEquip* item = (ItemEquip*)m_Item_vec[input - 1];
		if (item->GetItemRegion() == HEAD || item->GetItemRegion() == SHIRT || item->GetItemRegion() == GLOVE || item->GetItemRegion() == PANT || item->GetItemRegion() == SHOES)
		{
			CPlayer* pPlayer = (CPlayer*)GET_SINGLE(ObjectManager)->FindObject("Player");
			cout << item->GetItemInfo().strName << "을 " << item->GetItemRegionName() << "에 장착했습니다..." << endl;
			pPlayer->Equip(item);
			system("pause");
			return;
		}
		else
			cout << "장착할 수 없는 아이템입니다...." << endl; system("pause");
	}
	
}


bool Inventory::Init()
{
	return true;
}

void Inventory::Update()
{
	while (true)
	{
		system("cls");
		cout << "****************[인벤토리]****************" << endl;
		PrintItemList();
		switch (SelectOption())
		{
		case 1:
			EquipItem();
			break;
		case 2:
			break;
		case 3:
			ThrowItem();
			break;
		case 4:
			return;
		}
	}
}
