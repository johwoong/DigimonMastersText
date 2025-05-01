#pragma once
#include "CObj.h"
class CCharacter :
    public CObj
{
protected:
    CCharacter();
    CCharacter(const CCharacter& character);
    virtual ~CCharacter() = 0;

protected:
    CHARACTERINFO m_tInfo;
public:
    CHARACTERINFO GetCharacterInfo() const{
        return m_tInfo;
    }
    virtual void SetCharacterInfo(int iAttackMin, int iAttackMax, int iArmorMin, int iArmorMax, int iHpmax, int iDsMax, int iLevel, int iExp, int iFat = 0, int iSpeed = 0);
public:
    virtual bool Init();
    virtual void Render(); 
    virtual CCharacter* Clone() = 0;

public:
    virtual int GetDamage()
    {
        return rand() % (m_tInfo.iAttackMax - m_tInfo.iAttackMin + 1) + m_tInfo.iAttackMin;
    }

    virtual int GetArmor()
    {
        return rand() % (m_tInfo.iArmorMax - m_tInfo.iArmorMin + 1) + m_tInfo.iArmorMin;
    }

    virtual bool Damage(int damage);

    virtual void SetMaxHp();
    virtual void AddExp(int exp);
    virtual void LevelUp(int level);

    virtual void Save(class FileStream& stream);
    virtual void Load(class FileStream& stream);
};

