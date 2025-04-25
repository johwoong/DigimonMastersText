#include "pch.h"
#include "CPlayer.h"
#include "Skill.h"
#include "Item.h"
#include "ItemEquip.h"

CPlayer::CPlayer() : iTaymer(0), m_strTayName(""), m_tType(T_NONE), p_digimon(nullptr), isDigimon(false), p_skill(nullptr)
{
	memset(&m_equip, 0, sizeof(m_equip));
}

CPlayer::CPlayer(const CPlayer& player) : CCharacter(player)
{
	
}

CPlayer::~CPlayer()
{
	SAFE_DELETE(p_digimon);
	SAFE_DELETE(p_skill);
}

bool CPlayer::Init()
{
	return true;
}

void CPlayer::Render()
{
	cout << "[���̸� ����]" << endl;
	cout << "�̸� : " << GetName() << "\t���̸� : " << GetTaymerName() << endl;
	cout << "ü�� : " << m_tInfo.iHp << "\tDS : " << m_tInfo.iDs << endl;
	cout << "���� : " << m_tInfo.iLevel << "\t����ġ : " << m_tInfo.iExp << endl;
	cout << "��ų : " << GetSkill()->GetSkillName() << "\t�нú� ��ų : " << GetSkill()->GetFasiveSkillName() << endl;
	cout << endl << endl;
	PrintEquip();
}

CPlayer* CPlayer::Clone()
{
	return nullptr;
}

void CPlayer::SetDigimon(CDigimon* digimon)
{
	p_digimon = new CDigimon;
	p_digimon = digimon->Clone();
}

void CPlayer::SetSkill(Skill* skill)
{
	p_skill = skill;
}


void CPlayer::PrintEquip()
{
	cout << "[ĳ���� ���]" << endl;
	if (!m_equip[HEAD])
		cout << "�Ӹ� : ����" << endl;
	else
		cout << "�Ӹ� : " << m_equip[HEAD]->GetItemInfo().strName << endl;

	if (!m_equip[SHIRT])
		cout << "���� : ����" << endl;
	else
		cout << "���� : " << m_equip[SHIRT]->GetItemInfo().strName << endl;

	if (!m_equip[GLOVE])
		cout << "�尩 : ����" << endl;
	else
		cout << "�尩 : " << m_equip[GLOVE]->GetItemInfo().strName << endl;

	if (!m_equip[PANT])
		cout << "���� : ����" << endl;
	else
		cout << "���� : " << m_equip[PANT]->GetItemInfo().strName << endl;

	if (!m_equip[SHOES])
		cout << "�Ź� : ����" << endl;
	else
		cout << "�Ź� : " << m_equip[SHOES]->GetItemInfo().strName << endl;
}

void CPlayer::Equip(Item* item)
{
	ItemEquip* pItem = (ItemEquip*)item;
	switch (pItem->GetItemRegion())
	{
	case HEAD:
		m_equip[HEAD] = pItem;
		break;
	case SHIRT:
		m_equip[SHIRT] = pItem;
		break;
	case GLOVE:
		m_equip[GLOVE] = pItem;
		break;
	case PANT:
		m_equip[PANT] = pItem;
		break;
	case SHOES:
		m_equip[SHOES] = pItem;
		break;
	default:
		cout << "������ �� �ִ� ��� �ƴմϴ�." << endl;
	}
	// ��� �̹� ������ ��ü���ش�.
	// �Ӹ��� �Ӹ���
	// ���Ǵ� ����
	// ���Ǵ� ����
	// �Ź��� �Ź�
	
}
