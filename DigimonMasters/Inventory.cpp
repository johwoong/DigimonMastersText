#include "pch.h"
#include "Inventory.h"
#include "Item.h"
#include "ObjectManager.h"
#include "CPlayer.h"
#include "ItemEquip.h"
#include "ItemEgg.h"
#include "ItemGeneric.h"
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
	cout << "������ ���� : " << m_Item_vec.size() << "\t�뷮 : " << iWeight << endl;
	for (int i = 0; i < m_Item_vec.size(); ++i)
	{
		cout << endl << endl;
		cout << "[������ ��ȣ : " << i + 1 << "]" << endl;
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
		cout << "1. �� ����" << endl;
		cout << "2. �� ����" << endl;
		cout << "3. ������ ���" << endl;
		cout << "4. ������ ����" << endl;
		cout << "5. �ڷΰ���" << endl;
		cout << "�ɼ��� �������ּ��� : ";
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
		cout << "����� �������� �������� �ʽ��ϴ�...." << endl;
		system("pause");
		return;
	}
}

void Inventory::ThrowItem()
{
	if (m_Item_vec.size() == 0)
	{
		cout << "�κ��丮�� �������� �������� �ʽ��ϴ�...." << endl;
		system("pause");
		return;
	} 
	while (true)
	{
		cout << "���� �������� �������ּ��� : ";
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
			cout << "�������� �������� �ʽ��ϴ�!!" << endl;
			system("pause");
			return;
		}
		cout << "������ �������� �������ּ��� : ";
		int input = Input<int>();
		if (input < 0 || input > m_Item_vec.size())
			continue;
		ItemEquip* item = (ItemEquip*)m_Item_vec[input - 1];
		if (item->GetItemRegion() == HEAD || item->GetItemRegion() == SHIRT || item->GetItemRegion() == GLOVE || item->GetItemRegion() == PANT || item->GetItemRegion() == SHOES)
		{
			CPlayer* pPlayer = (CPlayer*)GET_SINGLE(ObjectManager)->FindObject("Player");
			cout << item->GetItemInfo().strName << "�� " << item->GetItemRegionName() << "�� �����߽��ϴ�..." << endl;
 			pPlayer->Equip(item);
			m_Item_vec.erase(m_Item_vec.begin() + (input - 1));
			system("pause");
			return;
		}
		else
		{
			cout << "������ �� ���� �������Դϴ�...." << endl;
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
			cout << "�������� �������� �ʽ��ϴ�!!" << endl;
			system("pause");
			return;
		}
		system("cls");
		pPlayer->PrintEquip();
		cout << "��� ������ ��� �����Ͻðڽ��ϱ�?" << endl;
		cout << "1. �Ӹ�" << endl;
		cout << "2. ����" << endl;
		cout << "3. ����" << endl;
		cout << "4. �尩" << endl;
		cout << "5. �Ź�" << endl;
		cout << "6. �ڷ� ����" << endl;
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
		cout << "****************[�κ��丮]****************" << endl;
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
			// ������ ���
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
