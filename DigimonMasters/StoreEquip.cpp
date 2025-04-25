#include "pch.h"
#include "StoreEquip.h"
#include "ItemEquip.h"

StoreEquip::StoreEquip()
{	
	ItemEquip* item = (ItemEquip*)CreateItem("가고일 돌갑옷", IT_EQ, 2000, 3, "단단한 갑옷");
	item->SetItemRegion(SHIRT);
	item->SetItemStatInfo(10, 20, 30, 50, 0);
	
	
	item = (ItemEquip*)CreateItem("광전사의 신발", IT_EQ, 1500, 3, "민첩성 증가");
	item->SetItemRegion(SHOES);
	item->SetItemStatInfo(5, 10, 15, 20, 50);

	item = (ItemEquip*)CreateItem("디그다의 뿔머리", IT_EQ, 1500, 3, "민첩성 증가");
	item->SetItemRegion(HEAD);
	item->SetItemStatInfo(5, 10, 15, 20, 50);

	item = (ItemEquip*)CreateItem("레오몬의 바지", IT_EQ, 1500, 3, "민첩성 증가");
	item->SetItemRegion(PANT);
	item->SetItemStatInfo(5, 10, 15, 20, 50);

	item = (ItemEquip*)CreateItem("임프몬의 신발", IT_EQ, 1500, 3, "민첩성 증가");
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
		cout << "********** 테이머 장비 **********" << endl;
		cout << "1. 전체보기" << endl;
		cout << "2. 머리" << endl;
		cout << "3. 상의" << endl;
		cout << "4. 장갑" << endl;
		cout << "5. 신발" << endl;
		cout << "6. 뒤로가기" << endl;
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
				cout << "[" << j << "] 아이템 " << endl;
				item->Render();
				j++;
			}
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
				cout << "[" << j << "] 아이템 " << endl;
				item->Render();
				j++;
			}
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
				cout << "[" << j << "] 아이템 " << endl;
				item->Render();
				j++;
			}
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
				cout << "[" << j << "] 아이템 " << endl;
				item->Render();
				j++;
			}
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
