#include "pch.h"
#include "Inventory.h"
#include "Item.h"
#include "ObjectManager.h"
#include "CPlayer.h"
#include "ItemEquip.h"
#include "FileStream.h"

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

void Inventory::Save(FileStream& stream)
{
	cout << "[Save] 아이템 수: " << m_Item_vec.size() << ", 무게: " << iWeight << endl;
	int itemCount = m_Item_vec.size();
	stream.Write(&itemCount, sizeof(itemCount));
	for (auto& item : m_Item_vec)
		item->Save(stream);
	stream.Write(&iWeight, sizeof(iWeight));
	system("pause");

}

void Inventory::Load(FileStream& stream)
{
	int itemCount = 0;
	if (!stream.Read(&itemCount, sizeof(itemCount))) {
		cout << "아이템 개수 읽기 실패!" << endl;
		return;
	}
	cout << "[Load] 읽은 아이템 개수: " << itemCount << endl;

	if (itemCount < 0 || itemCount > 1000) {  // 말이 안 되는 값이면 중단
		cout << "비정상적인 아이템 개수. 파일이 손상되었을 수 있음." << endl;
		return;
	}

	m_Item_vec.clear();
	for (int i = 0; i < itemCount; ++i)
	{
		Item* newItem = new Item;
		newItem->Load(stream);
		m_Item_vec.push_back(newItem);
	}
	if (!stream.Read(&iWeight, sizeof(iWeight))) {
		cout << "무게 읽기 실패!" << endl;
	}
	cout << "[Load] 아이템 무게: " << iWeight << endl;
	system("pause");
}
