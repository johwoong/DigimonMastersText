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
	cout << "[테이머 정보]" << endl;
	cout << "이름 : " << GetName() << "\t테이머 : " << GetTaymerName() << endl;
	cout << "체력 : " << m_tInfo.iHp << "\tDS : " << m_tInfo.iDs << endl;
	cout << "레벨 : " << m_tInfo.iLevel << "\t경험치 : " << m_tInfo.iExp << endl;
	cout << "스킬 : " << GetSkill()->GetSkillName() << "\t패시브 스킬 : " << GetSkill()->GetFasiveSkillName() << endl;
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
	cout << "[캐릭터 장비]" << endl;
	if (!m_equip[HEAD])
		cout << "머리 : 없음" << endl;
	else
		cout << "머리 : " << m_equip[HEAD]->GetItemInfo().strName << endl;

	if (!m_equip[SHIRT])
		cout << "상의 : 없음" << endl;
	else
		cout << "상의 : " << m_equip[SHIRT]->GetItemInfo().strName << endl;

	if (!m_equip[GLOVE])
		cout << "장갑 : 없음" << endl;
	else
		cout << "장갑 : " << m_equip[GLOVE]->GetItemInfo().strName << endl;

	if (!m_equip[PANT])
		cout << "하의 : 없음" << endl;
	else
		cout << "하의 : " << m_equip[PANT]->GetItemInfo().strName << endl;

	if (!m_equip[SHOES])
		cout << "신발 : 없음" << endl;
	else
		cout << "신발 : " << m_equip[SHOES]->GetItemInfo().strName << endl;
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
		cout << "장착할 수 있는 장비가 아닙니다." << endl;
	}
	// 장비가 이미 있으면 교체해준다.
	// 머리는 머리에
	// 상의는 상의
	// 하의는 하의
	// 신발은 신발
	
}
