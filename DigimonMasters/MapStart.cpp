#include "pch.h"
#include "MapStart.h"
#include "ObjectManager.h"
#include "CPlayer.h"
#include "CDigimon.h"
#include "Skill.h"


MapStart::MapStart() : digimonCount(0)
{
	strMapName = "시작의 마을";
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
		cout << "현재 위치 : " << strMapName << endl;
		cout << "1. 전투" << endl;
		cout << "2. 상점" << endl;
		cout << "3. 인벤토리 열기" << endl;
		cout << "4. 캐릭터 정보" << endl;
		cout << "5. 디지몬 정보" << endl;
		cout << "6. 닷트본부로 돌아가기" << endl;
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
	cout << "전투를 시작합니다. " << endl;
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


	cout << player->GetDigimon()->GetDigName() << "이 " << digimon->GetDigName() << "에게 "
		<< iDamage << " 피해를 주었습니다." << endl;
	if (!digimon->Damage(iDamage))
		cout << "파트너 디지몬이 쓰러졌습니다...." << endl;

	iDamage = digimon->GetDamage() -player->GetDigimon()->GetArmor();
	iDamage = iDamage < 1 ? 1 : iDamage;

	cout << digimon->GetDigName() << "이 " << player->GetDigimon()->GetDigName() << "에게 "
		<< iDamage << " 피해를 주었습니다." << endl;

	if (!digimon->Damage(iDamage))
	{
		cout << digimon->GetDigName() << "을 해치웠습니다!!." << endl;
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
		// 스킬 1번 사용
		skillDamage = player->GetDigimon()->GetSkillList()[0]->GetSkillDamage();

		cout << player->GetDigimon()->GetDigName() << "의 " << player->GetDigimon()->GetSkillList()[0]->GetSkillName() << "!!" << endl;

		cout << player->GetDigimon()->GetDigName() << "이 " << digimon->GetDigName() << "에게 "
			<< skillDamage << " 피해를 주었습니다." << endl;
		if (!digimon->Damage(skillDamage))
		{
			cout << digimon->GetDigName() << "을 해치웠습니다!!." << endl;
			digimon->SetMaxHp();
			player->AddExp(2);
			player->GetDigimon()->AddExp(10);
			return;
		}
		break;
	case 2:
		// 스킬 2번 사용
		skillDamage = player->GetDigimon()->GetSkillList()[1]->GetSkillDamage();
		cout << player->GetDigimon()->GetDigName() << "의 " << player->GetDigimon()->GetSkillList()[1]->GetSkillName() << "!!" << endl;

		cout << player->GetDigimon()->GetDigName() << "이 " << digimon->GetDigName() << "에게 "
			<< skillDamage << " 피해를 주었습니다." << endl;
		if (!digimon->Damage(skillDamage))
		{
			cout << digimon->GetDigName() << "을 해치웠습니다!!." << endl;
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
	pDigimon->SetDigName("두리몬");
	pDigimon->SetCharacterInfo(5, 10, 3, 5, 50, 30, 1, 0, 0, 0);
	pDigimon->SetEvalutionType(1);
	pDigimon->SetAttributeType(3);
	pDigimon->AddSKill(new Skill("구멍 파기", 10, 20));
	pDigimon->AddSKill(new Skill("뿔드릴", 10, 30));
	m_enemyVec.push_back(pDigimon);
	digimonCount++;

	pDigimon = (CDigimon*)GET_SINGLE(ObjectManager)->CloneObject("EnemyDigimon");
	pDigimon->SetDigName("팔몬");
	pDigimon->SetCharacterInfo(5, 10, 3, 5, 50, 30, 1, 0, 0, 0);
	pDigimon->SetEvalutionType(1);
	pDigimon->SetAttributeType(3);
	pDigimon->AddSKill(new Skill("뿌리 채찍", 10, 20));
	pDigimon->AddSKill(new Skill("흡수", 10, 20));
	m_enemyVec.push_back(pDigimon);
	digimonCount++;

	pDigimon = (CDigimon*)GET_SINGLE(ObjectManager)->CloneObject("EnemyDigimon");
	pDigimon->SetDigName("임프몬");
	pDigimon->SetCharacterInfo(5, 10, 3, 5, 50, 30, 1, 0);
	pDigimon->SetEvalutionType(1);
	pDigimon->SetAttributeType(3);
	pDigimon->AddSKill(new Skill("어둠의 불꽃", 10, 20));
	pDigimon->AddSKill(new Skill("샤몬", 10, 20));
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
		cout << "1. 공격" << endl;
		cout << "2. 스킬1번" << endl;
		cout << "3. 스킬2번" << endl;
		cout << "4. 도망" << endl;
		int input = Input<int>();
		if (input < 1 || input > 4)
			continue;
		return input;
	}
}

