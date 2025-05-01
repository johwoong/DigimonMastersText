#include "pch.h"
#include "Incubator.h"
#include "Inventory.h"
#include "CPlayer.h"
#include "ObjectManager.h"

Incubator::Incubator() : m_egg(nullptr), iStage(0), isHatch(false)
{

}

Incubator::~Incubator()
{
	Safe_Delete_VecList(m_eggItem_vec);
}

int Incubator::OutputMenu()
{

	while (true)
	{
		cout << "1. 용병 강화" << endl;
		cout << "2. 디지몬 알 해제" << endl;
		cout << "3. 뒤로가기" << endl;
		if (isHatch)
		{
			cout << "4. 디지몬 부화" << endl;
			int input = Input<int>();
			if (input < 1 || input > 4)
				continue;
			return input;
		}
		else
		{
			int input = Input<int>();
			if (input < 1 || input > 3)
			{
				system("cls");
				continue;
			}
			return input;
		}
	}
}

void Incubator::HatchDigimon()
{
	int successPercnet(0), destoryPercent(0);
	cout << "디지몬 알 부화를 시도합니다!!" << endl;
	switch (iStage)
	{
	case 0:
		successPercnet = 90;
		break;
	case 1:
		successPercnet = 70;
		break;
	case 2:
		successPercnet = 50;
		destoryPercent = 10;
		break;
	case 3:
		successPercnet = 30;
		destoryPercent = 30;
		break;
	case 4:
		successPercnet = 20;
		destoryPercent = 70;
		break;
	case 5:
		cout << "최고 단계입니다." << endl;
		system("pause");
		return;
	}
	int iRandom = rand() % 100;
	system("cls");
	cout << "디지몬 부화시도...." << endl;
	cout << "3" << endl;
	Sleep(1000);
	cout << "2" << endl;
	Sleep(1000);
	cout << "1" << endl;
	Sleep(1000);
	if (iRandom < successPercnet)
	{
		iStage++;
		cout << "디지몬 부화시도 " << iStage << "회 성공!!" << endl << endl;
		if (iStage >= 3)
		{
			isHatch = true;
			cout << "이제 부화시킬 수 있습니다!!" << endl;
		}
		system("pause");
	}
	else
	{
		int destoryRandom = rand() % 100; // 0 ~99 
		if (destoryRandom <= destoryPercent)
		{
			cout << "실패... 디지몬 알이 파괴되었습니다." << endl;
			iStage = 0;
			system("pause");
			m_egg = nullptr;
		}
		else
		{
			cout << "용병 디지몬 부화가 실패했지만 파괴되지는 않았습니다." << endl;
			system("pause");
		}
	}
}

void Incubator::DeleteEgg()
{
	if (iStage >= 1)
	{
		cout << "디지몬 알을 해제할 수 없습니다!!" << endl;
		system("pause");
	}
	else
	{
		GET_SINGLE(Inventory)->AddInventory(m_egg);
		m_egg = nullptr;
	}
}

void Incubator::CreateDigimon()
{
	cout << "디지몬을 생성합니다." << endl;
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(ObjectManager)->FindObject("Player");
	m_egg->GetDigimon()->SetDigionSize(iStage);
	pPlayer->SetDigimonVector(m_egg->GetDigimon());
	cout << m_egg->GetDigimon()->GetDigName() << "이 동료가 되었습니다!!" << endl;
	isHatch = false;
	m_egg = nullptr;
	iStage = 0;
	system("pause");
}

void Incubator::SetEggVec()
{
	vector<Item*> pEggVec = GET_SINGLE(Inventory)->GetItemVec();
	for (int i = 0; i < pEggVec.size(); ++i)
	{
		if (pEggVec[i]->GetItemInfo().eType == IT_EGG)
		{
			m_eggItem_vec.push_back(pEggVec[i]);
		}
	}
}


bool Incubator::Init()
{
	return true;
}

void Incubator::Update()
{
	while (true)
	{
		system("cls");
		SetConsoleColor(9);
		cout << "************* 디지몬 인큐베이터 * ************" << endl;
		if (m_egg == nullptr)
		{
			cout << "현재 알 : 없음" << endl;
		}
		else
			cout << "현재 알 : " << m_egg->GetItemInfo().strName << endl;
		cout << "현재 단계 : " << iStage << "단계" << endl;
		cout << "1단계 : 90%확률(파괴확률 : 없음)" << endl;
		cout << "2단계 : 70%확률(파괴확률 : 없음)" << endl;
		cout << "3단계 : 50%확률(파괴확률 : 10%)" << endl;
		cout << "4단계 : 30%확률(파괴확률 : 30%)" << endl;
		cout << "5단계 : 20%확률(파괴확률 : 70%)" << endl << endl;
		ResetConsoleColor();
		if (m_egg == nullptr)
		{
			for (int i = 0; i < m_eggItem_vec.size(); ++i)
			{
				cout << "[아이템 번호 : " << i + 1 << "]" << endl;
				m_eggItem_vec[i]->Render();
			}
			if (m_eggItem_vec.size() == 0)
			{
				cout << "디지몬 알이 존재하지 않습니다!!" << endl;
				system("pause");
				return;
			}
			cout << "부화 시킬 알을 선택해주세요 : ";
			int input = Input<int>();
			if (input < 1 || input > m_eggItem_vec.size())
				continue;
			// 인큐베이터에 알 넣기
			m_egg = (ItemEgg*)m_eggItem_vec[input - 1]->Clone();

			GET_SINGLE(Inventory)->DeleteItem(m_eggItem_vec[input - 1]);
			m_eggItem_vec.erase(m_eggItem_vec.begin() + input - 1);
			continue;
		}
		switch (OutputMenu())
		{
		case 1:
				HatchDigimon();
			break;
		case 2:
			DeleteEgg();
			break;
		case 3:
			return;
		case 4:
			if (isHatch)
				CreateDigimon();
			break;
		}
	}
}
