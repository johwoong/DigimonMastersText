#pragma once
#include "CCharacter.h"

class Skill;
class CDigimon : public CCharacter
{
protected:
	enum EVALUTION // ��ȭ
	{
		EV_GROW, // ����� 1
		EV_MATURITY, //  ������ 2 
		EV_INTEGER, // ����ü 3
		EV_ULTIMATE, // �ñ�ü 4
		EV_SUPERULTIMATE //�ʱñ�ü 5
	};

	enum ATTRIBUTE //������ �Ӽ�
	{
		AT_NONE,
		AT_UA, //��� 1
		AT_UI, // ���̷��� 2
		AT_DA, // ������ 3
		AT_UN // ���� 4
	};



protected:
	CDigimon();
	CDigimon(const CDigimon& digimon);
public:
	virtual ~CDigimon();

private:
	vector<Skill*> m_skillVec; // ��� ��ų ���� ����
	vector<EVINFO> m_evInfo;
	CHARACTERINFO m_originInfo;
protected:
	string m_strEvName;
	string m_strDigName;
	ATTRIBUTE m_aType;
	EVALUTION m_eType;
	vector<Skill*> m_useSkillVec; // ��� ��ų �������
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
	void Ev_Maturity(); // ������ ��ȭ
	void Ev_Integer(); // ����ü ��ȭ
	void Ev_Ultimat(); // �ñ�ü ��ȭ
	void EV_Super(); //�ʱñ�ü ��ȭ
	void Unevolve(); // ��ȭ����
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

