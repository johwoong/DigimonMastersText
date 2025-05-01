#include "pch.h"
#include "CGame.h"
#include "ObjectManager.h"
#include "SkillManager.h"
#include "MapManager.h"
#include "CPlayer.h"
#include "StoreManager.h"
#include "Inventory.h"
#include "FileStream.h"

DEFINITION_SINGLE(CGame)

CGame::CGame()
{
	srand(unsigned int(NULL));
}

CGame::~CGame()
{
	Release();
}

bool CGame::Initialize()
{
	if (!GET_SINGLE(ObjectManager)->Init())
		return false;

	if (!GET_SINGLE(SkillManager)->Init())
		return false;

	if (!GET_SINGLE(MapManager)->Init())
		return false;

	if (!GET_SINGLE(StoreManager)->Init())
		return false;

	if (!GET_SINGLE(Inventory)->Init())
		return false;

	return true;
}

void CGame::Update()
{
	while (true)
	{
		system("cls");
		CheckGameMode();
		SetPlayer();
		GET_SINGLE(MapManager)->Update();
		system("pause");
	}
}

void CGame::Release()
{
	DESTORY_SINGLE(MapManager);
	DESTORY_SINGLE(ObjectManager);
	DESTORY_SINGLE(SkillManager);
	DESTORY_SINGLE(StoreManager);
	DESTORY_SINGLE(Inventory);
}

void CGame::CheckGameMode()
{
	FileStream stream;
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(ObjectManager)->CreateObject("Player", OT_PLAYER);
	while (true)
	{
		system("cls");
		SetConsoleColor(11);
		cout << "*************************������ ��������*************************" << endl;
		cout << "1. �� ����" << endl;
		cout << "2. �ҷ�����" << endl;
		int input = Input<int>();
		if (input == 1)
		{
			ResetConsoleColor();
			break;
		}
		else if (input == 2)
		{
			// �ҷ�����
			ResetConsoleColor();
			if (stream.Open("save.dat", "rb"))
			{
				GET_SINGLE(Inventory)->Load(stream);  // �κ��丮 �ҷ�����
				stream.Close();
				cout << "�ҷ����� �Ϸ�Ǿ����ϴ�." << endl;
				return;
			}
			cout << "�ҷ�����" << endl;
		}
		else
			continue;
		ResetConsoleColor();
	}
}

void CGame::SetPlayer()
{
	system("cls");
	cout << "******************* ������ ���迡 ���� �� ȯ���մϴ�. *******************" << endl;
	cout << "�ݰ����ϴ�! ���̸Ӵ� �̸��� �����ΰ���? " << endl;
	cout << ">>>";
	string strName = Input<string>();
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(ObjectManager)->CreateObject("Player", OT_PLAYER);
	pPlayer->SetName(strName);
	while (true)
	{
		system("cls");
		Skill* skill = new Skill;
		cout << strName << "�� �ݰ����ϴ�. ���̸Ӹ� �������ּ��� " << endl;
		cout << "1. ������" << endl;
		cout << "2. ��Ʃ" << endl;
		cout << "3. �̹̳�" << endl;
		cout << "4. ��Ű" << endl;
		cout << "5. �ڷΰ���" << endl;
		int iInput = Input<int>();
		if (iInput < T_NONE || iInput >= T_END)
			continue;
		switch (iInput)
		{
		case T_TAIL:
			pPlayer->SetCharacterInfo(0, 0, 0, 0, 100, 100, 1, 0, 100, 0);
			pPlayer->SetTaymerTypeAndName(T_TAIL, "������");
			skill->SetSkillName("����ȭ");
			skill->SetFasiveSkillName("�������� ���");
			pPlayer->SetSkill(skill);
			break;
		case T_METU:
			pPlayer->SetCharacterInfo(0, 0, 0, 0, 100, 100, 1, 0, 100, 0);
			pPlayer->SetTaymerTypeAndName(T_METU, "��Ʃ");
			skill->SetSkillName("���");
			skill->SetFasiveSkillName("��Ʃ�� ����");
			pPlayer->SetSkill(skill);
			break;
		case T_MINA:
			pPlayer->SetCharacterInfo(0, 0, 0, 0, 100, 100, 1, 0, 100, 0);
			pPlayer->SetTaymerTypeAndName(T_MINA, "�̹̳�");
			skill->SetSkillName("���");
			skill->SetFasiveSkillName("�̹̳��� ����");
			pPlayer->SetSkill(skill);
			break;
		case T_LIKI:
			pPlayer->SetCharacterInfo(0, 0, 0, 0, 100, 100, 1, 0, 100, 0);
			pPlayer->SetTaymerTypeAndName(T_LIKI, "��Ű");
			skill->SetSkillName("����");
			skill->SetFasiveSkillName("��Ű�� ���");
			pPlayer->SetSkill(skill);
			break;
		case T_BACK:
			return;
		}
		system("cls");
		cout << pPlayer->GetTaymerName() << "�� �����ϼ̽��ϴ�." << endl;
		cout << "��Ʈ���η� �̵��մϴ�......" << endl;
		Sleep(1500);
		break;
	}


}
