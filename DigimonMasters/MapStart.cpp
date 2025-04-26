#include "pch.h"
#include "MapStart.h"
#include "ObjectManager.h"
#include "CPlayer.h"
#include "CDigimon.h"
#include "Skill.h"


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
		switch (OutputMap())
		{
		case 1:
			Battle();
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			return;
		}
	}
}


int MapStart::OutputMap()
{
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(ObjectManager)->FindObject("Player");
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
			SkillAttack(pPlayer, m_enemyVec[random], 1);
			system("pause");
			break;
		case 3:
			SkillAttack(pPlayer, m_enemyVec[random], 2);
			system("pause");
			break;
		case 4:
			m_enemyVec[random]->SetMaxHp();
			return;
		}
	}
}

void MapStart::GenericAttack(CPlayer* player, CDigimon* digimon)
{
	int iDamage = player->GetDigimon()->GetDamage() - digimon->GetArmor();
	iDamage = iDamage < 1 ? 1 : iDamage;


	cout << player->GetDigimon()->GetDigName() << "�� " << digimon->GetDigName() << "���� "
		<< iDamage << " ���ظ� �־����ϴ�." << endl;
	if (!digimon->Damage(iDamage))
		cout << "��Ʈ�� �������� ���������ϴ�...." << endl;

	iDamage = digimon->GetDamage() -player->GetDigimon()->GetArmor();
	iDamage = iDamage < 1 ? 1 : iDamage;

	cout << digimon->GetDigName() << "�� " << player->GetDigimon()->GetDigName() << "���� "
		<< iDamage << " ���ظ� �־����ϴ�." << endl;

	if (!digimon->Damage(iDamage))
	{
		cout << digimon->GetDigName() << "�� ��ġ�����ϴ�!!." << endl;
		digimon->SetMaxHp();
		player->AddExp(2);
		player->GetDigimon()->AddExp(10);
		return;
	}

}

void MapStart::SkillAttack(CPlayer* player, CDigimon* digimon, int num)
{
	int skillDamage = 0;
	switch (num)
	{
	case 1:
		// ��ų 1�� ���
		skillDamage = player->GetDigimon()->GetSkillList()[0]->GetSkillDamage();

		cout << player->GetDigimon()->GetDigName() << "�� " << player->GetDigimon()->GetSkillList()[0]->GetSkillName() << "!!" << endl;

		cout << player->GetDigimon()->GetDigName() << "�� " << digimon->GetDigName() << "���� "
			<< skillDamage << " ���ظ� �־����ϴ�." << endl;
		if (!digimon->Damage(skillDamage))
		{
			cout << digimon->GetDigName() << "�� ��ġ�����ϴ�!!." << endl;
			digimon->SetMaxHp();
			player->AddExp(2);
			player->GetDigimon()->AddExp(10);
			return;
		}
		break;
	case 2:
		// ��ų 2�� ���
		skillDamage = player->GetDigimon()->GetSkillList()[1]->GetSkillDamage();
		cout << player->GetDigimon()->GetDigName() << "�� " << player->GetDigimon()->GetSkillList()[1]->GetSkillName() << "!!" << endl;

		cout << player->GetDigimon()->GetDigName() << "�� " << digimon->GetDigName() << "���� "
			<< skillDamage << " ���ظ� �־����ϴ�." << endl;
		if (!digimon->Damage(skillDamage))
		{
			cout << digimon->GetDigName() << "�� ��ġ�����ϴ�!!." << endl;
			digimon->SetMaxHp();
			player->AddExp(2);
			player->GetDigimon()->AddExp(10);
			return;
		}
		break;
	}
}

void MapStart::CreateEnemy()
{
	CDigimon* pDigimon = (CDigimon*)GET_SINGLE(ObjectManager)->CloneObject("EnemyDigimon");
	pDigimon->SetDigName("�θ���");
	pDigimon->SetCharacterInfo(5, 10, 3, 5, 50, 30, 1, 0, 0, 0);
	pDigimon->SetEvalutionType(1);
	pDigimon->SetAttributeType(3);
	pDigimon->AddSKill(new Skill("���� �ı�", 10, 20));
	pDigimon->AddSKill(new Skill("�Ե帱", 10, 30));
	m_enemyVec.push_back(pDigimon);
	digimonCount++;

	pDigimon = (CDigimon*)GET_SINGLE(ObjectManager)->CloneObject("EnemyDigimon");
	pDigimon->SetDigName("�ȸ�");
	pDigimon->SetCharacterInfo(5, 10, 3, 5, 50, 30, 1, 0, 0, 0);
	pDigimon->SetEvalutionType(1);
	pDigimon->SetAttributeType(3);
	pDigimon->AddSKill(new Skill("�Ѹ� ä��", 10, 20));
	pDigimon->AddSKill(new Skill("���", 10, 20));
	m_enemyVec.push_back(pDigimon);
	digimonCount++;

	pDigimon = (CDigimon*)GET_SINGLE(ObjectManager)->CloneObject("EnemyDigimon");
	pDigimon->SetDigName("������");
	pDigimon->SetCharacterInfo(5, 10, 3, 5, 50, 30, 1, 0);
	pDigimon->SetEvalutionType(1);
	pDigimon->SetAttributeType(3);
	pDigimon->AddSKill(new Skill("����� �Ҳ�", 10, 20));
	pDigimon->AddSKill(new Skill("����", 10, 20));
	m_enemyVec.push_back(pDigimon);
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
		cout << "2. ��ų1��" << endl;
		cout << "3. ��ų2��" << endl;
		cout << "4. ����" << endl;
		int input = Input<int>();
		if (input < 1 || input > 4)
			continue;
		return input;
	}
}

