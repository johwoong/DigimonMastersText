#pragma once
#include "CCharacter.h"
#include "Skill.h"
class CDigimon : public CCharacter
{
private:
	enum EVALUTION // ��ȭ
	{
		EV_NONE,
		EV_GROW, //����� 1
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

private:
	CDigimon();
	CDigimon(const CDigimon& digimon);
	~CDigimon();

private:
	string m_strDigName;
	EVALUTION m_eType;
	ATTRIBUTE m_aType;

public:
	string GetDigName() const { return m_strDigName; }

public:
	void SetDigName(string digName);
	void SetEvalutionType(int number);
	void SetAttributeType(int number);
private:
	friend class CPlayer;
	friend class ObjectManager;

public:
	virtual bool Init();
	virtual void Render();
	virtual CDigimon* Clone();
};

