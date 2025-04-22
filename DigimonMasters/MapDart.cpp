#include "pch.h"
#include "MapDart.h"

MapDart::MapDart() 
{
	strMapName = "��Ʈ ����";
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
		cout << "���� ��ġ : " << strMapName << endl;
		switch (OutputMenu())
		{
		case MENU_TALK:
			cout << "������ ��ȭ��";
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
	cout << "1. ������ ��ȭ" << endl;
	cout << "2. ����" << endl;
	cout << "3. �κ��丮 ����" << endl;
	cout << "4. ĳ���� ����â" << endl;
	cout << "5. ������ ����â" << endl;
	cout << "6. ����" << endl;
	int iMenu = Input<int>();
	if (iMenu <= MENU_NONE || iMenu > MENU_EXIT)
		return MENU_NONE;

	return iMenu;
}
