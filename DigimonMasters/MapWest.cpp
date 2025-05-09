#include "pch.h"
#include "MapWest.h"


MapWest::MapWest()
{
	strMapName = "서부 마을";
}
MapWest::~MapWest()
{
}

bool MapWest::Init()
{
	CreateEnemy();
	return true;
}

void MapWest::Update()
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

int MapWest::OutputMap()
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

void MapWest::CreateEnemy()
{
	// 적 생성
	CEnemyDigimon* pDigimon = (CEnemyDigimon*)GET_SINGLE(ObjectManager)->CloneObject("EnemyDigimon");
	pDigimon->SetDigName("아르마몬");
	pDigimon->SetCharacterInfo(5, 10, 3, 5, 50, 30, 1, 0, 0, 0);
	pDigimon->SetAttributeType(3);
	pDigimon->SetEvaultionType(1);
	pDigimon->AddSKill(new Skill("구르기", 10, 20));
	pDigimon->AddSKill(new Skill("흙놀이", 20, 30));
	pDigimon->UpdateEnemySkill();
	pDigimon->SetGold(4000);
	m_enemyVec.push_back(pDigimon);

	// 아이템 생성
	Item* item = new ItemEgg;
	item->SetItemInfo(IT_EGG, "아르마몬의 알", 1000, 50, "아르마몬의 알");
	// 2. 디지몬 스킬 목록 준비
	vector<pair<string, pair<int, int>>> skills = {
	{"드릴 스트라이크", {10, 20}},         // 기본 드릴 공격
	{"강철 해머", {30, 30}},              // 무거운 타격
	{"파워 슬래시", {60, 50}},            // 베기
	{"로어 임팩트", {90, 60}},            // 소리/충격파 공격
	{"하울링 어택", {120, 100}},          // 고함 + 공격
	{"아이언 월", {180, 0}},             // 방어 강화 (피해 없음)
	{"스톤 블로우", {240, 100}},          // 돌 공격
	{"바이킹 러쉬", {300, 150}},         // 연속 돌진
	{"다크 드래곤 슬래시", {500, 200}},   // 블랙 바이킹몬 기술
	{"오딘의 분노", {800, 300}}          // 최종기, 신화 기반
	};

	vector<tuple<string, int, int, int, int>> evolutions = {
	{"디그몬", 30, 30, 20, 20},
	{"토우몬", 40, 40, 25, 25},
	{"바이킹몬", 50, 50, 30, 30},
	{"블랙 바이킹몬", 60, 60, 35, 35}
	};

	// 4. 디지몬 정보 세팅
	if (item) {
		dynamic_cast<ItemEgg*>(item)->SetDigimonInfo(
			"아르마몬",
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
	item->SetItemInfo(IT_GENERIC, "아르마몬의 등껍질", 50, 1, "재료 아이템");
	pDigimon->SetItemList(item);
	digimonCount++;


	pDigimon = (CEnemyDigimon*)GET_SINGLE(ObjectManager)->CloneObject("EnemyDigimon");
	pDigimon->SetDigName("카메몬");
	pDigimon->SetCharacterInfo(5, 10, 3, 5, 50, 30, 1, 0, 0, 0);
	pDigimon->SetAttributeType(3);
	pDigimon->SetEvaultionType(1);
	pDigimon->AddSKill(new Skill("물대포", 10, 20));
	pDigimon->AddSKill(new Skill("고속스핀", 20, 30));
	pDigimon->UpdateEnemySkill();
	pDigimon->SetGold(4000);
	m_enemyVec.push_back(pDigimon);

	// 아이템 생성
	item = new ItemEgg;
	item->SetItemInfo(IT_EGG, "카메몬의 알", 1000, 50, "카메몬의 알");
	// 2. 디지몬 스킬 목록 준비
	skills = {
	{"방어 껍질", {10, 5}},                 // 기본 방어 스킬
	{"전기 충격", {20, 15}},               // 전기 속성 기본기
	{"하이드 인 셸", {40, 0}},             // 완전 방어 (피해 없음, 방어 강화)
	{"전격 파동", {60, 40}},               // 범위 전기 공격
	{"쇼크 실드", {80, 20}},               // 공격 반사
	{"아이언 셸", {100, 70}},             // 방어력 대폭 상승
	{"레이저 바이트", {130, 100}},         // 근거리 강타
	{"가디언 웨이브", {180, 110}},         // 보호+회복 복합기
	{"메가 쇼크 캐논", {250, 130}},         // 강력한 전격기
	{"코어 버스트", {300, 150}}            // 하이안드로몬 궁극
	};

	evolutions = {
	{"가와몬", 30, 30, 20, 20},
	{"가드라몬", 40, 40, 25, 25},
	{"안드로몬", 50, 50, 30, 30},
	{"하이안드로몬", 60, 60, 35, 35}
	};

	// 4. 디지몬 정보 세팅
	if (item) {
		dynamic_cast<ItemEgg*>(item)->SetDigimonInfo(
			"카메몬",
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
	item->SetItemInfo(IT_GENERIC, "카메몬의 등껍질", 50, 1, "재료 아이템");
	pDigimon->SetItemList(item);
	digimonCount++;


	pDigimon = (CEnemyDigimon*)GET_SINGLE(ObjectManager)->CloneObject("EnemyDigimon");
	pDigimon->SetDigName("스타몬");
	pDigimon->SetCharacterInfo(100, 150, 50, 100, 100, 100, 25, 0, 0, 0);
	pDigimon->SetAttributeType(1);
	pDigimon->SetEvaultionType(3);
	pDigimon->AddSKill(new Skill("스타펀치", 10, 20));
	pDigimon->AddSKill(new Skill("스타빔", 20, 30));
	pDigimon->UpdateEnemySkill();
	pDigimon->SetGold(20000);
	m_enemyVec.push_back(pDigimon);

	// 아이템 생성
	item = new ItemEgg;
	item->SetItemInfo(IT_EGG, "스타몬의 알", 1000, 50, "스타몬의 알");

	skills = {
	{"스타 스트라이크", {10, 10}},           // 기본 광속 공격
	{"플래시 빔", {20, 15}},                 // 속성 빛 광선
	{"썬더 임팩트", {40, 30}},               // 광속 단일기
	{"라이트닝 커터", {60, 50}},             // 빠른 다단히트
	{"슈팅 스타 어택", {80, 70}},            // 연속 공격
	{"스타 버스트", {100, 90}},              // 범위 광속 폭발
	{"갤럭틱 레이", {130, 100}},             // 고출력 에너지빔
	{"빛의 심판", {180, 120}},               // 마법 계열 광속 궁극기
	{"저스티스 브레이크", {250, 150}},        // 저스티몬 기술
	{"스타 저지먼트", {300, 180}}             // 최종 진화 전용 기술
	};

	evolutions = {
	{"슈팅스타몬", 30, 30, 20, 20},
	{"슈퍼스타몬", 40, 40, 25, 25},
	{"저스티몬", 50, 50, 30, 30},
	{"풍신몬", 60, 60, 35, 35}
	};

	// 4. 디지몬 정보 세팅
	if (item) {
		dynamic_cast<ItemEgg*>(item)->SetDigimonInfo(
			"스타몬",
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
	item->SetItemInfo(IT_GENERIC, "광석형 DATA", 100, 1, "재료 아이템");
	pDigimon->SetItemList(item);
	digimonCount++;
}


