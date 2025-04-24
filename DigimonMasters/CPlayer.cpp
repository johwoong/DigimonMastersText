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
	cout << "[���̸� ����]" << endl;
	cout << "�̸� : " << GetName() << "\t���̸� : " << GetTaymerName() << endl;
	cout << "ü�� : " << m_tInfo.iHp << "\tDS : " << m_tInfo.iDs << endl;
	cout << "���� : " << m_tInfo.iLevel << "\t����ġ : " << m_tInfo.iExp << endl;
	cout << "��ų : " << GetSkill()->GetSkillName() << "\t�нú� ��ų : " << GetSkill()->GetFasiveSkillName() << endl;
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
