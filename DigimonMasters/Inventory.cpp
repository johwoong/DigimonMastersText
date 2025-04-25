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
	cout << "������ ���� : " << m_Item_vec.size() << "\t�뷮 : " << iWeight << endl;
	for (int i = 0; i < m_Item_vec.size(); ++i)
	{
		cout << endl << endl;
		cout << "[������ ��ȣ : " << i + 1 << "]" << endl;
		m_Item_vec[i]->Render();
	}
}

int Inventory::SelectOption()
{
	while (true)
	{
		cout << "1. �� ����" << endl;
		cout << "2. ������ ���" << endl;
		cout << "3. ������ ����" << endl;
		cout << "4. �ڷΰ���" << endl;
		cout << "�ɼ��� �������ּ��� : ";
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
		iWeight--;
		return;
	}
}

void Inventory::EquipItem()
{
	while (true)
	{
		cout << "������ �������� �������ּ��� : ";
		int input = Input<int>();
		if (input < 0 || input > m_Item_vec.size() + 1)
			continue;
		ItemEquip* item = (ItemEquip*)m_Item_vec[input - 1];
		if (item->GetItemRegion() == HEAD || item->GetItemRegion() == SHIRT || item->GetItemRegion() == GLOVE || item->GetItemRegion() == PANT || item->GetItemRegion() == SHOES)
		{
			CPlayer* pPlayer = (CPlayer*)GET_SINGLE(ObjectManager)->FindObject("Player");
			cout << item->GetItemInfo().strName << "�� " << item->GetItemRegionName() << "�� �����߽��ϴ�..." << endl;
			pPlayer->Equip(item);
			system("pause");
			return;
		}
		else
			cout << "������ �� ���� �������Դϴ�...." << endl; system("pause");
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
		cout << "****************[�κ��丮]****************" << endl;
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
