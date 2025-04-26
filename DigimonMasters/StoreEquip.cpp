#include "pch.h"
#include "StoreEquip.h"
#include "ItemEquip.h"

StoreEquip::StoreEquip() : iHead(0), iShirt(0), iGlove(0), iPant(0), iShoes(0)
{	
	ItemEquip* item = (ItemEquip*)CreateItem("�������� ����", IT_EQ, 2000, 3, "�������� ����");
	item->SetItemRegion(HEAD);
	item->SetItemStatInfo(2, 3, 10, 5, 5);	
	item = (ItemEquip*)CreateItem("���ڸ��� ����", IT_EQ, 2000, 3, "�������� ����");
	item->SetItemRegion(HEAD);
	item->SetItemStatInfo(2, 3, 10, 5, 5);

	item = (ItemEquip*)CreateItem("�������� ����", IT_EQ, 2000, 3, "�������� ����");
	item->SetItemRegion(SHIRT);
	item->SetItemStatInfo(2, 3, 10, 5, 5);
	item = (ItemEquip*)CreateItem("���ڸ��� ����", IT_EQ, 2000, 3, "�������� ����");
	item->SetItemRegion(SHIRT);
	item->SetItemStatInfo(2, 3, 10, 5, 5);


	item = (ItemEquip*)CreateItem("�������� �尩", IT_EQ, 2000, 3, "�������� ����");
	item->SetItemRegion(GLOVE);
	item->SetItemStatInfo(2, 3, 10, 5, 5);
	item = (ItemEquip*)CreateItem("���ڸ��� �尩", IT_EQ, 2000, 3, "�������� ����");
	item->SetItemRegion(GLOVE);
	item->SetItemStatInfo(2, 3, 10, 5, 5);


	item = (ItemEquip*)CreateItem("�������� ����", IT_EQ, 2000, 3, "�������� ����");
	item->SetItemRegion(PANT);
	item->SetItemStatInfo(2, 3, 10, 5, 5);
	item = (ItemEquip*)CreateItem("���ڸ��� ����", IT_EQ, 2000, 3, "�������� ����");
	item->SetItemRegion(PANT);
	item->SetItemStatInfo(2, 3, 10, 5, 5);


	item = (ItemEquip*)CreateItem("�������� �Ź�", IT_EQ, 2000, 3, "�������� ����");
	item->SetItemRegion(SHOES);
	item->SetItemStatInfo(2, 3, 10, 5, 5);
	item = (ItemEquip*)CreateItem("���ڸ��� �Ź�", IT_EQ, 2000, 3, "�������� ����");
	item->SetItemRegion(SHOES);
	item->SetItemStatInfo(2, 3, 10, 5, 5);
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
			ShowPantList();
			break;
		case 5:
			ShowGloveList();
			break;
		case 6:
			ShowShoesList();
			break;
		case 7:
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
		cout << "4. ����" << endl;
		cout << "5. �尩" << endl;
		cout << "6. �Ź�" << endl;
		cout << "7. �ڷΰ���" << endl;
		cout << ">>> ";
		int input = Input<int>();
		if (input > 7 || input < 1)
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
		vector<int> vecHeadIndex; 

		for (int i = 0; i < m_vecItemList.size(); ++i)
		{
			ItemEquip* item = (ItemEquip*)m_vecItemList[i];
			if (item->GetItemRegion() == HEAD)
			{
				vecHeadIndex.push_back(i);
				cout << "[" << j << "] ������ " << endl;
				item->Render();
				j++;
			}
		}

		cout << "�����Ͻ� �������� ��ȣ�� �Է����ּ���(������ 0��)>>> ";
		int input = Input<int>();

		if (input < 0 || input >= j)
			continue;
		if (input == 0)
			return;

		int realIndex = vecHeadIndex[input - 1];
		Item* item = m_vecItemList[realIndex]->Clone();
		AddInventoryInItem(item);
	}

}

void StoreEquip::ShowShirtList()
{
	while (true)
	{
		system("cls");
		int j = 1;
		vector<int> vecShirtIndex;

		for (int i = 0; i < m_vecItemList.size(); ++i)
		{
			ItemEquip* item = (ItemEquip*)m_vecItemList[i];
			if (item->GetItemRegion() == SHIRT)
			{
				vecShirtIndex.push_back(i);
				cout << "[" << j << "] ������ " << endl;
				item->Render();
				j++;
			}
		}

		cout << "�����Ͻ� �������� ��ȣ�� �Է����ּ���(������ 0��)>>> ";
		int input = Input<int>();

		if (input < 0 || input >= j)
			continue;
		if (input == 0)
			return;

		int realIndex = vecShirtIndex[input - 1];
		Item* item = m_vecItemList[realIndex]->Clone();
		AddInventoryInItem(item);
	}
}

void StoreEquip::ShowGloveList()
{
	while (true)
	{
		system("cls");
		int j = 1;
		vector<int> vecGloveIndex;

		for (int i = 0; i < m_vecItemList.size(); ++i)
		{
			ItemEquip* item = (ItemEquip*)m_vecItemList[i];
			if (item->GetItemRegion() == GLOVE)
			{
				vecGloveIndex.push_back(i);
				cout << "[" << j << "] ������ " << endl;
				item->Render();
				j++;
			}
		}

		cout << "�����Ͻ� �������� ��ȣ�� �Է����ּ���(������ 0��)>>> ";
		int input = Input<int>();

		if (input < 0 || input >= j)
			continue;
		if (input == 0)
			return;

		int realIndex = vecGloveIndex[input - 1];
		Item* item = m_vecItemList[realIndex]->Clone();
		AddInventoryInItem(item);
	}
}

void StoreEquip::ShowPantList()
{
	while (true)
	{
		system("cls");
		int j = 1;
		vector<int> vecPantList;

		for (int i = 0; i < m_vecItemList.size(); ++i)
		{
			ItemEquip* item = (ItemEquip*)m_vecItemList[i];
			if (item->GetItemRegion() == PANT)
			{
				vecPantList.push_back(i);
				cout << "[" << j << "] ������ " << endl;
				item->Render();
				j++;
			}
		}

		cout << "�����Ͻ� �������� ��ȣ�� �Է����ּ���(������ 0��)>>> ";
		int input = Input<int>();

		if (input < 0 || input >= j)
			continue;
		if (input == 0)
			return;

		int realIndex = vecPantList[input - 1];
		Item* item = m_vecItemList[realIndex]->Clone();
		AddInventoryInItem(item);
	}
}

void StoreEquip::ShowShoesList()
{
	while (true)
	{
		system("cls");
		int j = 1;
		vector<int> vecShoesList;

		for (int i = 0; i < m_vecItemList.size(); ++i)
		{
			ItemEquip* item = (ItemEquip*)m_vecItemList[i];
			if (item->GetItemRegion() == SHOES)
			{
				vecShoesList.push_back(i);
				cout << "[" << j << "] ������ " << endl;
				item->Render();
				j++;
			}
		}

		cout << "�����Ͻ� �������� ��ȣ�� �Է����ּ���(������ 0��)>>> ";
		int input = Input<int>();

		if (input < 0 || input >= j)
			continue;
		if (input == 0)
			return;

		int realIndex = vecShoesList[input - 1];
		Item* item = m_vecItemList[realIndex]->Clone();
		AddInventoryInItem(item);
	}
}
