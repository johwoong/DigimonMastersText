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

void Skill::Save(FileStream& stream)
{
    // 1. m_skillName 历厘
    int nameLen = (int)m_skillName.length() + 1;
    stream.Write(&nameLen, sizeof(int));
    stream.Write((void*)m_skillName.c_str(), nameLen);

    // 2. m_fasiveSkillName 历厘
    int fasiveLen = (int)m_fasiveSkillName.length() + 1;
    stream.Write(&fasiveLen, sizeof(int));
    stream.Write((void*)m_fasiveSkillName.c_str(), fasiveLen);

    // 3. skillDamage 历厘
    stream.Write(&skillDamage, sizeof(int));

    // 4. minusDs 历厘
    stream.Write(&minusDs, sizeof(int));
}

void Skill::Load(FileStream& stream)
{
}
