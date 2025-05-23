#include "pch.h"
#include "Inventory.h"
#include "Item.h"
#include "ObjectManager.h"
#include "CPlayer.h"
#include "ItemEquip.h"
#include "ItemEgg.h"
#include "ItemGeneric.h"
#include "FileStream.h"
#include "CPlayer.h"

DEFINITION_SINGLE(Inventory)

Inventory::Inventory() : iWeight(0), iMaxWeight(30)
{

}

Inventory::~Inventory()
{
	Safe_Delete_VecList(m_Item_vec);
}

bool Inventory::AddInventory(Item* item)
{
	if (m_Item_vec.size() >= iMaxWeight || CPlayer::GetGold() < item->GetItemInfo().iPrice)
		return false;
	m_Item_vec.push_back(item);
	iWeight++;
	return true;
}

void Inventory::PrintItemList()
{
	cout << "아이템 개수 : " << m_Item_vec.size() << "\t용량 : " << iWeight << "/"  << iMaxWeight << endl;
	for (int i = 0; i < m_Item_vec.size(); ++i)
	{
		cout << endl << endl;
		cout << "[아이템 번호 : " << i + 1 << "]" << endl;
		if (m_Item_vec[i] == nullptr)
		{
			return;
		}
		else
			m_Item_vec[i]->Render();
	}
}

int Inventory::SelectOption()
{
	while (true)
	{
		cout << "현재 골드 : " << CPlayer::GetGold() << "원" << endl;
		cout << "1. 방어구 장착" << endl;
		cout << "2. 방어구 해제" << endl;
		cout << "3. 아이템 사용" << endl;
		cout << "4. 아이템 삭제" << endl;
		cout << "5. 뒤로가기" << endl;
		cout << "옵션을 선택해주세요 : ";
		int input = Input<int>();
		if (input < 0 || input > 5)
			return 0;
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

void Inventory::DeleteItem(Item* item)
{
	for (auto iter = m_Item_vec.begin(); iter != m_Item_vec.end(); ++iter)
	{
		if (*iter == item)
		{
			m_Item_vec.erase(iter);
			iWeight--;
			break;
		}
	}
}

void Inventory::EquipItem()
{
	while (true)
	{
		if (m_Item_vec.size() == 0)
		{
			cout << "아이템이 존재하지 않습니다!!" << endl;
			system("pause");
			return;
		}
		cout << "장착할 아이템을 선택해주세요 : ";
		int input = Input<int>();
		if (input < 0 || input > m_Item_vec.size())
			continue;
		ItemEquip* item = (ItemEquip*)m_Item_vec[input - 1];
		if (item->GetItemRegion() == HEAD || item->GetItemRegion() == SHIRT || item->GetItemRegion() == GLOVE || item->GetItemRegion() == PANT || item->GetItemRegion() == SHOES)
		{
			CPlayer* pPlayer = (CPlayer*)GET_SINGLE(ObjectManager)->FindObject("Player");
			cout << item->GetItemInfo().strName << "을 " << item->GetItemRegionName() << "에 장착했습니다..." << endl;
 			pPlayer->Equip(item);
			m_Item_vec.erase(m_Item_vec.begin() + (input - 1));
			iWeight--;
			system("pause");
			return;
		}
		else
		{
			cout << "장착할 수 없는 아이템입니다...." << endl;
			system("pause");
			return;
		}
	}
	
}

void Inventory::UnEquipItem()
{
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(ObjectManager)->FindObject("Player");
	while (true)
	{
		if (m_Item_vec.size() == 0)
		{
			cout << "아이템이 존재하지 않습니다!!" << endl;
			system("pause");
			return;
		}
		system("cls");
		pPlayer->PrintEquip();
		cout << "어느 부위의 장비를 해제하시겠습니까?" << endl;
		cout << "1. 머리" << endl;
		cout << "2. 상의" << endl;
		cout << "3. 하의" << endl;
		cout << "4. 장갑" << endl;
		cout << "5. 신발" << endl;
		cout << "6. 뒤로 가기" << endl;
		cout << ">>> ";
		int input = Input<int>();
		if (input < 0 || input > 6)
			continue;
		switch (input)
		{
		case 1:
			pPlayer->UnEquip(HEAD);
			break;
		case 2:
			pPlayer->UnEquip(SHIRT);
			break;
		case 3:
			pPlayer->UnEquip(PANT);
			break;
		case 4:
			pPlayer->UnEquip(GLOVE);
			break;
		case 5:
			pPlayer->UnEquip(SHOES);
			break;
		case 6:
			return;
		}
		iWeight++;
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
		SetConsoleColor(9);
		system("cls");
		cout << "****************[인벤토리]****************" << endl;
		PrintItemList();
		switch (SelectOption())
		{
		case 1:
			EquipItem();
			break;
		case 2:
			UnEquipItem();
			break;
		case 3:
			// 아이템 사용
			break;
		case 4:
			ThrowItem();
			break;
		case 5:
			return;
		}
		ResetConsoleColor();
	}
}

void Inventory::Save(FileStream* pFile)
{
	int itemCount = m_Item_vec.size();
	pFile->Write(&itemCount, sizeof(int));

	for (auto it : m_Item_vec)
	{
		ITEM_CLASS_TYPE eType = ICT_BASE;

		if (dynamic_cast<ItemEgg*>(it))      eType = ICT_EGG;
		else if (dynamic_cast<ItemEquip*>(it)) eType = ICT_EQUIP;
		else if (dynamic_cast<ItemGeneric*>(it)) eType = ICT_GENERIC;

		pFile->Write(&eType, sizeof(int));
		it->Save(pFile);
	}
}

void Inventory::Load(FileStream* pFile)
{
	int itemCount = 0;
	pFile->Read(&itemCount, sizeof(int));
	for (int i = 0; i < itemCount; ++i)
	{
		int type = 0;
		pFile->Read(&type, sizeof(int));

		Item* pItem = nullptr;

		switch ((ITEM_CLASS_TYPE)type)
		{
		case ICT_EGG:
			pItem = new ItemEgg;
			break;
		case ICT_EQUIP:
			pItem = new ItemEquip;
			break;
		case ICT_GENERIC:
			pItem = new ItemGeneric;
			break;
		}
		pItem->Load(pFile);
		m_Item_vec.push_back(pItem);
	}
}
