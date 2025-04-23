#include "pch.h"
#include "MapDart.h"
#include "ObjectManager.h"
#include "CPlayer.h"
#include "CDigimon.h"

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
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(ObjectManager)->FindObject("Player");
	while (true)
	{
		system("cls");
		cout << "���� ��ġ : " << strMapName << endl;
		switch (OutputMenu())
		{
		case MENU_TALK:
			if (pPlayer->GetIsDigimon())
				switch (OutputMap())
				{
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				}
			else
				SelectDigimon();
			break;
		case MENU_STORE:
			break;
		case MENU_INVENTORY:
			break;
		case MENU_STATUS:
			system("cls");
			pPlayer->Render();
			system("pause");  
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
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(ObjectManager)->FindObject("Player");
	if (pPlayer->GetIsDigimon())
		cout << "1. ��" << endl;
	else
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

void MapDart::SelectDigimon()
{
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(ObjectManager)->FindObject("Player");
	CDigimon* pDigimon = (CDigimon*)GET_SINGLE(ObjectManager)->FindObject("Digimon");
	while (true)
	{
		system("cls");
		cout << "���� : ��Ʈ���ο� �°� ȯ���Ѵ�. �츮�� �Ͽ����μ� ��Ʈ�� �������� ����. ��� ���ڳ�.." << endl;
		cout << "1. �Ʊ���" << endl;
		cout << "2. ���Ǹ�" << endl;
		cout << "3. ���" << endl;
		cout << "4. �Ĵڸ�" << endl;
		cout << "5. ���̸�" << endl;
		cout << ">>> ";
		int iMenu = Input<int>();
		if (iMenu <= 0 || iMenu > 5)
			continue;
		switch (iMenu)
		{
		case 1:
			pDigimon->SetDigName("�Ʊ���");
			pDigimon->SetCharacterInfo(10, 20, 5, 10, 100, 60, 1, 0);
			pDigimon->SetEvalutionType(1);
			pDigimon->SetAttributeType(3);
			break;
		case 2:
			pDigimon->SetDigName("���Ǹ�");
			pDigimon->SetCharacterInfo(10, 20, 5, 10, 100, 60, 1, 0);
			pDigimon->SetEvalutionType(1);
			pDigimon->SetAttributeType(2);
			break;
		case 3:
			pDigimon->SetDigName("���");
			pDigimon->SetCharacterInfo(10, 20, 5, 10, 100, 60, 1, 0);
			pDigimon->SetEvalutionType(1);
			pDigimon->SetAttributeType(3);
			break;
		case 4:
			pDigimon->SetDigName("�Ĵڸ�");
			pDigimon->SetCharacterInfo(10, 20, 5, 10, 100, 60, 1, 0);
			pDigimon->SetEvalutionType(1);
			pDigimon->SetAttributeType(1);
			break;
		case 5:
			pDigimon->SetDigName("���̸�");
			pDigimon->SetCharacterInfo(10, 20, 5, 10, 100, 60, 1, 0);
			pDigimon->SetEvalutionType(1);
			pDigimon->SetAttributeType(3);
			break;
		}
		pPlayer->SetDigimon(pDigimon);
		cout << pPlayer->GetDigimon()->GetDigName() << "�� �����ϼ̽��ϴ�." << endl;
		pPlayer->SetIsDigimon(true);
		system("pause");
		break;
	}
}

int MapDart::OutputMap()
{
	while (true)
	{
		system("cls");
		cout << "���� �̵��Ͻðڽ��ϱ�?" << endl;
		cout << "1. ���θ���" << endl;
		cout << "2. �����Ǹ���" << endl;
		cout << "3. ��������" << endl;
		cout << "4. �ڷΰ���" << endl;
		cout << ">>> ";
		int iMenu = Input<int>();
		if (iMenu <= 0 || iMenu > 4)
			continue;
		return iMenu;
	}
}
