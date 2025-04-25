#include "pch.h"
#include "StoreEquip.h"
#include "ItemEquip.h"

StoreEquip::StoreEquip()
{	
	ItemEquip* item = (ItemEquip*)CreateItem("������ ������", IT_EQ, 2000, 3, "�ܴ��� ����");
	item->SetItemRegion(SHIRT);
	item->SetItemStatInfo(10, 20, 30, 50, 0);
	
	
	item = (ItemEquip*)CreateItem("�������� �Ź�", IT_EQ, 1500, 3, "��ø�� ����");
	item->SetItemRegion(SHOES);
	item->SetItemStatInfo(5, 10, 15, 20, 50);

	item = (ItemEquip*)CreateItem("��״��� �ԸӸ�", IT_EQ, 1500, 3, "��ø�� ����");
	item->SetItemRegion(HEAD);
	item->SetItemStatInfo(5, 10, 15, 20, 50);

	item = (ItemEquip*)CreateItem("�������� ����", IT_EQ, 1500, 3, "��ø�� ����");
	item->SetItemRegion(PANT);
	item->SetItemStatInfo(5, 10, 15, 20, 50);

	item = (ItemEquip*)CreateItem("�������� �Ź�", IT_EQ, 1500, 3, "��ø�� ����");
	item->SetItemRegion(SHOES);
	item->SetItemStatInfo(5, 10, 15, 20, 50);


	
}

StoreEquip::~StoreEquip()
{

}

void StoreEquip::Update()
{
	while (true)
	{
		switch (OutputMenu())
		{
		case 1:
			ShowList();
			break;
		case 2:
			ShowHeadList();
			break;
		case 3:
			ShowShirtList();
			break;
		case 4:
			ShowGloveList();
			break;
		case 5:
			ShowShoesList();
			break;
		case 6:
			return;
		}
	}
}

int StoreEquip::OutputMenu()
{
	while (true)
	{
		system("cls");
		cout << "********** ���̸� ��� **********" << endl;
		cout << "1. ��ü����" << endl;
		cout << "2. �Ӹ�" << endl;
		cout << "3. ����" << endl;
		cout << "4. �尩" << endl;
		cout << "5. �Ź�" << endl;
		cout << "6. �ڷΰ���" << endl;
		cout << ">>> ";
		int input = Input<int>();
		if (input > 6 || input < 1)
			continue;
		return input;;
	}
}



void StoreEquip::ShowHeadList()
{
	while (true)
	{
		system("cls");
		int j = 1;
		for (int i = 0; i < m_vecItemList.size(); ++i)
		{
			ItemEquip* item = (ItemEquip*)m_vecItemList[i];
			if (item->GetItemRegion() == HEAD)
			{
				cout << "[" << j << "] ������ " << endl;
				item->Render();
				j++;
			}
		}
		cout << "�����Ͻ� �������� ��ȣ�� �Է����ּ���(������ 0��)>>> ";
		int input = Input<int>();
		if (input < 0 || input > m_vecItemList.size() + 1)
			continue;
		if (input == 0)
			return;
		Item* item = m_vecItemList[input - 1]->Clone();
		AddInventoryInItem(item);
	}

}

void StoreEquip::ShowShirtList()
{
	while (true)
	{
		system("cls");
		int j = 1;
		for (int i = 0; i < m_vecItemList.size(); ++i)
		{
			ItemEquip* item = (ItemEquip*)m_vecItemList[i];
			if (item->GetItemRegion() == SHIRT)
			{
				cout << "[" << j << "] ������ " << endl;
				item->Render();
				j++;
			}
		}
		cout << "�����Ͻ� �������� ��ȣ�� �Է����ּ���(������ 0��)>>> ";
		int input = Input<int>();
		if (input < 0 || input > m_vecItemList.size() + 1)
			continue;
		if (input == 0)
			return;
		Item* item = m_vecItemList[input - 1]->Clone();
		AddInventoryInItem(item);
	}
}

void StoreEquip::ShowGloveList()
{
	while (true)
	{
		system("cls");
		int j = 1;
		for (int i = 0; i < m_vecItemList.size(); ++i)
		{
			ItemEquip* item = (ItemEquip*)m_vecItemList[i];
			if (item->GetItemRegion() == GLOVE)
			{
				cout << "[" << j << "] ������ " << endl;
				item->Render();
				j++;
			}
		}
		cout << "�����Ͻ� �������� ��ȣ�� �Է����ּ���(������ 0��)>>> ";
		int input = Input<int>();
		if (input < 0 || input > m_vecItemList.size() + 1)
			continue;
		if (input == 0)
			return;
		Item* item = m_vecItemList[input - 1]->Clone();
		AddInventoryInItem(item);
	}
}

void StoreEquip::ShowShoesList()
{
	while (true)
	{
		system("cls");
		int j = 1;
		for (int i = 0; i < m_vecItemList.size(); ++i)
		{
			ItemEquip* item = (ItemEquip*)m_vecItemList[i];
			if (item->GetItemRegion() == SHOES)
			{
				cout << "[" << j << "] ������ " << endl;
				item->Render();
				j++;
			}
		}
		cout << "�����Ͻ� �������� ��ȣ�� �Է����ּ���(������ 0��)>>> ";
		int input = Input<int>();
		if (input < 0 || input > m_vecItemList.size() + 1)
			continue;
		if (input == 0)
			return;
		Item* item = m_vecItemList[input - 1]->Clone();
		AddInventoryInItem(item);
	}
}
