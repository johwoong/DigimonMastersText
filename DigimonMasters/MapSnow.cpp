#include "pch.h"
#include "MapSnow.h"


MapSnow::MapSnow() : MapStart()
{
    strMapName = "������ ����";
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
				cout << "�������� �������� �ʽ��ϴ�!!" << endl;
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
		cout << "���� ��ġ : " << strMapName << endl;
		cout << "1. ����" << endl;
		cout << "2. ����" << endl;
		cout << "3. �κ��丮 ����" << endl;
		cout << "4. ĳ���� ����" << endl;
		cout << "5. ������ ����" << endl;
		cout << "6. ��Ʈ���η� ���ư���" << endl;
		int iMenu = Input<int>();
		if (iMenu < 1 || iMenu > 6)
			continue;
		return iMenu;
	}
}



void MapSnow::CreateEnemy()
{
	// �� ����
	CEnemyDigimon* pDigimon = (CEnemyDigimon*)GET_SINGLE(ObjectManager)->CloneObject("EnemyDigimon");
	pDigimon->SetDigName("�����");
	pDigimon->SetCharacterInfo(5, 10, 3, 5, 50, 30, 1, 0, 0, 0);
	pDigimon->SetAttributeType(3);
	pDigimon->SetEvaultionType(1);
	pDigimon->AddSKill(new Skill("������", 10, 20));
	pDigimon->AddSKill(new Skill("������", 20, 30));
	pDigimon->UpdateEnemySkill();
	pDigimon->SetGold(4000);
	m_enemyVec.push_back(pDigimon);

	// ������ ����
	Item* item = new ItemEgg;
	item->SetItemInfo(IT_EGG, "������� ��", 1000, 50, "������� ��");
	// 2. ������ ��ų ��� �غ�
	vector<pair<string, pair<int, int>>> skills = {
	{"�޺� ��ġ", {10, 20}},
	{"���� ��ġ", {30, 30}},
	{"�Ŀ� ������", {60, 50}},
	{"������ �ξ�", {90, 60}},
	{"�Ͽ︵ ũ����", {120, 100}},
	{"���̾� �ǽ�Ʈ", {180, 150}},
	{"��ö�� ����", {240, 100}},
	{"���� ũ����", {300, 100}},
	{"�극�̺� �Ͽ�", {500, 200}},
	{"ǻ��� ��ο�", {800, 300}}
	};

	vector<tuple<string, int, int, int, int>> evolutions = {
	{"�׸����", 30, 30, 20, 20},
	{"��������", 40, 40, 25, 25},
	{"���ݷ�����", 50, 50, 30, 30},
	{"���ݷ����� �������", 60, 60, 35, 35} 
	};

	// 4. ������ ���� ����
	if (item) {
		dynamic_cast<ItemEgg*>(item)->SetDigimonInfo(
			"�����",
			10, 20,        // ���ݷ� �ּ�, �ִ�
			5, 10,         // ���� �ּ�, �ִ�
			100, 60,       // HP �ִ�, DS �ִ�
			1, 0, 0, 0,    // ����, ����ġ, �Ƿε�, �ӵ�
			3,             // �Ӽ� Ÿ��
			skills,
			evolutions
		);
	}
	pDigimon->SetItemList(item);


	item = new ItemGeneric;
	item->SetItemInfo(IT_GENERIC, "������� �߹ٴ�", 50, 1, "��� ������");
	pDigimon->SetItemList(item);
	digimonCount++;


	pDigimon = (CEnemyDigimon*)GET_SINGLE(ObjectManager)->CloneObject("EnemyDigimon");
	pDigimon->SetDigName("�÷�Ʈ��");
	pDigimon->SetCharacterInfo(5, 10, 3, 5, 50, 30, 1, 0, 0, 0);
	pDigimon->SetAttributeType(3);
	pDigimon->SetEvaultionType(1);
	pDigimon->AddSKill(new Skill("����� ���ޱ�", 10, 20));
	pDigimon->AddSKill(new Skill("�Ŀ˱�", 20, 30));
	pDigimon->UpdateEnemySkill();
	pDigimon->SetGold(4000);
	m_enemyVec.push_back(pDigimon);

	// ������ ����
	item = new ItemEgg;
	item->SetItemInfo(IT_EGG, "�÷�Ʈ���� ��", 1000, 50, "�÷�Ʈ���� ��");
	// 2. ������ ��ų ��� �غ�
	skills = {
	{"������ ����", {10, 10}},
	{"���� ��", {20, 15}},
	{"õ���� �ձ�", {40, 30}},
	{"ť�� �޽�", {60, 50}},
	{"������Ʈ ��", {80, 60}},
	{"���� ����", {100, 70}},
	{"���� ����ũ", {130, 80}},
	{"Ȧ�� �ʵ�", {180, 100}},
	{"������ �÷���", {250, 120}},
	{"�ż��� ���", {300, 150}}
	};

	evolutions = {
	{"��Ʈ��", 30, 30, 20, 20},
	{"�������", 40, 40, 25, 25},
	{"���Ĵϸ�", 50, 50, 30, 30},
	{"���Ĵϸ� �����ٿ� ���", 60, 60, 35, 35}
	};

	// 4. ������ ���� ����
	if (item) {
		dynamic_cast<ItemEgg*>(item)->SetDigimonInfo(
			"�÷�Ʈ��",
			10, 20,        // ���ݷ� �ּ�, �ִ�
			5, 10,         // ���� �ּ�, �ִ�
			100, 60,       // HP �ִ�, DS �ִ�
			1, 0, 0, 0,    // ����, ����ġ, �Ƿε�, �ӵ�
			3,             // �Ӽ� Ÿ��
			skills,
			evolutions
		);
	}
	pDigimon->SetItemList(item);


	item = new ItemGeneric;
	item->SetItemInfo(IT_GENERIC, "�÷�Ʈ���� ����", 50, 1, "��� ������");
	pDigimon->SetItemList(item);
	digimonCount++;


	pDigimon = (CEnemyDigimon*)GET_SINGLE(ObjectManager)->CloneObject("EnemyDigimon");
	pDigimon->SetDigName("����");
	pDigimon->SetCharacterInfo(100, 150, 50, 100, 100, 100, 25, 0, 0, 0);
	pDigimon->SetAttributeType(1);
	pDigimon->SetEvaultionType(3);
	pDigimon->AddSKill(new Skill("���� �ޱ�", 10, 20));
	pDigimon->AddSKill(new Skill("��������", 20, 30));
	pDigimon->UpdateEnemySkill();
	pDigimon->SetGold(20000);
	m_enemyVec.push_back(pDigimon);

	// ������ ����
	item = new ItemEgg;
	item->SetItemInfo(IT_EGG, "���ð�θ����� ��", 1000, 50, "���ð�θ����� ��");
	// 2. ������ ��ų ��� �غ�
	skills = {
	{"����� �ֵθ���", {10, 10}},
	{"������ ����ġ��", {20, 20}},
	{"�г��� ��ȿ", {40, 30}},
	{"���� ��ġ��", {60, 50}},
	{"���� ��Ÿ", {80, 70}},
	{"������ �Ͱ�", {100, 90}},
	{"���¢�� ö��", {130, 100}},
	{"�м��� ��ġ", {180, 120}},
	{"������ ��Ÿ", {250, 150}},
	{"����� �ϰ�", {300, 180}}
	};

	evolutions = {
	{"�ϴ���", 30, 30, 20, 20},
	{"����", 40, 40, 25, 25},
	{"���ø���", 50, 50, 30, 30},
	{"�����ĸ���", 60, 60, 35, 35}
	};

	// 4. ������ ���� ����
	if (item) {
		dynamic_cast<ItemEgg*>(item)->SetDigimonInfo(
			"���� ��θ���",
			10, 20,        // ���ݷ� �ּ�, �ִ�
			5, 10,         // ���� �ּ�, �ִ�
			100, 60,       // HP �ִ�, DS �ִ�
			1, 0, 0, 0,    // ����, ����ġ, �Ƿε�, �ӵ�
			3,             // �Ӽ� Ÿ��
			skills,
			evolutions
		);
	}
	pDigimon->SetItemList(item);


	item = new ItemGeneric;
	item->SetItemInfo(IT_GENERIC, "������ ����", 100, 1, "��� ������");
	pDigimon->SetItemList(item);
	digimonCount++;
}



