#pragma once
#include "CCharacter.h"

class Skill;
class CDigimon : public CCharacter
{
protected:
	enum EVALUTION // 진화
	{
		EV_GROW, // 성장기 1
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



protected:
	CDigimon();
	CDigimon(const CDigimon& digimon);
public:
	virtual ~CDigimon();

private:
	vector<Skill*> m_skillVec; // 모든 스킬 정보 저장
	vector<EVINFO> m_evInfo;
	CHARACTERINFO m_originInfo;
protected:
	string m_strEvName;
	string m_strDigName;
	ATTRIBUTE m_aType;
	EVALUTION m_eType;
	vector<Skill*> m_useSkillVec; // 사용 스킬 저장공간
	bool isDie;

public:
	string GetDigName() const { return m_strDigName; }
	const vector<Skill*>& GetUseSkillList() const { return m_useSkillVec; }
	const vector<EVINFO>& GetEvoulutionList() const { return m_evInfo; }
	bool GetIsDie() const { return isDie; }
	void SetOriginInfo();
	

public:
	void SetDigName(string digName);
	void SetAttributeType(int number);
	void SetEvaultionType(int number);
	void AddSKill(Skill* skill);
	void UpdateStat(int iAttack, int iArmor, int iSkillDamage, int iSkillDamage2);
	void SetEvaultionList(string strName, int iHp, int iDs, int iAttack, int iArmor);
	void Ev_Maturity(); // 성숙기 진화
	void Ev_Integer(); // 완전체 진화
	void Ev_Ultimat(); // 궁극체 진화
	void EV_Super(); //초궁극체 진화
	void Unevolve(); // 진화해제
	void UpdateSkill();
	void UpdateEnemySkill();
	void SetIsDie(bool isDie) { this->isDie = isDie; }
	void MaxHp();
	friend class CPlayer;
	friend class ObjectManager;

public:
	virtual bool Init();
	virtual void Render();
	virtual CDigimon* Clone();
};

