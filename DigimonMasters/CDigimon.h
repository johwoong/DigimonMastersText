#pragma once
#include "CCharacter.h"

class Skill;
class CDigimon : public CCharacter
{
private:
	enum EVALUTION // 진화
	{
		EV_NONE,
		EV_GROW, //성장기 1
		EV_MATURITY, //  성숙기 2 
		EV_INTEGER, // 완전체 3
		EV_ULTIMATE, // 궁극체 4
		EV_SUPERULTIMATE //초궁극체 5
	};

	enum ATTRIBUTE //디지몬 속성
	{
		AT_NONE,
		AT_UA, //백신 1
		AT_UI, // 바이러스 2
		AT_DA, // 데이터 3
		AT_UN // 언노운 4
	};

private:
	CDigimon();
	CDigimon(const CDigimon& digimon);
public:
	virtual ~CDigimon();

private:
	string m_strDigName;
	EVALUTION m_eType;
	ATTRIBUTE m_aType;
	vector<Skill*> m_skillVec;

public:
	string GetDigName() const { return m_strDigName; }
	const vector<Skill*>& GetSkillList() const { return m_skillVec; }

public:
	void SetDigName(string digName);
	void SetEvalutionType(int number); 
	void SetAttributeType(int number);
	void AddSKill(Skill* skill);

	friend class CPlayer;
	friend class ObjectManager;

public:
	virtual bool Init();
	virtual void Render();
	virtual CDigimon* Clone();
};

