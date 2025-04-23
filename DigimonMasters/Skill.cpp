#include "pch.h"
#include "Skill.h"

Skill::Skill() : m_skillName(""), m_fasiveSkillName("")
{

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
