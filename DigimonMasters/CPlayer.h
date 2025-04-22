#pragma once
#include "CCharacter.h"
class CPlayer :
    public CCharacter
{
private:
    CPlayer();
    CPlayer(const CPlayer& player);
    ~CPlayer();
private:
    int iTaymer;
    string m_strTayName;
    class Skill* skill;
    TAYMER m_tType;

private:
    friend class ObjectManager;

public:
    virtual bool Init();
    virtual void Render();
    virtual CPlayer* Clone();
public:
    void SetTaymerTypeAndName(TAYMER eType, string strName) { m_tType = eType; m_strTayName = strName; }
    string GetTaymerName() { return m_strTayName; }

};

