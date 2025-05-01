#include "pch.h"
#include "MapStart.h"
#include "ObjectManager.h"
#include "Inventory.h"
#include "StoreManager.h"
#include "CPlayer.h"
#include "CEnemyDigimon.h"
#include "Skill.h"
#include "ItemEgg.h"
#include "ItemGeneric.h"


MapStart::MapStart() : digimonCount(0)
{
	strMapName = "������ ����";
}
MapStart::~MapStart()
{

}

bool MapStart::Init()
{
	CreateEnemy();
	return true;
}

void MapStart::Update()
{
	while (true)
	{
		CPlayer* pPlayer = (CPlayer*)GET_SINGLE(ObjectManager)->FindObject("Player");
		switch (OutputMap())
		{
		case 1:
			Battle();
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


int MapStart::OutputMap()
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

void MapStart::Battle()
{
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(ObjectManager)->FindObject("Player");
	int random = rand() % digimonCount;
	cout << "������ �����մϴ�. " << endl;
	while (true)
	{
		if (pPlayer->GetDigimon()->GetIsDie() == true)
		{
			return;
		}
		system("cls");
		Render();
		m_enemyVec[random]->Render();
		switch (OutputBattleMenu())
		{
		case 1:
			GenericAttack(pPlayer, m_enemyVec[random]);
			system("pause");
			break;
		case 2:
			switch (OutputEvoutuionMenu())
			{
			case 1:
				pPlayer->GetDigimon()->Ev_Maturity();
				break;
			case 2:
				pPlayer->GetDigimon()->Ev_Integer();
				break;
			case 3:
				pPlayer->GetDigimon()->Ev_Ultimat();
				break;
			case 4:
				pPlayer->GetDigimon()->EV_Super();
				break;
			case 5:
				pPlayer->GetDigimon()->Unevolve();
				break;
			case 6:
				return;
			}
			break;
		case 3:
			SkillAttack(pPlayer, m_enemyVec[random], 1);
			break;
		case 4:
			SkillAttack(pPlayer, m_enemyVec[random], 2);
			break;
		case 5:
			m_enemyVec[random]->SetMaxHp();
			return;
		}
	}
}

void MapStart::GenericAttack(CPlayer* player, CEnemyDigimon* digimon)
{
	int iDamage = player->GetDigimon()->GetDamage() - digimon->GetArmor();
	iDamage = iDamage < 1 ? 1 : iDamage;


	cout << player->GetDigimon()->GetDigName() << "�� " << digimon->GetDigName() << "���� "
		<< iDamage << " ���ظ� �־����ϴ�." << endl;
	if (!digimon->Damage(iDamage))
	{
		cout << digimon->GetDigName() << "�� ��ġ�����ϴ�!!." << endl;
		digimon->SetMaxHp();
		digimon->DropItem();
		player->AddExp(2);
		player->GetDigimon()->AddExp(10);
		return;
	}

	iDamage = player->GetDigimon()->GetDamage() - digimon->GetArmor();
	iDamage = iDamage < 1 ? 1 : iDamage;

	cout << digimon->GetDigName() << "�� " << player->GetDigimon()->GetDigName() << "���� "
		<< iDamage << " ���ظ� �־����ϴ�." << endl;

	if (!player->GetDigimon()->Damage(iDamage))
	{
		player->GetDigimon()->SetIsDie(true);
		cout << "��Ʈ�� �������� ���������ϴ�...." << endl;
		cout << "������ ���ư��ϴ�.." << endl;
		return;
	}
}

void MapStart::SkillAttack(CPlayer* player, CEnemyDigimon* digimon, int num)
{
	int skillDamage = 0;
	switch (num)
	{
	case 1:
		// ��ų 1�� ���
		if (player->GetDigimon()->GetCharacterInfo().iDs <= 0)
		{
			player->GetDigimon()->SetDsZero();
			cout << "DS�� �����մϴ�." << endl;
			system("pause");
			return;
		}
		player->GetDigimon()->MinusDs(player->GetDigimon()->GetUseSkillList()[0]->minusDs);
		skillDamage = player->GetDigimon()->GetUseSkillList()[0]->GetSkillDamage();

		cout << player->GetDigimon()->GetDigName() << "�� " << player->GetDigimon()->GetUseSkillList()[0]->GetSkillName() << "!!" << endl;

		cout << player->GetDigimon()->GetDigName() << "�� " << digimon->GetDigName() << "���� "
			<< skillDamage << " ���ظ� �־����ϴ�." << endl;

		if (!digimon->Damage(skillDamage))
		{
			cout << digimon->GetDigName() << "�� ��ġ�����ϴ�!!." << endl;
			digimon->SetMaxHp();
			digimon->DropItem();
			player->AddExp(2);
			player->GetDigimon()->AddExp(10);
			return;
		}
		system("pause");
		break;
	case 2:
		// ��ų 2�� ���
		if (player->GetDigimon()->GetCharacterInfo().iDs <= 0)
		{
			player->GetDigimon()->SetDsZero();
			cout << "DS�� �����մϴ�." << endl;
			return;
		}
		player->GetDigimon()->MinusDs(player->GetDigimon()->GetUseSkillList()[0]->minusDs);
		skillDamage = player->GetDigimon()->GetUseSkillList()[1]->GetSkillDamage();
		cout << player->GetDigimon()->GetDigName() << "�� " << player->GetDigimon()->GetUseSkillList()[1]->GetSkillName() << "!!" << endl;

		cout << player->GetDigimon()->GetDigName() << "�� " << digimon->GetDigName() << "���� "
			<< skillDamage << " ���ظ� �־����ϴ�." << endl;
		if (!digimon->Damage(skillDamage))
		{
			cout << digimon->GetDigName() << "�� ��ġ�����ϴ�!!." << endl;
			digimon->SetMaxHp();
			digimon->DropItem();
			player->AddExp(2);
			player->GetDigimon()->AddExp(10);
			system("pause");
			return;
		}
		system("pause");
		break;
	}
}


void MapStart::CreateEnemy()
{
	// �� ����
	CEnemyDigimon* pDigimon = (CEnemyDigimon*)GET_SINGLE(ObjectManager)->CloneObject("EnemyDigimon");
	pDigimon->SetDigName("�θ���");
	pDigimon->SetCharacterInfo(5, 10, 3, 5, 50, 30, 1, 0, 0, 0);
	pDigimon->SetAttributeType(3);
	pDigimon->SetEvaultionType(1);
	pDigimon->AddSKill(new Skill("���� �ı�", 10, 20));
	pDigimon->AddSKill(new Skill("�Ե帱", 10, 30));
	pDigimon->UpdateEnemySkill();
	m_enemyVec.push_back(pDigimon);
	pDigimon->SetGold(300);

	// ������ ����
	Item* item = new ItemEgg;
	item->SetItemInfo(IT_EGG, "�θ����� ��", 1000, 50, "�θ����� ��");
	// 2. ������ ��ų ��� �غ�
	vector<pair<string, pair<int, int>>> skills = {
		{"�����ı�", {10, 20}},
		{"�Ե帱", {50, 50}},
		{"��� ����", {100, 150}},
		{"�� ũ��", {100, 100}},
		{"���ü�� ���", {100, 200}},
		{"����Ʈ �ǵ�", {200, 400}},
		{"ī�� ���̽�Ʈ", {300, 100}},
		{"����� ����", {600, 100}},
		{"�� ����", {1000, 100}},
		{"���� ����", {2000, 500}}
	};

	// 3. ������ ��ȭ ��� �غ�
	vector<tuple<string, int, int, int, int>> evolutions = {
		{"��׸�", 30, 30, 20, 20},
		{"��ź��", 30, 30, 20, 20},
		{"���� �ȵ�θ�", 30, 30, 20, 20},
		{"ũ���Ͼ���", 30, 30, 20, 20}
	};

	// 4. ������ ���� ����
	if (item) {
		dynamic_cast<ItemEgg*>(item)->SetDigimonInfo(
			"�θ���",
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
	item->SetItemInfo(IT_GENERIC, "�θ����� ��", 50, 1, "��� ������");
	pDigimon->SetItemList(item);
	digimonCount++;



	// �� ����
	pDigimon = (CEnemyDigimon*)GET_SINGLE(ObjectManager)->CloneObject("EnemyDigimon");
	pDigimon->SetDigName("������");
	pDigimon->SetCharacterInfo(5, 10, 3, 5, 50, 30, 1, 0, 0, 0);
	pDigimon->SetAttributeType(3);
	pDigimon->SetEvaultionType(1);
	pDigimon->AddSKill(new Skill("����Ʈ ���� ���̾�", 10, 20));
	pDigimon->AddSKill(new Skill("��ȯ", 10, 30));
	pDigimon->UpdateEnemySkill();
	m_enemyVec.push_back(pDigimon);
	pDigimon->SetGold(300);

	// ������ ����
	item = new ItemEgg;
	item->SetItemInfo(IT_EGG, "�������� ��", 1000, 50, "�θ����� ��");
	// 2. ������ ��ų ��� �غ�
	skills = {
		{"����Ʈ ���� ���̾�", {10, 20}},
		{"��ȯ", {50, 50}},
		{"��ũ ����Ʈ", {100, 150}},
		{"������ �÷���", {100, 100}},
		{"���� ����Ʈ", {100, 200}},
		{"��ũ �ǵ�", {200, 400}},
		{"ī���� ī��", {300, 100}},
		{"����� ����", {600, 100}},
		{"���� ��", {1000, 100}},
		{"��ũ ������", {2000, 500}}
	};

	// 3. ������ ��ȭ ��� �غ�
	evolutions = {
		{"���̽������", 30, 30, 20, 20},
		{"���û�ź��", 30, 30, 20, 20},
		{"���������", 30, 30, 20, 20},
		{"��������� �����͸��", 30, 30, 20, 20}
	};

	// 4. ������ ���� ����
	if (item) {
		dynamic_cast<ItemEgg*>(item)->SetDigimonInfo(
			"������",
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
	item->SetItemInfo(IT_GENERIC, "�����Ǹ��� ��ȥ", 50, 1, "��� ������");
	pDigimon->SetItemList(item);
	digimonCount++;

	// �� ����
	pDigimon = (CEnemyDigimon*)GET_SINGLE(ObjectManager)->CloneObject("EnemyDigimon");
	pDigimon->SetDigName("�õ���");
	pDigimon->SetCharacterInfo(5, 10, 3, 5, 50, 30, 1, 0, 0, 0);
	pDigimon->SetAttributeType(1);
	pDigimon->SetEvaultionType(2);
	pDigimon->AddSKill(new Skill("���� ��Ʈ", 10, 20));
	pDigimon->AddSKill(new Skill("���� ����", 10, 30));
	pDigimon->UpdateEnemySkill();
	m_enemyVec.push_back(pDigimon);
	pDigimon->SetGold(300);

	// ������ ����
	item = new ItemEgg;
	item->SetItemInfo(IT_EGG, "��Ÿ���� ��", 1000, 50, "��Ÿ���� ��");
	// 2. ������ ��ų ��� �غ�
	skills = {
		{"�Ϸ�Ʈ ��Ŀ", {10, 20}},
		{"���� ����", {50, 50}},
		{"���� ��Ʈ", {100, 150}},
		{"���� ����", {100, 100}},
		{"���� �����", {100, 200}},
		{"��� ��ȣ��", {200, 400}},
		{"��� ���̺�", {300, 100}},
		{"���̵�� ������", {600, 100}},
		{"������", {1000, 100}},
		{"������ �г�", {2000, 500}}
	};

	// 3. ������ ��ȭ ��� �غ�
	evolutions = {
		{"�õ���", 30, 30, 20, 20},
		{"�ް��õ���", 30, 30, 20, 20},
		{"��Ż�õ���", 30, 30, 20, 20},
		{"������ �õ���", 30, 30, 20, 20}
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
	item->SetItemInfo(IT_GENERIC, "�õ����� ���", 50, 1, "��� ������");
	pDigimon->SetItemList(item);
	digimonCount++;





}

void MapStart::Render()
{
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(ObjectManager)->FindObject("Player");
	pPlayer->GetDigimon()->Render();
	cout << endl << endl;
}

int MapStart::OutputBattleMenu()
{
	while (true)
	{
		cout << "1. ����" << endl;
		cout << "2. ��ȭ" << endl;
		cout << "3. ��ų1��" << endl;
		cout << "4. ��ų2��" << endl;
		cout << "5. ����" << endl;
		int input = Input<int>();
		if (input < 1 || input > 5)
			continue;
		return input;
	}
}

int MapStart::OutputEvoutuionMenu()
{
	while (true)
	{
		system("cls");
		cout << "1. ������" << endl;
		cout << "2. ����ü" << endl;
		cout << "3. �ñ�ü" << endl;
		cout << "4. �ʱñ�ü" << endl;
		cout << "5. ��ȭ����" << endl;
		cout << "6. �ڷΰ���" << endl;
		int input = Input<int>();
		if (input < 1 || input > 6)
			continue;
		return input;
	}
}

