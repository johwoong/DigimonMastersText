#include "pch.h"
#include "StoreEgg.h"
#include "ItemEgg.h"

StoreEgg::StoreEgg()
{

    // 1. �� ������ ����
	ItemEgg* item = (ItemEgg*)CreateItem("�Ĵڸ��� �� ", IT_EGG, 10000, 20, "��");

    // 2. ������ ��ų ��� �غ�
    vector<pair<string, pair<int, int>>> skills = {
        {"���� ��", {10, 20}},
        {"���� ��", {50, 50}},
        {"���� ��ġ", {100, 150}},
        {"���� ��", {100, 100}},
        {"õ���� ��", {100, 200}},
        {"����Ʈ �ǵ�", {200, 400}},
        {"���� ����", {300, 100}},
        {"����Ʈ��", {600, 100}},
        {"��� ȭ��", {1000, 100}},
        {"���� ����", {2000, 500}}
    };

    // 3. ������ ��ȭ ��� �غ�
    vector<tuple<string, int, int, int, int>> evolutions = {
        {"������", 30, 30, 20, 20},
        {"Ȧ��������", 30, 30, 20, 20},
        {"�����Ǹ�", 30, 30, 20, 20},
        {"�� �����Ǹ�", 30, 30, 20, 20}
    };

    // 4. ������ ���� ����
    if (item) {
        item->SetDigimonInfo(
            "�Ĵڸ�",
            10, 20,        // ���ݷ� �ּ�, �ִ�
            5, 10,         // ���� �ּ�, �ִ�
            100, 60,       // HP �ִ�, DS �ִ�
            1, 0, 0, 0,    // ����, ����ġ, �Ƿε�, �ӵ�
            3,             // �Ӽ� Ÿ��
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
	cout << "******************** ������ �� ���� ******************** " << endl;
	ShowList();
    return 0;
}
