#pragma once
#include "CCharacter.h"
#include "CDigimon.h"
#include "Skill.h"
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
    TAYMER m_tType;
    CDigimon* p_digimon;
    bool isDigimon;
    Skill* p_skill;
    class Item* m_equip[5];

private:
    friend class ObjectManager;

public:
    virtual bool Init();
    virtual void Render();
    virtual CPlayer* Clone();
public:
    void SetTaymerTypeAndName(TAYMER eType, string strName) { m_tType = eType; m_strTayName = strName; }
    string GetTaymerName() const { return m_strTayName; }
    void SetDigimon(CDigimon* digimon);
    CDigimon* GetDigimon() { return p_digimon; }
    bool GetIsDigimon() const { return isDigimon; }
    void SetIsDigimon(bool isDigimon) { this->isDigimon = isDigimon; }
    Skill* GetSkill() const { return p_skill; }
    void SetSkill(Skill* skill);
public:
    void PrintEquip();
    void Equip(Item* item);
    void UnEquip(ITEM_REGION eType);
    void ApplyEquip(Item* item);
    void PrintItemStat(Item* item);
 

 

};

