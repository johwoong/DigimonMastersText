#include "pch.h"
#include "CGame.h"
#include "ObjectManager.h"
#include "SkillManager.h"
#include "MapManager.h"
#include "CPlayer.h"
#include "StoreManager.h"
#include "Inventory.h"
#include "FileStream.h"
#include "Incubator.h"

DEFINITION_SINGLE(CGame)

CGame::CGame() : isPlayer(false)
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

	if (!GET_SINGLE(Incubator)->Init())
		return false;

	return true;
}

void CGame::Update()
{
	while (true)
	{
		system("cls");
		CheckGameMode();
		if(!isPlayer)
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
	DESTORY_SINGLE(Incubator);
}

void CGame::CheckGameMode()
{
	FileStream file;
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(ObjectManager)->FindObject("Player");
	while (true)
	{
		system("cls");
		SetConsoleColor(11);
		cout << "*************************디지몬 마스터즈*************************" << endl;
		cout << "1. 새 게임" << endl;
		cout << "2. 불러오기" << endl;
		int input = Input<int>();
		if (input == 1)
		{
			ResetConsoleColor();
			break;
		}
		else if (input == 2)
		{
			if (file.Open("playerData.sar", "rb"))
			{
				pPlayer->Load(&file);
				GET_SINGLE(Inventory)->Load(&file);
				GET_SINGLE(Incubator)->Load(&file);
				isPlayer = true;
				file.Close();
			}
			return;
		}
		else
			continue;
		ResetConsoleColor();
	}
}

void CGame::SetPlayer()
{
	system("cls");
	cout << "******************* 디지몬 세계에 오신 걸 환영합니다. *******************" << endl;
	cout << "반갑습니다! 테이머님 이름이 무엇인가요? " << endl;
	cout << ">>>";
	string strName = Input<string>();
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(ObjectManager)->FindObject("Player");
	pPlayer->SetName(strName);
	while (true)
	{
		system("cls");
		Skill* skill = new Skill;
		cout << strName << "님 반갑습니다. 테이머를 선택해주세요 " << endl;
		cout << "1. 신태일" << endl;
		cout << "2. 메튜" << endl;
		cout << "3. 이미나" << endl;
		cout << "4. 리키" << endl;
		cout << "5. 뒤로가기" << endl;
		int iInput = Input<int>();
		if (iInput < T_NONE || iInput >= T_END)
			continue;
		switch (iInput)
		{
		case T_TAIL:
			pPlayer->SetCharacterInfo(0, 0, 0, 0, 100, 100, 1, 0, 100, 0);
			pPlayer->SetTaymerTypeAndName(T_TAIL, "신태일");
			skill->SetSkillName("광폭화");
			skill->SetFasiveSkillName("신태일의 용기");
			pPlayer->SetSkill(skill);
			break;
		case T_METU:
			pPlayer->SetCharacterInfo(0, 0, 0, 0, 100, 100, 1, 0, 100, 0);
			pPlayer->SetTaymerTypeAndName(T_METU, "메튜");
			skill->SetSkillName("기백");
			skill->SetFasiveSkillName("메튜의 우정");
			pPlayer->SetSkill(skill);
			break;
		case T_MINA:
			pPlayer->SetCharacterInfo(0, 0, 0, 0, 100, 100, 1, 0, 100, 0);
			pPlayer->SetTaymerTypeAndName(T_MINA, "이미나");
			skill->SetSkillName("기원");
			skill->SetFasiveSkillName("이미나의 순수");
			pPlayer->SetSkill(skill);
			break;
		case T_LIKI:
			pPlayer->SetCharacterInfo(0, 0, 0, 0, 100, 100, 1, 0, 100, 0);
			pPlayer->SetTaymerTypeAndName(T_LIKI, "리키");
			skill->SetSkillName("응원");
			skill->SetFasiveSkillName("리키의 희망");
			pPlayer->SetSkill(skill);
			break;
		case T_BACK:
			return;
		}
		system("cls");
		cout << pPlayer->GetTaymerName() << "을 선택하셨습니다." << endl;
		cout << "닷트본부로 이동합니다......" << endl;
		Sleep(1500);
		break;
	}


}
