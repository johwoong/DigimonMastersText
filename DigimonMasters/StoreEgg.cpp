#include "pch.h"
#include "StoreEgg.h"
#include "ItemEgg.h"

StoreEgg::StoreEgg()
{
	ItemEgg* item = (ItemEgg*)CreateItem("�Ʊ����� �� ", IT_EGG, 10000, 20, "��");
	item = (ItemEgg*)CreateItem("��׸��� �� ", IT_EGG, 10000, 20, "��");
	item = (ItemEgg*)CreateItem("������� �� ", IT_EGG, 10000, 20, "��");
	item = (ItemEgg*)CreateItem("��Ÿ���� �� ", IT_EGG, 10000, 20, "��");
	item = (ItemEgg*)CreateItem("���ڸ��� �� ", IT_EGG, 10000, 20, "��");

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
	cout << "******************** ������ �� ���� ******************** " << endl;
	ShowList();
    return 0;
}
