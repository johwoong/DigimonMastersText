#include "pch.h"
#include "Skill.h"
#include "FileStream.h"

Skill::Skill() : m_skillName(""), m_fasiveSkillName(""), skillDamage(0)
{

}

Skill::Skill(string m_SKillName, int skillDamage, int minusDs)
{
	this->m_skillName = m_SKillName;
	this->skillDamage = skillDamage;
	this->m_fasiveSkillName = "";
	this->minusDs = minusDs;
}

Skill::Skill(const Skill& skill)
{
	m_skillName = skill.m_skillName;
	m_fasiveSkillName = skill.m_fasiveSkillName;
}

Skill::~Skill()
{

}

void Skill::Render()
{

}

Skill* Skill::Clone()
{
	return new Skill(*this);
}

void Skill::Save(FileStream* pFile)
{
	// 스킬이름 저장
	int iLength = m_skillName.length();
	pFile->Write(&iLength, 4);
	pFile->Write((void*)m_skillName.c_str(), iLength);

	// 패시브스킬이름 저장
	iLength = m_fasiveSkillName.length();
	pFile->Write(&iLength, 4);
	pFile->Write((void*)m_fasiveSkillName.c_str(), iLength);

	pFile->Write(&skillDamage, sizeof(int));
	pFile->Write(&minusDs, sizeof(int));
}

void Skill::Load(FileStream* pFile)
{
	// 스킬 이름 불러오기
	int iLength = 0;
	pFile->Read(&iLength, 4);
	char* pName = new char[iLength + 1];
	memset(pName, 0, iLength + 1);

	pFile->Read(pName, iLength);
	pName[iLength] = 0;
	m_skillName = pName;


	// 패시브스킬 이름 불러오기
	iLength = 0;
	pFile->Read(&iLength, 4);
	pName = new char[iLength + 1];
	memset(pName, 0, iLength + 1);
	pFile->Read(pName, iLength);
	pName[iLength] = 0;
	m_fasiveSkillName = pName;

	pFile->Read(&skillDamage, sizeof(int));
	pFile->Read(&minusDs, sizeof(int));
}
