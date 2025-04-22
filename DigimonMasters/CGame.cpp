#include "pch.h"
#include "CGame.h"
#include "ObjectManager.h"
#include "SkillManager.h"
#include "MapManager.h"
#include "CPlayer.h"

DEFINITION_SINGLE(CGame)

CGame::CGame()
{
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

	return true;
}

void CGame::Update()
{
	while (true)
	{
		system("cls");
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
}

void CGame::SetPlayer()
{
	cout << "******************* ������ ���迡 ���� �� ȯ���մϴ�. *******************" << endl;
	cout << "�ݰ����ϴ�! ���̸Ӵ� �̸��� �����ΰ���? " << endl;
	cout << ">>>";
	string strName = Input<string>();
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(ObjectManager)->CreateObject("Player", OT_PLAYER);
	pPlayer->SetName(strName);
	while (true)
	{
		system("cls");
		cout << strName << "�� �ݰ����ϴ�. ���̸Ӹ� �������ּ��� " << endl;
		cout << "1. ������" << endl;
		cout << "2. ��Ʃ" << endl;
		cout << "3. �̹̳�" << endl;
		cout << "4. ��Ű" << endl;
		int iInput = Input<int>();
		if (iInput < T_NONE || iInput >= T_END)
			continue;
		switch (iInput)
		{
		case T_TAIL:
			pPlayer->SetCharacterInfo(0, 0, 0, 0, 100, 100, 1, 0);
			pPlayer->SetTaymerTypeAndName(T_TAIL, "������");
			break;
		case T_METU:
			pPlayer->SetCharacterInfo(0, 0, 0, 0, 100, 100, 1, 0);
			pPlayer->SetTaymerTypeAndName(T_METU, "��Ʃ");
			break;
		case T_MINA:
			pPlayer->SetCharacterInfo(0, 0, 0, 0, 100, 100, 1, 0);
			pPlayer->SetTaymerTypeAndName(T_MINA, "�̹̳�");
			break;
		case T_LIKI:
			pPlayer->SetCharacterInfo(0, 0, 0, 0, 100, 100, 1, 0);
			pPlayer->SetTaymerTypeAndName(T_LIKI, "��Ű");
			break;
		}
		system("cls");
		cout << pPlayer->GetTaymerName() << "�� �����ϼ̽��ϴ�." << endl;
		cout << "��Ʈ���η� �̵��մϴ�......" << endl;
		Sleep(1500);
		break;
	}


}
