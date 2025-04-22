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
	cout << "******************* 디지몬 세계에 오신 걸 환영합니다. *******************" << endl;
	cout << "반갑습니다! 테이머님 이름이 무엇인가요? " << endl;
	cout << ">>>";
	string strName = Input<string>();
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(ObjectManager)->CreateObject("Player", OT_PLAYER);
	pPlayer->SetName(strName);
	while (true)
	{
		system("cls");
		cout << strName << "님 반갑습니다. 테이머를 선택해주세요 " << endl;
		cout << "1. 신태일" << endl;
		cout << "2. 메튜" << endl;
		cout << "3. 이미나" << endl;
		cout << "4. 리키" << endl;
		int iInput = Input<int>();
		if (iInput < T_NONE || iInput >= T_END)
			continue;
		switch (iInput)
		{
		case T_TAIL:
			pPlayer->SetCharacterInfo(0, 0, 0, 0, 100, 100, 1, 0);
			pPlayer->SetTaymerTypeAndName(T_TAIL, "신태일");
			break;
		case T_METU:
			pPlayer->SetCharacterInfo(0, 0, 0, 0, 100, 100, 1, 0);
			pPlayer->SetTaymerTypeAndName(T_METU, "메튜");
			break;
		case T_MINA:
			pPlayer->SetCharacterInfo(0, 0, 0, 0, 100, 100, 1, 0);
			pPlayer->SetTaymerTypeAndName(T_MINA, "이미나");
			break;
		case T_LIKI:
			pPlayer->SetCharacterInfo(0, 0, 0, 0, 100, 100, 1, 0);
			pPlayer->SetTaymerTypeAndName(T_LIKI, "리키");
			break;
		}
		system("cls");
		cout << pPlayer->GetTaymerName() << "을 선택하셨습니다." << endl;
		cout << "닷트본부로 이동합니다......" << endl;
		Sleep(1500);
		break;
	}


}
