#include "pch.h"
#include "MapWest.h"


MapWest::MapWest()
{
	strMapName = "���� ����";
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

int MapWest::OutputMap()
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

void MapWest::CreateEnemy()
{
	// �� ����
	CEnemyDigimon* pDigimon = (CEnemyDigimon*)GET_SINGLE(ObjectManager)->CloneObject("EnemyDigimon");
	pDigimon->SetDigName("�Ƹ�����");
	pDigimon->SetCharacterInfo(5, 10, 3, 5, 50, 30, 1, 0, 0, 0);
	pDigimon->SetAttributeType(3);
	pDigimon->SetEvaultionType(1);
	pDigimon->AddSKill(new Skill("������", 10, 20));
	pDigimon->AddSKill(new Skill("�����", 20, 30));
	pDigimon->UpdateEnemySkill();
	pDigimon->SetGold(4000);
	m_enemyVec.push_back(pDigimon);

	// ������ ����
	Item* item = new ItemEgg;
	item->SetItemInfo(IT_EGG, "�Ƹ������� ��", 1000, 50, "�Ƹ������� ��");
	// 2. ������ ��ų ��� �غ�
	vector<pair<string, pair<int, int>>> skills = {
	{"�帱 ��Ʈ����ũ", {10, 20}},         // �⺻ �帱 ����
	{"��ö �ظ�", {30, 30}},              // ���ſ� Ÿ��
	{"�Ŀ� ������", {60, 50}},            // ����
	{"�ξ� ����Ʈ", {90, 60}},            // �Ҹ�/����� ����
	{"�Ͽ︵ ����", {120, 100}},          // ���� + ����
	{"���̾� ��", {180, 0}},             // ��� ��ȭ (���� ����)
	{"���� ��ο�", {240, 100}},          // �� ����
	{"����ŷ ����", {300, 150}},         // ���� ����
	{"��ũ �巡�� ������", {500, 200}},   // �� ����ŷ�� ���
	{"������ �г�", {800, 300}}          // ������, ��ȭ ���
	};

	vector<tuple<string, int, int, int, int>> evolutions = {
	{"��׸�", 30, 30, 20, 20},
	{"����", 40, 40, 25, 25},
	{"����ŷ��", 50, 50, 30, 30},
	{"�� ����ŷ��", 60, 60, 35, 35}
	};

	// 4. ������ ���� ����
	if (item) {
		dynamic_cast<ItemEgg*>(item)->SetDigimonInfo(
			"�Ƹ�����",
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
	item->SetItemInfo(IT_GENERIC, "�Ƹ������� ���", 50, 1, "��� ������");
	pDigimon->SetItemList(item);
	digimonCount++;


	pDigimon = (CEnemyDigimon*)GET_SINGLE(ObjectManager)->CloneObject("EnemyDigimon");
	pDigimon->SetDigName("ī�޸�");
	pDigimon->SetCharacterInfo(5, 10, 3, 5, 50, 30, 1, 0, 0, 0);
	pDigimon->SetAttributeType(3);
	pDigimon->SetEvaultionType(1);
	pDigimon->AddSKill(new Skill("������", 10, 20));
	pDigimon->AddSKill(new Skill("��ӽ���", 20, 30));
	pDigimon->UpdateEnemySkill();
	pDigimon->SetGold(4000);
	m_enemyVec.push_back(pDigimon);

	// ������ ����
	item = new ItemEgg;
	item->SetItemInfo(IT_EGG, "ī�޸��� ��", 1000, 50, "ī�޸��� ��");
	// 2. ������ ��ų ��� �غ�
	skills = {
	{"��� ����", {10, 5}},                 // �⺻ ��� ��ų
	{"���� ���", {20, 15}},               // ���� �Ӽ� �⺻��
	{"���̵� �� ��", {40, 0}},             // ���� ��� (���� ����, ��� ��ȭ)
	{"���� �ĵ�", {60, 40}},               // ���� ���� ����
	{"��ũ �ǵ�", {80, 20}},               // ���� �ݻ�
	{"���̾� ��", {100, 70}},             // ���� ���� ���
	{"������ ����Ʈ", {130, 100}},         // �ٰŸ� ��Ÿ
	{"����� ���̺�", {180, 110}},         // ��ȣ+ȸ�� ���ձ�
	{"�ް� ��ũ ĳ��", {250, 130}},         // ������ ���ݱ�
	{"�ھ� ����Ʈ", {300, 150}}            // ���̾ȵ�θ� �ñ�
	};

	evolutions = {
	{"���͸�", 30, 30, 20, 20},
	{"������", 40, 40, 25, 25},
	{"�ȵ�θ�", 50, 50, 30, 30},
	{"���̾ȵ�θ�", 60, 60, 35, 35}
	};

	// 4. ������ ���� ����
	if (item) {
		dynamic_cast<ItemEgg*>(item)->SetDigimonInfo(
			"ī�޸�",
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
	item->SetItemInfo(IT_GENERIC, "ī�޸��� ���", 50, 1, "��� ������");
	pDigimon->SetItemList(item);
	digimonCount++;


	pDigimon = (CEnemyDigimon*)GET_SINGLE(ObjectManager)->CloneObject("EnemyDigimon");
	pDigimon->SetDigName("��Ÿ��");
	pDigimon->SetCharacterInfo(100, 150, 50, 100, 100, 100, 25, 0, 0, 0);
	pDigimon->SetAttributeType(1);
	pDigimon->SetEvaultionType(3);
	pDigimon->AddSKill(new Skill("��Ÿ��ġ", 10, 20));
	pDigimon->AddSKill(new Skill("��Ÿ��", 20, 30));
	pDigimon->UpdateEnemySkill();
	pDigimon->SetGold(20000);
	m_enemyVec.push_back(pDigimon);

	// ������ ����
	item = new ItemEgg;
	item->SetItemInfo(IT_EGG, "��Ÿ���� ��", 1000, 50, "��Ÿ���� ��");

	skills = {
	{"��Ÿ ��Ʈ����ũ", {10, 10}},           // �⺻ ���� ����
	{"�÷��� ��", {20, 15}},                 // �Ӽ� �� ����
	{"��� ����Ʈ", {40, 30}},               // ���� ���ϱ�
	{"����Ʈ�� Ŀ��", {60, 50}},             // ���� �ٴ���Ʈ
	{"���� ��Ÿ ����", {80, 70}},            // ���� ����
	{"��Ÿ ����Ʈ", {100, 90}},              // ���� ���� ����
	{"����ƽ ����", {130, 100}},             // ����� ��������
	{"���� ����", {180, 120}},               // ���� �迭 ���� �ñر�
	{"����Ƽ�� �극��ũ", {250, 150}},        // ����Ƽ�� ���
	{"��Ÿ ������Ʈ", {300, 180}}             // ���� ��ȭ ���� ���
	};

	evolutions = {
	{"���ý�Ÿ��", 30, 30, 20, 20},
	{"���۽�Ÿ��", 40, 40, 25, 25},
	{"����Ƽ��", 50, 50, 30, 30},
	{"ǳ�Ÿ�", 60, 60, 35, 35}
	};

	// 4. ������ ���� ����
	if (item) {
		dynamic_cast<ItemEgg*>(item)->SetDigimonInfo(
			"��Ÿ��",
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
	item->SetItemInfo(IT_GENERIC, "������ DATA", 100, 1, "��� ������");
	pDigimon->SetItemList(item);
	digimonCount++;
}


