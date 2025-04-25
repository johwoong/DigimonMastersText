#include "pch.h"
#include "CObj.h"

CObj::CObj() : m_eType(OT_DIGIMON)
{
}

CObj::CObj(const CObj& obj)
{
	strName = obj.strName;
	m_eType = obj.m_eType;
}

CObj::~CObj()
{

}