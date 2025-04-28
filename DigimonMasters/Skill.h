#pragma once
class Skill
{
private:
	Skill();
	Skill(string m_SKillName, int skillDamage, int minusDs);
	Skill(const Skill& skill);
public:
	~Skill();

	string m_skillName;
	string m_fasiveSkillName;
	int skillDamage; // 스킬데미지
	int minusDs;  // 스킬사용 마나 소모값
private:
	friend class CPlayer;
	friend class CGame;
	friend class MapDart;
	friend class MapStart;
public:
	void Render();
 	string GetSkillName() const { return m_skillName; }
	string GetFasiveSkillName() const { return m_fasiveSkillName; }
	void SetSkillName(string m_skillName) { this->m_skillName = m_skillName; }
	void SetFasiveSkillName(string m_fasiveSkillName) { this->m_fasiveSkillName = m_fasiveSkillName; }
	void SetSkillDamage(int damage) { this->skillDamage = damage; }
	int GetSkillDamage() { return skillDamage; }
	void SetMinusDs(int value) { this->minusDs = value; }
	int GetMinusDs() { return minusDs; }
public:
	virtual Skill* Clone();
};

