#include "pch.h"
#include "Skill.h"

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
