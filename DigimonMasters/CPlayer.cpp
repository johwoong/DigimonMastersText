#include "pch.h"
#include "CPlayer.h"

CPlayer::CPlayer() : iTaymer(0), m_strTayName(""), skill(nullptr), m_tType(T_NONE)
{
}

CPlayer::CPlayer(const CPlayer& player) : CCharacter(player)
{

}

CPlayer::~CPlayer()
{

}

bool CPlayer::Init()
{
	return true;
}

void CPlayer::Render()
{
}

CPlayer* CPlayer::Clone()
{
	return nullptr;
}
