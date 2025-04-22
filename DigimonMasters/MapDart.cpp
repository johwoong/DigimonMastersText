#include "pch.h"
#include "MapDart.h"

MapDart::MapDart() 
{
	strMapName = "닷트 본부";
}

MapDart::~MapDart()
{
}

bool MapDart::Init()
{
	return true;
}

void MapDart::Update()
{
	while (true)
	{
		system("cls");
		cout << "현재 위치 : " << strMapName << endl;
		switch (OutputMenu())
		{
		case MENU_TALK:
			cout << "고동혁과 대화중";
			system("pause");
			break;
		case MENU_STORE:
			break;
		case MENU_INVENTORY:
			break;
		case MENU_STATUS:
			break;
		case MENU_DIGIMONSTATIUS:
			break;
		case MENU_EXIT:
			exit(0);
		}
	}
}

int MapDart::OutputMenu()
{
	cout << "1. 고동혁과 대화" << endl;
	cout << "2. 상점" << endl;
	cout << "3. 인벤토리 열기" << endl;
	cout << "4. 캐릭터 정보창" << endl;
	cout << "5. 디지몬 정보창" << endl;
	cout << "6. 종료" << endl;
	int iMenu = Input<int>();
	if (iMenu <= MENU_NONE || iMenu > MENU_EXIT)
		return MENU_NONE;

	return iMenu;
}
