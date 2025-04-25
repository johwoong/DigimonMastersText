#include "pch.h"
#include "StoreManager.h"
#include "Map.h"
#include "Store.h"
#include "StoreEquip.h"
#include "StoreEgg.h"
#include "StoreGeneric.h"
#include "ItemEquip.h"
#include "ItemEgg.h"
#include "ItemGeneric.h"
DEFINITION_SINGLE(StoreManager)

StoreManager::StoreManager()
{

}

StoreManager::~StoreManager()
{

}



bool StoreManager::Init()
{
	return true;
}

void StoreManager::Update(class Map* currentMap)
{
	Store* pStore = nullptr;
	while (true)
	{
		system("cls");
		cout << "********************" << currentMap->GetMapName() << "상점 ********************" << endl;
		switch (OutputMenu())
		{
		case 1:
			pStore = new StoreEquip;
			pStore->Update();
			break;
		case 2:
			pStore = new StoreEgg;
			pStore->Update();
			break;
		case 3:
			pStore = new StoreGeneric;
			pStore->Update();
			break;
		case 4:
			return;
		}

	}
}

int StoreManager::OutputMenu()
{
	while (true)
	{
		system("cls");
		cout << "1. 테이머 장비" << endl;
		cout << "2. 디지몬 알" << endl;
		cout << "3. 일반 상점" << endl;
		cout << "4. 뒤로가기" << endl;
		cout << ">>> ";
		int input = Input<int>();
		if (input < 1 || input > 4)
			continue;
		return input;
	}
}
