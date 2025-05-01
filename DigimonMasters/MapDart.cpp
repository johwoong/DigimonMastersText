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
	Incubator* pIncubator = new Incubator;
	FileStream file("playerData.sar", "wb");
	while (true)
	{
		system("cls");
		cout << "현재 위치 : " << strMapName << endl;
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
				cout << "디지몬이 존재하지 않습니다!!" << endl;
			}
			else
			{
				SetConsoleColor(14);
				cout << "[현재 디지몬]" << endl;
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
				cout << "디지몬이 존재하지 않습니다!!" << endl;
				system("pause");
			}
			else
			{
				while (true)
				{
					system("cls");
					SetConsoleColor(14);
					cout << "[현재 디지몬]" << endl << endl;
					pPlayer->GetDigimon()->Render();
					pPlayer->PrintHasDigimon(); 
					cout << "교체할 디지몬을 선택해주세요 : ";
					int iInput = Input<int>();
					if (iInput < 1 || iInput > pPlayer->GetDigimonVec().size())
						continue;
					pPlayer->ChangeDigimon(iInput - 1);
					cout << "디지몬이 " << pPlayer->GetDigimon()->m_strDigName << "으로 교체되었습니다." << endl;
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
	cout << "0. 저장하기" << endl;
	if (pPlayer->GetIsDigimon())
		cout << "1. 맵" << endl;
	else
		cout << "1. 고동혁과 대화" << endl;
	cout << "2. 상점" << endl;
	cout << "3. 인벤토리 열기" << endl;
	cout << "4. 캐릭터 정보창" << endl;
	cout << "5. 디지몬 정보창" << endl;
	cout << "6. 디지몬 교체" << endl;
	cout << "7. 디지몬 인큐베이터" << endl;
	cout << "8. 종료" << endl;
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
			pDigimon->SetAttributeType(3);
			pDigimon->AddSKill(new Skill("꼬마 불꽃", 10, 20));
			pDigimon->AddSKill(new Skill("꼬마 화염", 50, 50));
			pDigimon->SetEvaultionList("그레이몬", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("화염볼", 100, 150));
			pDigimon->AddSKill(new Skill("메가 화염", 100, 100));
			pDigimon->SetEvaultionList("메탈그레이몬", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("철발톱", 100, 200));
			pDigimon->AddSKill(new Skill("인공지능 미사일", 200, 400));
			pDigimon->SetEvaultionList("워그레이몬", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("용발톱", 300, 100));
			pDigimon->AddSKill(new Skill("테라광선", 600, 100));
			pDigimon->SetEvaultionList("오메가몬", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("그레이가검", 1000, 100));
			pDigimon->AddSKill(new Skill("가루포", 2000, 500));
			pDigimon->UpdateSkill();
			break;
		case 2:
			pDigimon->SetDigName("파피몬");
			pDigimon->SetCharacterInfo(10, 20, 5, 10, 100, 60, 1, 0, 0, 0);
			pDigimon->SetAttributeType(2);
			pDigimon->SetEvaultionType(1);
			pDigimon->AddSKill(new Skill("뿔 찌르기", 10, 20));
			pDigimon->AddSKill(new Skill("푸른 불꽃", 50, 50));
			pDigimon->SetEvaultionList("가루몬", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("푸른화염", 100, 150));
			pDigimon->AddSKill(new Skill("얼음업니", 100, 100));
			pDigimon->SetEvaultionList("워가루몬", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("워펀치", 100, 200));
			pDigimon->AddSKill(new Skill("로킥", 200, 400));
			pDigimon->SetEvaultionList("메탈가루몬", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("설화", 300, 100));
			pDigimon->AddSKill(new Skill("인공지능포", 600, 100));
			pDigimon->SetEvaultionList("오메가몬", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("그레이가검", 1000, 100));
			pDigimon->AddSKill(new Skill("가루포", 2000, 500));
			pDigimon->UpdateSkill();
			break;
		case 3:
			pDigimon->SetDigName("길몬");
			pDigimon->SetCharacterInfo(10, 20, 5, 10, 100, 60, 1, 0, 0, 0);
			pDigimon->SetAttributeType(3);
			pDigimon->SetEvaultionType(1);
			pDigimon->AddSKill(new Skill("화염 불꽃", 10, 20));
			pDigimon->AddSKill(new Skill("브레스", 50, 50));
			pDigimon->AddSKill(new Skill("화염 킥", 100, 150));
			pDigimon->AddSKill(new Skill("드로우", 100, 100));
			pDigimon->SetEvaultionList("그라우몬", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("화염베기", 100, 200));
			pDigimon->AddSKill(new Skill("파잉로우", 200, 400));
			pDigimon->SetEvaultionList("메가그라우몬", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("창찌르기", 300, 100));
			pDigimon->AddSKill(new Skill("성스러운방패", 600, 100));
			pDigimon->SetEvaultionList("듀크몬", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("듀크검", 1000, 100));
			pDigimon->AddSKill(new Skill("정의의 깃발", 2000, 500));
			pDigimon->SetEvaultionList("듀크몬 크림존모드", 30, 30, 20, 20);

			break;
		case 4:
			pDigimon->SetDigName("파닥몬");
			pDigimon->SetCharacterInfo(10, 20, 5, 10, 100, 60, 1, 0, 0, 0);
			pDigimon->SetAttributeType(1);
			pDigimon->SetEvaultionType(1);
			pDigimon->AddSKill(new Skill("공기팡", 10, 20));
			pDigimon->AddSKill(new Skill("공기버블", 50, 50));
			pDigimon->AddSKill(new Skill("엔젤 펀치", 100, 150));
			pDigimon->AddSKill(new Skill("엔젤 봉", 100, 100));
			pDigimon->SetEvaultionList("엔젤몬", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("천공의 검", 100, 200));
			pDigimon->AddSKill(new Skill("라이트 실드", 200, 400));
			pDigimon->SetEvaultionList("홀리엔젤몬", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("빛의 심판", 300, 100));
			pDigimon->AddSKill(new Skill("라이트 검", 600, 100));
			pDigimon->SetEvaultionList("세라피몬", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("어둠 화살", 1000, 100));
			pDigimon->AddSKill(new Skill("빛의 방패", 2000, 500));
			pDigimon->SetEvaultionList("블랙 세라피몬", 30, 30, 20, 20);
			break;
		case 5:
			pDigimon->SetDigName("브이몬");
			pDigimon->SetCharacterInfo(10, 20, 5, 10, 100, 60, 1, 0, 0, 0);
			pDigimon->SetAttributeType(3);
			pDigimon->SetEvaultionType(1);
			pDigimon->AddSKill(new Skill("박치기", 10, 20));
			pDigimon->AddSKill(new Skill("브이 펀치", 60, 40));
			pDigimon->AddSKill(new Skill("엑스 펀치", 100, 150));
			pDigimon->AddSKill(new Skill("엑스빔", 100, 100));
			pDigimon->SetEvaultionList("엑스브이몬", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("스크래취", 100, 200));
			pDigimon->AddSKill(new Skill("무법천지", 200, 400));
			pDigimon->SetEvaultionList("파일드라몬", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("기가 화염포", 300, 100));
			pDigimon->AddSKill(new Skill("메가 블레이드", 600, 100));
			pDigimon->SetEvaultionList("황제드라몬", 30, 30, 20, 20);
			pDigimon->AddSKill(new Skill("오메가 블레이드", 1000, 100));
			pDigimon->AddSKill(new Skill("샤이닝 샷", 2000, 500));
			pDigimon->SetEvaultionList("황제드라몬 팔라딘모드", 30, 30, 20, 20);
			break;
		}
		pPlayer->SetDigimon(pDigimon);
		cout << pPlayer->GetDigimon()->GetDigName() << "을 선택하셨습니다." << endl;
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


