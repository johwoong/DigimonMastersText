#include "pch.h"
#include "CDigimon.h"

CDigimon::CDigimon() : m_strDigName(""), m_eType(EV_NONE), m_aType(AT_NONE)
{
}

CDigimon::CDigimon(const CDigimon& digimon) : CCharacter(digimon)
{
	m_strDigName = digimon.m_strDigName;
	m_eType = digimon.m_eType;
	m_aType = digimon.m_aType;
}

CDigimon::~CDigimon()
{

}

void CDigimon::SetDigName(string digName)
{
	m_strDigName = digName;
}

void CDigimon::SetEvalutionType(int number)
{
	m_eType = (EVALUTION)number;
}

void CDigimon::SetAttributeType(int number)
{
	m_aType = (ATTRIBUTE)number;
}

bool CDigimon::Init()
{
	return true;
}

void CDigimon::Render()
{

}


CDigimon* CDigimon::Clone()
{
	return new CDigimon(*this);
}
