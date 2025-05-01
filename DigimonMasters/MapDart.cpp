#include "pch.h"
#include "MapDart.h"
#include "MapManager.h"
#include "ObjectManager.h"
#include "CPlayer.h"
#include "CDigimon.h"
#include "Skill.h"
#include "StoreManager.h"
#include "Inventory.h"
#include "Incubator.h"
#include "FileStream.h"

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
	Incubator* pIncubator = new Incubator;
	FileStream file("playerData.sar", "wb");
	while (true)
	{
		system("cls");
		cout << "���� ��ġ : " << strMapName << endl;
		switch (OutputMenu())
		{
		case MENU_SAVE:
			if (file.Open("playerData.sar", "wb"))
			{
				pPlayer->Save(&file);
				file.Close();
			}
			break;
		case MENU_TALK:
			if (pPlayer->GetIsDigimon())
				switch (OutputMap())
				{
				case 1:
					GET_SINGLE(MapManager)->GetInst()->GetMapList()[1]->Update();
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
			GET_SINGLE(StoreManager)->GetInst()->Update(this);
			break;
		case MENU_INVENTORY:
			GET_SINGLE(Inventory)->GetInst()->Update();
			break;
		case MENU_STATUS:
			system("cls");
			pPlayer->Render();
			system("pause");  
			break;
		case MENU_DIGIMONSTATIUS:
			system("cls");
			if (pPlayer->GetDigimon() == nullptr)
			{
				cout << "�������� �������� �ʽ��ϴ�!!" << endl;
			}
			else
			{
				SetConsoleColor(14);
				cout << "[���� ������]" << endl;
				pPlayer->GetDigimon()->Render();
				pPlayer->RenderDigimonList();
				ResetConsoleColor();
			}
			system("pause");
			break;
		case MENU_CHANGEDIGIMON:
			system("cls");
			if (pPlayer->GetDigimon() == nullptr)
			{
				cout << "�������� �������� �ʽ��ϴ�!!" << endl;
				system("pause");
			}
			else
			{
				while (true)
				{
					system("cls");
					SetConsoleColor(14);
					cout << "[���� ������]" << endl << endl;
					pPlayer->GetDigimon()->Render();
					pPlayer->PrintHasDigimon(); 
					cout << "��ü�� �������� �������ּ��� : ";
					int iInput = Input<int>();
					if (iInput < 1 || iInput > pPlayer->GetDigimonVec().size())
						continue;
					pPlayer->ChangeDigimon(iInput - 1);
					cout << "�������� " << pPlayer->GetDigimon()->m_strDigName << "���� ��ü�Ǿ����ϴ�." << endl;
					system("pause");
					break;
				}
			}
			break;
		case MENU_INCUBATOR:
			pIncubator->SetEggVec();
			pIncubator->Update();
			break;
		case MENU_EXIT:
			exit(0);
		}
	}
}

int MapDart::OutputMenu()
{
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(ObjectManager)->FindObject("Player");
	cout << "0. �����ϱ�" << endl;
	if (pPlayer->GetIsDigimon())
		cout << "1. ��" << endl;
	else
		cout << "1. ������ ��ȭ" << endl;
	cout << "2. ����" << endl;
	cout << "3. �κ��丮 ����" << endl;
	cout << "4. ĳ���� ����â" << endl;
	cout << "5. ������ ����â" << endl;
	cout << "6. ������ ��ü" << endl;
	cout << "7. ������ ��ť������" << endl;
	cout << "8. ����" << endl;
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
			pDigimon->SetCharacterInfo(10, 20, 5, 10, 100, 60, 1, 0, 0, 0);
			pDigimon->SetAttributeType(3);
			pDigimon->AddSKill(new Skill("���� �Ҳ�", 10, 20));
			pDigimon->AddSKill(new Skill("���� ȭ��", 50, 50));
			pDigimon->SetEvaultionList("�׷��̸�", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("ȭ����", 100, 150));
			pDigimon->AddSKill(new Skill("�ް� ȭ��", 100, 100));
			pDigimon->SetEvaultionList("��Ż�׷��̸�", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("ö����", 100, 200));
			pDigimon->AddSKill(new Skill("�ΰ����� �̻���", 200, 400));
			pDigimon->SetEvaultionList("���׷��̸�", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("�����", 300, 100));
			pDigimon->AddSKill(new Skill("�׶󱤼�", 600, 100));
			pDigimon->SetEvaultionList("���ް���", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("�׷��̰���", 1000, 100));
			pDigimon->AddSKill(new Skill("������", 2000, 500));
			pDigimon->UpdateSkill();
			break;
		case 2:
			pDigimon->SetDigName("���Ǹ�");
			pDigimon->SetCharacterInfo(10, 20, 5, 10, 100, 60, 1, 0, 0, 0);
			pDigimon->SetAttributeType(2);
			pDigimon->SetEvaultionType(1);
			pDigimon->AddSKill(new Skill("�� ���", 10, 20));
			pDigimon->AddSKill(new Skill("Ǫ�� �Ҳ�", 50, 50));
			pDigimon->SetEvaultionList("�����", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("Ǫ��ȭ��", 100, 150));
			pDigimon->AddSKill(new Skill("��������", 100, 100));
			pDigimon->SetEvaultionList("�������", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("����ġ", 100, 200));
			pDigimon->AddSKill(new Skill("��ű", 200, 400));
			pDigimon->SetEvaultionList("��Ż�����", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("��ȭ", 300, 100));
			pDigimon->AddSKill(new Skill("�ΰ�������", 600, 100));
			pDigimon->SetEvaultionList("���ް���", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("�׷��̰���", 1000, 100));
			pDigimon->AddSKill(new Skill("������", 2000, 500));
			pDigimon->UpdateSkill();
			break;
		case 3:
			pDigimon->SetDigName("���");
			pDigimon->SetCharacterInfo(10, 20, 5, 10, 100, 60, 1, 0, 0, 0);
			pDigimon->SetAttributeType(3);
			pDigimon->SetEvaultionType(1);
			pDigimon->AddSKill(new Skill("ȭ�� �Ҳ�", 10, 20));
			pDigimon->AddSKill(new Skill("�극��", 50, 50));
			pDigimon->AddSKill(new Skill("ȭ�� ű", 100, 150));
			pDigimon->AddSKill(new Skill("��ο�", 100, 100));
			pDigimon->SetEvaultionList("�׶���", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("ȭ������", 100, 200));
			pDigimon->AddSKill(new Skill("���׷ο�", 200, 400));
			pDigimon->SetEvaultionList("�ް��׶���", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("â���", 300, 100));
			pDigimon->AddSKill(new Skill("�����������", 600, 100));
			pDigimon->SetEvaultionList("��ũ��", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("��ũ��", 1000, 100));
			pDigimon->AddSKill(new Skill("������ ���", 2000, 500));
			pDigimon->SetEvaultionList("��ũ�� ũ�������", 30, 30, 20, 20);

			break;
		case 4:
			pDigimon->SetDigName("�Ĵڸ�");
			pDigimon->SetCharacterInfo(10, 20, 5, 10, 100, 60, 1, 0, 0, 0);
			pDigimon->SetAttributeType(1);
			pDigimon->SetEvaultionType(1);
			pDigimon->AddSKill(new Skill("������", 10, 20));
			pDigimon->AddSKill(new Skill("�������", 50, 50));
			pDigimon->AddSKill(new Skill("���� ��ġ", 100, 150));
			pDigimon->AddSKill(new Skill("���� ��", 100, 100));
			pDigimon->SetEvaultionList("������", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("õ���� ��", 100, 200));
			pDigimon->AddSKill(new Skill("����Ʈ �ǵ�", 200, 400));
			pDigimon->SetEvaultionList("Ȧ��������", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("���� ����", 300, 100));
			pDigimon->AddSKill(new Skill("����Ʈ ��", 600, 100));
			pDigimon->SetEvaultionList("�����Ǹ�", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("��� ȭ��", 1000, 100));
			pDigimon->AddSKill(new Skill("���� ����", 2000, 500));
			pDigimon->SetEvaultionList("�� �����Ǹ�", 30, 30, 20, 20);
			break;
		case 5:
			pDigimon->SetDigName("���̸�");
			pDigimon->SetCharacterInfo(10, 20, 5, 10, 100, 60, 1, 0, 0, 0);
			pDigimon->SetAttributeType(3);
			pDigimon->SetEvaultionType(1);
			pDigimon->AddSKill(new Skill("��ġ��", 10, 20));
			pDigimon->AddSKill(new Skill("���� ��ġ", 60, 40));
			pDigimon->AddSKill(new Skill("���� ��ġ", 100, 150));
			pDigimon->AddSKill(new Skill("������", 100, 100));
			pDigimon->SetEvaultionList("�������̸�", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("��ũ����", 100, 200));
			pDigimon->AddSKill(new Skill("����õ��", 200, 400));
			pDigimon->SetEvaultionList("���ϵ���", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("�Ⱑ ȭ����", 300, 100));
			pDigimon->AddSKill(new Skill("�ް� ���̵�", 600, 100));
			pDigimon->SetEvaultionList("Ȳ������", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("���ް� ���̵�", 1000, 100));
			pDigimon->AddSKill(new Skill("���̴� ��", 2000, 500));
			pDigimon->SetEvaultionList("Ȳ������ �ȶ����", 30, 30, 20, 20);
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
		cout << "1. �����Ǹ���" << endl;
		cout << "2. ���θ���" << endl;
		cout << "3. ��������" << endl;
		cout << "4. �ڷΰ���" << endl;
		cout << ">>> ";
		int iMenu = Input<int>();
		if (iMenu <= 0 || iMenu > 4)
			continue;
		return iMenu;
	}
}

void MapDart::Battle()
{

}


