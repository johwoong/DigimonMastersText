#include "pch.h"
#include "StoreGeneric.h"
#include "ItemGeneric.h"

StoreGeneric::StoreGeneric()
{
	ItemGeneric* item = (ItemGeneric*)CreateItem("ü�� ���� ", IT_GENERIC, 10000, 20, "ü���� 10ä����");
	item = (ItemGeneric*)CreateItem("DS ���� ", IT_GENERIC, 10000, 20, "DS�� 10ä����");
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
	cout << "********************  �Ϲ� ���� ******************** " << endl;
	ShowList();
	return 0;
}
