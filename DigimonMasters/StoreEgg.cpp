#include "pch.h"
#include "StoreEgg.h"
#include "ItemEgg.h"

StoreEgg::StoreEgg()
{

    // 1. 알 아이템 생성
	ItemEgg* item = (ItemEgg*)CreateItem("파닥몬의 알 ", IT_EGG, 10000, 20, "알");

    // 2. 디지몬 스킬 목록 준비
    vector<pair<string, pair<int, int>>> skills = {
        {"에어 샷", {10, 20}},
        {"공기 팡", {50, 50}},
        {"엔젤 펀치", {100, 150}},
        {"엔젤 봉", {100, 100}},
        {"천공의 검", {100, 200}},
        {"라이트 실드", {200, 400}},
        {"빛의 심판", {300, 100}},
        {"라이트검", {600, 100}},
        {"어둠 화살", {1000, 100}},
        {"빛의 방패", {2000, 500}}
    };

    // 3. 디지몬 진화 목록 준비
    vector<tuple<string, int, int, int, int>> evolutions = {
        {"엔젤몬", 30, 30, 20, 20},
        {"홀리엔젤몬", 30, 30, 20, 20},
        {"세라피몬", 30, 30, 20, 20},
        {"블랙 세라피몬", 30, 30, 20, 20}
    };

    // 4. 디지몬 정보 세팅
    if (item) {
        item->SetDigimonInfo(
            "파닥몬",
            10, 20,        // 공격력 최소, 최대
            5, 10,         // 방어력 최소, 최대
            100, 60,       // HP 최대, DS 최대
            1, 0, 0, 0,    // 레벨, 경험치, 피로도, 속도
            3,             // 속성 타입
            skills,
            evolutions
        );
    }
}

StoreEgg::~StoreEgg()
{
}

void StoreEgg::Update()
{
	OutputMenu();
}

int StoreEgg::OutputMenu()
{
	cout << "******************** 디지몬 알 상점 ******************** " << endl;
	ShowList();
    return 0;
}
