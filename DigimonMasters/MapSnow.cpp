#include "pch.h"
#include "MapSnow.h"


MapSnow::MapSnow() : MapStart()
{
    strMapName = "눈보라 마을";
}

MapSnow::~MapSnow()
{
}

bool MapSnow::Init()
{
	CreateEnemy();
    return true;
}

void MapSnow::Update()
{
	while (true)
	{
		CPlayer* pPlayer = (CPlayer*)GET_SINGLE(ObjectManager)->FindObject("Player");
		switch (OutputMap())
		{
		case 1:
			MapStart::Battle();
			break;
		case 2:
			GET_SINGLE(StoreManager)->GetInst()->Update(this);
			break;
		case 3:
			GET_SINGLE(Inventory)->GetInst()->Update();
			break;
		case 4:
			system("cls");
			pPlayer->Render();
			system("pause");
			break;
		case 5:
			system("cls");
			if (pPlayer->GetDigimon() == nullptr)
				cout << "디지몬이 존재하지 않습니다!!" << endl;
			else
				pPlayer->GetDigimon()->Render();
			system("pause");
			break;
		case 6:
			return;
		}
	}
}

int MapSnow::OutputMap()
{
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(ObjectManager)->FindObject("Player");
	pPlayer->GetDigimon()->SetIsDie(false);
	pPlayer->GetDigimon()->MaxHp();
	while (true)
	{
		system("cls");
		cout << "현재 위치 : " << strMapName << endl;
		cout << "1. 전투" << endl;
		cout << "2. 상점" << endl;
		cout << "3. 인벤토리 열기" << endl;
		cout << "4. 캐릭터 정보" << endl;
		cout << "5. 디지몬 정보" << endl;
		cout << "6. 닷트본부로 돌아가기" << endl;
		int iMenu = Input<int>();
		if (iMenu < 1 || iMenu > 6)
			continue;
		return iMenu;
	}
}



void MapSnow::CreateEnemy()
{
	// 적 생성
	CEnemyDigimon* pDigimon = (CEnemyDigimon*)GET_SINGLE(ObjectManager)->CloneObject("EnemyDigimon");
	pDigimon->SetDigName("베어몬");
	pDigimon->SetCharacterInfo(5, 10, 3, 5, 50, 30, 1, 0, 0, 0);
	pDigimon->SetAttributeType(3);
	pDigimon->SetEvaultionType(1);
	pDigimon->AddSKill(new Skill("할퀴기", 10, 20));
	pDigimon->AddSKill(new Skill("베어베어빔", 20, 30));
	pDigimon->UpdateEnemySkill();
	pDigimon->SetGold(4000);
	m_enemyVec.push_back(pDigimon);

	// 아이템 생성
	Item* item = new ItemEgg;
	item->SetItemInfo(IT_EGG, "베어몬의 알", 1000, 50, "베어몬의 알");
	// 2. 디지몬 스킬 목록 준비
	vector<pair<string, pair<int, int>>> skills = {
	{"콤보 펀치", {10, 20}},
	{"마하 펀치", {30, 30}},
	{"파워 슬래시", {60, 50}},
	{"슬래핑 로어", {90, 60}},
	{"하울링 크래시", {120, 100}},
	{"아이언 피스트", {180, 150}},
	{"강철의 결의", {240, 100}},
	{"스톤 크래쉬", {300, 100}},
	{"브레이브 하울", {500, 200}},
	{"퓨리어스 블로우", {800, 300}}
	};

	vector<tuple<string, int, int, int, int>> evolutions = {
	{"그리즐몬", 30, 30, 20, 20},
	{"마르스몬", 40, 40, 25, 25},
	{"반쵸레오몬", 50, 50, 30, 30},
	{"반쵸레오몬 각성모드", 60, 60, 35, 35} 
	};

	// 4. 디지몬 정보 세팅
	if (item) {
		dynamic_cast<ItemEgg*>(item)->SetDigimonInfo(
			"베어몬",
			10, 20,        // 공격력 최소, 최대
			5, 10,         // 방어력 최소, 최대
			100, 60,       // HP 최대, DS 최대
			1, 0, 0, 0,    // 레벨, 경험치, 피로도, 속도
			3,             // 속성 타입
			skills,
			evolutions
		);
	}
	pDigimon->SetItemList(item);


	item = new ItemGeneric;
	item->SetItemInfo(IT_GENERIC, "베어몬의 발바닥", 50, 1, "재료 아이템");
	pDigimon->SetItemList(item);
	digimonCount++;


	pDigimon = (CEnemyDigimon*)GET_SINGLE(ObjectManager)->CloneObject("EnemyDigimon");
	pDigimon->SetDigName("플룻트몬");
	pDigimon->SetCharacterInfo(5, 10, 3, 5, 50, 30, 1, 0, 0, 0);
	pDigimon->SetAttributeType(3);
	pDigimon->SetEvaultionType(1);
	pDigimon->AddSKill(new Skill("고양이 돈받기", 10, 20));
	pDigimon->AddSKill(new Skill("냐옹기", 20, 30));
	pDigimon->UpdateEnemySkill();
	pDigimon->SetGold(4000);
	m_enemyVec.push_back(pDigimon);

	// 아이템 생성
	item = new ItemEgg;
	item->SetItemInfo(IT_EGG, "플룻트몬의 알", 1000, 50, "플룻트몬의 알");
	// 2. 디지몬 스킬 목록 준비
	skills = {
	{"포근한 찰싹", {10, 10}},
	{"힐링 빔", {20, 15}},
	{"천사의 손길", {40, 30}},
	{"큐어 펄스", {60, 50}},
	{"프로텍트 윙", {80, 60}},
	{"엔젤 가드", {100, 70}},
	{"블레싱 스파크", {130, 80}},
	{"홀리 필드", {180, 100}},
	{"세라픽 플레어", {250, 120}},
	{"신성한 재생", {300, 150}}
	};

	evolutions = {
	{"가트몬", 30, 30, 20, 20},
	{"엔젤우몬", 40, 40, 25, 25},
	{"오파니몬", 50, 50, 30, 30},
	{"오파니몬 폴른다운 모드", 60, 60, 35, 35}
	};

	// 4. 디지몬 정보 세팅
	if (item) {
		dynamic_cast<ItemEgg*>(item)->SetDigimonInfo(
			"플룻트몬",
			10, 20,        // 공격력 최소, 최대
			5, 10,         // 방어력 최소, 최대
			100, 60,       // HP 최대, DS 최대
			1, 0, 0, 0,    // 레벨, 경험치, 피로도, 속도
			3,             // 속성 타입
			skills,
			evolutions
		);
	}
	pDigimon->SetItemList(item);


	item = new ItemGeneric;
	item->SetItemInfo(IT_GENERIC, "플룻트몬의 생선", 50, 1, "재료 아이템");
	pDigimon->SetItemList(item);
	digimonCount++;


	pDigimon = (CEnemyDigimon*)GET_SINGLE(ObjectManager)->CloneObject("EnemyDigimon");
	pDigimon->SetDigName("맘몬");
	pDigimon->SetCharacterInfo(100, 150, 50, 100, 100, 100, 25, 0, 0, 0);
	pDigimon->SetAttributeType(1);
	pDigimon->SetEvaultionType(3);
	pDigimon->AddSKill(new Skill("들이 받기", 10, 20));
	pDigimon->AddSKill(new Skill("땅가르기", 20, 30));
	pDigimon->UpdateEnemySkill();
	pDigimon->SetGold(20000);
	m_enemyVec.push_back(pDigimon);

	// 아이템 생성
	item = new ItemEgg;
	item->SetItemInfo(IT_EGG, "원시고부리몬의 알", 1000, 50, "원시고부리몬의 알");
	// 2. 디지몬 스킬 목록 준비
	skills = {
	{"방망이 휘두르기", {10, 10}},
	{"돌도끼 내리치기", {20, 20}},
	{"분노의 포효", {40, 30}},
	{"돌격 박치기", {60, 50}},
	{"광폭 연타", {80, 70}},
	{"원시의 맹공", {100, 90}},
	{"울부짖는 철퇴", {130, 100}},
	{"분쇄의 망치", {180, 120}},
	{"지옥의 맹타", {250, 150}},
	{"멸망의 일격", {300, 180}}
	};

	evolutions = {
	{"하누몬", 30, 30, 20, 20},
	{"맘몬", 40, 40, 25, 25},
	{"스컬맘몬", 50, 50, 30, 30},
	{"데니쳐맘몬", 60, 60, 35, 35}
	};

	// 4. 디지몬 정보 세팅
	if (item) {
		dynamic_cast<ItemEgg*>(item)->SetDigimonInfo(
			"원시 고부리몬",
			10, 20,        // 공격력 최소, 최대
			5, 10,         // 방어력 최소, 최대
			100, 60,       // HP 최대, DS 최대
			1, 0, 0, 0,    // 레벨, 경험치, 피로도, 속도
			3,             // 속성 타입
			skills,
			evolutions
		);
	}
	pDigimon->SetItemList(item);


	item = new ItemGeneric;
	item->SetItemInfo(IT_GENERIC, "맘몬의 가죽", 100, 1, "재료 아이템");
	pDigimon->SetItemList(item);
	digimonCount++;
}



