#include "pch.h"
#include "StoreGeneric.h"
#include "ItemGeneric.h"

StoreGeneric::StoreGeneric()
{
	ItemGeneric* item = (ItemGeneric*)CreateItem("체력 포션 ", IT_GENERIC, 500, 20, "체력을 10채워줌");
	item = (ItemGeneric*)CreateItem("DS 포션 ", IT_GENERIC, 500, 20, "DS를 10채워줌");
}

StoreGeneric::~StoreGeneric()
{

}

void StoreGeneric::Update()
{
	OutputMenu();
}

int StoreGeneric::OutputMenu()
{
	cout << "********************  일반 상점 ******************** " << endl;
	ShowList();
	return 0;
}
