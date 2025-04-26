#include "pch.h"
#include "MapDart.h"
#include "MapManager.h"
#include "ObjectManager.h"
#include "CPlayer.h"
#include "CDigimon.h"
#include "Skill.h"
#include "StoreManager.h"
#include "Inventory.h"

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
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(ObjectManager)->FindObject("Player");
	while (true)
	{
		system("cls");
		cout << "현재 위치 : " << strMapName << endl;
		switch (OutputMenu())
		{
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
				cout << "디지몬이 존재하지 않습니다!!" << endl;
			else
				pPlayer->GetDigimon()->Render();
			system("pause");
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
		cout << "1. 맵" << endl;
	else
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

void MapDart::SelectDigimon()
{
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(ObjectManager)->FindObject("Player");
	CDigimon* pDigimon = (CDigimon*)GET_SINGLE(ObjectManager)->FindObject("Digimon");
	while (true)
	{
		system("cls");
		cout << "고동혁 : 닷트본부에 온걸 환영한다. 우리의 일원으로서 파트너 디지몬을 주지. 어떤걸 고르겠나.." << endl;
		cout << "1. 아구몬" << endl;
		cout << "2. 파피몬" << endl;
		cout << "3. 길몬" << endl;
		cout << "4. 파닥몬" << endl;
		cout << "5. 브이몬" << endl;
		cout << ">>> ";
		int iMenu = Input<int>();
		if (iMenu <= 0 || iMenu > 5)
			continue;
		switch (iMenu)
		{
		case 1:
			pDigimon->SetDigName("아구몬");
			pDigimon->SetCharacterInfo(10, 20, 5, 10, 100, 60, 1, 0, 0, 0);
			pDigimon->SetEvalutionType(1);
			pDigimon->SetAttributeType(3);
			pDigimon->AddSKill(new Skill("꼬마 불꽃", 10, 20));
			pDigimon->AddSKill(new Skill("꼬마 화염", 50, 50));
			break;
		case 2:
			pDigimon->SetDigName("파피몬");
			pDigimon->SetCharacterInfo(10, 20, 5, 10, 100, 60, 1, 0, 0, 0);
			pDigimon->SetEvalutionType(1);
			pDigimon->SetAttributeType(2);
			pDigimon->AddSKill(new Skill("뿔 찌르기", 10, 20));
			pDigimon->AddSKill(new Skill("푸른 불꽃", 50, 50));
			break;
		case 3:
			pDigimon->SetDigName("길몬");
			pDigimon->SetCharacterInfo(10, 20, 5, 10, 100, 60, 1, 0, 0, 0);
			pDigimon->SetEvalutionType(1);
			pDigimon->SetAttributeType(3);
			pDigimon->AddSKill(new Skill("화염 불꽃", 10, 20));
			pDigimon->AddSKill(new Skill("브레스", 50, 50));
			break;
		case 4:
			pDigimon->SetDigName("파닥몬");
			pDigimon->SetCharacterInfo(10, 20, 5, 10, 100, 60, 1, 0, 0, 0);
			pDigimon->SetEvalutionType(1);
			pDigimon->SetAttributeType(1);
			pDigimon->AddSKill(new Skill("공기팡", 10, 20));
			pDigimon->AddSKill(new Skill("공기버블", 50, 50));
			break;
		case 5:
			pDigimon->SetDigName("브이몬");
			pDigimon->SetCharacterInfo(10, 20, 5, 10, 100, 60, 1, 0, 0, 0);
			pDigimon->SetEvalutionType(1);
			pDigimon->SetAttributeType(3);
			pDigimon->AddSKill(new Skill("박치기", 10, 20));
			pDigimon->AddSKill(new Skill("브이 펀치", 60, 40));
			break;
		}
		pPlayer->SetDigimon(pDigimon);
		cout << pPlayer->GetDigimon()->GetDigName() << "을 선택하셨습니다." << endl;
		pPlayer->SetIsDigimon(true);
		system("pause");		break;
	}
}

int MapDart::OutputMap()
{
	while (true)
	{
		system("cls");
		cout << "어디로 이동하시겠습니까?" << endl;
		cout << "1. 시작의마을" << endl;
		cout << "2. 서부마을" << endl;
		cout << "3. 눈보라마을" << endl;
		cout << "4. 뒤로가기" << endl;
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


