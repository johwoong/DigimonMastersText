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
				cout << "디지몬이 존재하지 않습니다!!" << endl;
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


	cout << player->GetDigimon()->GetDigName() << "이 " << digimon->GetDigName() << "에게 "
		<< iDamage << " 피해를 주었습니다." << endl;
	if (!digimon->Damage(iDamage))
	{
		cout << digimon->GetDigName() << "을 해치웠습니다!!." << endl;
		digimon->SetMaxHp();
		digimon->DropItem();
		player->AddExp(2);
		player->GetDigimon()->AddExp(10);
		return;
	}

	iDamage = player->GetDigimon()->GetDamage() - digimon->GetArmor();
	iDamage = iDamage < 1 ? 1 : iDamage;

	cout << digimon->GetDigName() << "이 " << player->GetDigimon()->GetDigName() << "에게 "
		<< iDamage << " 피해를 주었습니다." << endl;

	if (!player->GetDigimon()->Damage(iDamage))
	{
		player->GetDigimon()->SetIsDie(true);
		cout << "파트너 디지몬이 쓰러졌습니다...." << endl;
		cout << "기지로 돌아갑니다.." << endl;
		return;
	}
}

void MapStart::SkillAttack(CPlayer* player, CEnemyDigimon* digimon, int num)
{
	int skillDamage = 0;
	switch (num)
	{
	case 1:
		// 스킬 1번 사용
		skillDamage = player->GetDigimon()->GetUseSkillList()[0]->GetSkillDamage();

		cout << player->GetDigimon()->GetDigName() << "의 " << player->GetDigimon()->GetUseSkillList()[0]->GetSkillName() << "!!" << endl;

		cout << player->GetDigimon()->GetDigName() << "이 " << digimon->GetDigName() << "에게 "
			<< skillDamage << " 피해를 주었습니다." << endl;

		if (!digimon->Damage(skillDamage))
		{
			cout << digimon->GetDigName() << "을 해치웠습니다!!." << endl;
			digimon->SetMaxHp();
			digimon->DropItem();
			player->AddExp(2);
			player->GetDigimon()->AddExp(10);
			return;
		}
		break;
	case 2:
		// 스킬 2번 사용
		skillDamage = player->GetDigimon()->GetUseSkillList()[1]->GetSkillDamage();
		cout << player->GetDigimon()->GetDigName() << "의 " << player->GetDigimon()->GetUseSkillList()[1]->GetSkillName() << "!!" << endl;

		cout << player->GetDigimon()->GetDigName() << "이 " << digimon->GetDigName() << "에게 "
			<< skillDamage << " 피해를 주었습니다." << endl;
		if (!digimon->Damage(skillDamage))
		{
			cout << digimon->GetDigName() << "을 해치웠습니다!!." << endl;
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
	pDigimon->SetDigName("두리몬");
	pDigimon->SetCharacterInfo(5, 10, 3, 5, 50, 30, 1, 0, 0, 0);
	pDigimon->SetAttributeType(3);
	pDigimon->SetEvaultionType(1);
	pDigimon->AddSKill(new Skill("구멍 파기", 10, 20));
	pDigimon->AddSKill(new Skill("뿔드릴", 10, 30));
	pDigimon->UpdateEnemySkill();
	m_enemyVec.push_back(pDigimon);
	pDigimon->SetGold(300);
	Item* item = new ItemEgg;
	item->SetItemInfo(IT_EGG, "두리몬의 알", 1000, 50, "두리몬의 알");
	pDigimon->SetItemList(item);
	item = new ItemGeneric;
	item->SetItemInfo(IT_GENERIC, "두리몬의 뿔", 50, 1, "재료 아이템");
	pDigimon->SetItemList(item);
	digimonCount++;

	pDigimon = (CEnemyDigimon*)GET_SINGLE(ObjectManager)->CloneObject("EnemyDigimon");
	pDigimon->SetDigName("임프몬");
	pDigimon->SetCharacterInfo(5, 10, 3, 5, 50, 30, 1, 0, 0, 0);
	pDigimon->SetAttributeType(3);
	pDigimon->SetEvaultionType(1);
	pDigimon->AddSKill(new Skill("막치기", 10, 20));
	pDigimon->AddSKill(new Skill("데몬 펀치", 10, 30));
	pDigimon->UpdateEnemySkill();
	m_enemyVec.push_back(pDigimon);
	pDigimon->SetGold(300);
	item = new ItemEgg;
	item->SetItemInfo(IT_EGG, "임프몬의 알", 1000, 50, "임프몬 알");
	pDigimon->SetItemList(item);
	item = new ItemGeneric;
	item->SetItemInfo(IT_GENERIC, "꼬마악마의 뿔", 50, 1, "재료 아이템");
	pDigimon->SetItemList(item);
	digimonCount++;

	pDigimon = (CEnemyDigimon*)GET_SINGLE(ObjectManager)->CloneObject("EnemyDigimon");
	pDigimon->SetDigName("시드라몬");
	pDigimon->SetCharacterInfo(30, 50, 10, 15, 50, 30, 1, 0, 0, 0);
	pDigimon->SetAttributeType(1);
	pDigimon->SetEvaultionType(2);
	pDigimon->AddSKill(new Skill("물의 맹세", 50, 20));
	pDigimon->AddSKill(new Skill("웨더 볼", 20, 30));
	pDigimon->UpdateEnemySkill();
	m_enemyVec.push_back(pDigimon);
	pDigimon->SetGold(300);
	item = new ItemEgg;
	item->SetItemInfo(IT_EGG, "베타몬의 알", 1000, 50, "베타몬의 알");
	pDigimon->SetItemList(item);
	item = new ItemGeneric;
	item->SetItemInfo(IT_GENERIC, "시드라몬의 비닐", 50, 1, "재료 아이템");
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
		cout << "1. 공격" << endl;
		cout << "2. 진화" << endl;
		cout << "3. 스킬1번" << endl;
		cout << "4. 스킬2번" << endl;
		cout << "5. 도망" << endl;
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
		cout << "1. 성숙기" << endl;
		cout << "2. 완전체" << endl;
		cout << "3. 궁극체" << endl;
		cout << "4. 초궁극체" << endl;
		cout << "5. 진화해제" << endl;
		cout << "6. 뒤로가기" << endl;
		int input = Input<int>();
		if (input < 1 || input > 6)
			continue;
		return input;
	}
}

