#include "pch.h"
#include "StoreEgg.h"
#include "ItemEgg.h"

StoreEgg::StoreEgg()
{
	ItemEgg* item = (ItemEgg*)CreateItem("아구몬의 알 ", IT_EGG, 10000, 20, "알");
	item = (ItemEgg*)CreateItem("쿠네몬의 알 ", IT_EGG, 10000, 20, "알");
	item = (ItemEgg*)CreateItem("쉬라몬의 알 ", IT_EGG, 10000, 20, "알");
	item = (ItemEgg*)CreateItem("텐타몬의 알 ", IT_EGG, 10000, 20, "알");
	item = (ItemEgg*)CreateItem("위자몬의 알 ", IT_EGG, 10000, 20, "알");

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
