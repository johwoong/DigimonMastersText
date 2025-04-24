#include "pch.h"
#include "CPlayer.h"
#include "Skill.h"

CPlayer::CPlayer() : iTaymer(0), m_strTayName(""), m_tType(T_NONE), p_digimon(nullptr), isDigimon(false), p_skill(nullptr)
{
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
