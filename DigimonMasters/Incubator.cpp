#include "pch.h"
#include "Incubator.h"
#include "Inventory.h"
#include "CPlayer.h"
#include "ObjectManager.h"
#include "FileStream.h"

DEFINITION_SINGLE(Incubator)

Incubator::Incubator() : m_egg(nullptr), iStage(0), isHatch(false)
{

}

Incubator::~Incubator()
{
	Safe_Delete_VecList(m_eggItem_vec);
	SAFE_DELETE(m_egg);
}

int Incubator::OutputMenu()
{

	while (true)
	{
		cout << "1. �뺴 ��ȭ" << endl;
		cout << "2. ������ �� ����" << endl;
		cout << "3. �ڷΰ���" << endl;
		if (isHatch)
		{
			cout << "4. ������ ��ȭ" << endl;
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
	cout << "������ �� ��ȭ�� �õ��մϴ�!!" << endl;
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
		cout << "�ְ� �ܰ��Դϴ�." << endl;
		system("pause");
		return;
	}
	int iRandom = rand() % 100;
	system("cls");
	cout << "������ ��ȭ�õ�...." << endl;
	cout << "3" << endl;
	Sleep(1000);
	cout << "2" << endl;
	Sleep(1000);
	cout << "1" << endl;
	Sleep(1000);
	if (iRandom < successPercnet)
	{
		iStage++;
		cout << "������ ��ȭ�õ� " << iStage << "ȸ ����!!" << endl << endl;
		if (iStage >= 3)
		{
			isHatch = true;
			cout << "���� ��ȭ��ų �� �ֽ��ϴ�!!" << endl;
		}
		system("pause");
	}
	else
	{
		int destoryRandom = rand() % 100; // 0 ~99 
		if (destoryRandom <= destoryPercent)
		{
			cout << "����... ������ ���� �ı��Ǿ����ϴ�." << endl;
			iStage = 0;
			system("pause");
			m_egg = nullptr;
		}
		else
		{
			cout << "�뺴 ������ ��ȭ�� ���������� �ı������� �ʾҽ��ϴ�." << endl;
			system("pause");
		}
	}
}

void Incubator::DeleteEgg()
{
	if (iStage >= 1)
	{
		cout << "������ ���� ������ �� �����ϴ�!!" << endl;
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
	cout << "�������� �����մϴ�." << endl;
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(ObjectManager)->FindObject("Player");
	m_egg->GetDigimon()->SetDigionSize(iStage);
	pPlayer->SetDigimonVector(m_egg->GetDigimon());
	cout << m_egg->GetDigimon()->GetDigName() << "�� ���ᰡ �Ǿ����ϴ�!!" << endl;
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
		cout << "************* ������ ��ť������ * ************" << endl;
		if (m_egg == nullptr)
		{
			cout << "���� �� : ����" << endl;
		}
		else
			cout << "���� �� : " << m_egg->GetItemInfo().strName << endl;
		cout << "���� �ܰ� : " << iStage << "�ܰ�" << endl;
		cout << "1�ܰ� : 90%Ȯ��(�ı�Ȯ�� : ����)" << endl;
		cout << "2�ܰ� : 70%Ȯ��(�ı�Ȯ�� : ����)" << endl;
		cout << "3�ܰ� : 50%Ȯ��(�ı�Ȯ�� : 10%)" << endl;
		cout << "4�ܰ� : 30%Ȯ��(�ı�Ȯ�� : 30%)" << endl;
		cout << "5�ܰ� : 20%Ȯ��(�ı�Ȯ�� : 70%)" << endl << endl;
		ResetConsoleColor();
		if (m_egg == nullptr)
		{
			for (int i = 0; i < m_eggItem_vec.size(); ++i)
			{
				cout << "[������ ��ȣ : " << i + 1 << "]" << endl;
				m_eggItem_vec[i]->Render();
			}
			if (m_eggItem_vec.size() == 0)
			{
				cout << "������ ���� �������� �ʽ��ϴ�!!" << endl;
				system("pause");
				return;
			}
			cout << "��ȭ ��ų ���� �������ּ��� : ";
			int input = Input<int>();
			if (input < 1 || input > m_eggItem_vec.size())
				continue;
			// ��ť�����Ϳ� �� �ֱ�
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

void Incubator::Save(FileStream* pFile)
{
	int itemCount = m_eggItem_vec.size();
	pFile->Write(&itemCount, sizeof(int)); // �� ������ ���� ����

	for (int i = 0; i < itemCount; ++i)
	{
		m_eggItem_vec[i]->Save(pFile);
	}
	if(m_egg != nullptr)
		m_egg->Save(pFile);
	pFile->Write(&iStage, sizeof(iStage));
	pFile->Write(&isHatch, sizeof(isHatch));
}

void Incubator::Load(FileStream* pFile)
{
	int itemCount = 0;
	pFile->Read(&itemCount, sizeof(int));
	for (int i = 0; i < itemCount; ++i)
	{
		ItemEgg* pItem = new ItemEgg;
		pItem->Load(pFile);
		m_eggItem_vec.push_back(pItem);
	}
	m_egg = new ItemEgg;
	m_egg->Load(pFile);
	if (m_egg->p_digimon == nullptr)
	{
		SAFE_DELETE(m_egg);
	}
	pFile->Read(&iStage, sizeof(iStage));
	pFile->Read(&isHatch, sizeof(isHatch));
}
