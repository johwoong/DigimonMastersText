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
			system("pause");
			break;
		case 4:
			SkillAttack(pPlayer, m_enemyVec[random], 2);
			system("pause");
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
		break;
	case 2:
		// ��ų 2�� ���
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
			return;
		}
		break;
	}
}


void MapStart::CreateEnemy()
{
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
	Item* item = new ItemEgg;
	item->SetItemInfo(IT_EGG, "�θ����� ��", 1000, 50, "�θ����� ��");
	pDigimon->SetItemList(item);
	item = new ItemGeneric;
	item->SetItemInfo(IT_GENERIC, "�θ����� ��", 50, 1, "��� ������");
	pDigimon->SetItemList(item);
	digimonCount++;

	pDigimon = (CEnemyDigimon*)GET_SINGLE(ObjectManager)->CloneObject("EnemyDigimon");
	pDigimon->SetDigName("������");
	pDigimon->SetCharacterInfo(5, 10, 3, 5, 50, 30, 1, 0, 0, 0);
	pDigimon->SetAttributeType(3);
	pDigimon->SetEvaultionType(1);
	pDigimon->AddSKill(new Skill("��ġ��", 10, 20));
	pDigimon->AddSKill(new Skill("���� ��ġ", 10, 30));
	pDigimon->UpdateEnemySkill();
	m_enemyVec.push_back(pDigimon);
	pDigimon->SetGold(300);
	item = new ItemEgg;
	item->SetItemInfo(IT_EGG, "�������� ��", 1000, 50, "������ ��");
	pDigimon->SetItemList(item);
	item = new ItemGeneric;
	item->SetItemInfo(IT_GENERIC, "�����Ǹ��� ��", 50, 1, "��� ������");
	pDigimon->SetItemList(item);
	digimonCount++;

	pDigimon = (CEnemyDigimon*)GET_SINGLE(ObjectManager)->CloneObject("EnemyDigimon");
	pDigimon->SetDigName("�õ���");
	pDigimon->SetCharacterInfo(30, 50, 10, 15, 50, 30, 1, 0, 0, 0);
	pDigimon->SetAttributeType(1);
	pDigimon->SetEvaultionType(2);
	pDigimon->AddSKill(new Skill("���� �ͼ�", 50, 20));
	pDigimon->AddSKill(new Skill("���� ��", 20, 30));
	pDigimon->UpdateEnemySkill();
	m_enemyVec.push_back(pDigimon);
	pDigimon->SetGold(300);
	item = new ItemEgg;
	item->SetItemInfo(IT_EGG, "��Ÿ���� ��", 1000, 50, "��Ÿ���� ��");
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

