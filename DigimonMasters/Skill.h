#pragma once
class Skill
{
private:
	Skill();
	Skill(const Skill& skill);
	~Skill();

	string m_skillName;
	string m_fasiveSkillName;

private:
	friend class CPlayer;
	friend class CGame;
public:
	void Render();
	string GetSkillName() const { return m_skillName; }
	string GetFasiveSkillName() const { return m_fasiveSkillName; }
	void SetSkillName(string m_skillName) { this->m_skillName = m_skillName; }
	void SetFasiveSkillName(string m_fasiveSkillName) { this->m_fasiveSkillName = m_fasiveSkillName; }

public:
	virtual Skill* Clone();
};

