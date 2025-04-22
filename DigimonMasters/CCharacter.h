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

    virtual void SetCharacterInfo(int iAttackMin, int iAttackMax, int iArmorMin, int iArmorMax, int iHpmax, int iDsMax, int iLevel, int iExp);
public:
    virtual bool Init();
    virtual void Render();
    virtual CCharacter* Clone() = 0;

};

