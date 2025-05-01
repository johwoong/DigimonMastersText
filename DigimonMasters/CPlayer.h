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
    vector<CDigimon*> m_digimonVec; // 모든 디지몬 저장
    CDigimon* p_digimon; // 현재 디지몬 저장
    bool isDigimon;
    Skill* p_skill;
    class Item* m_equip[5];
    
private:
    static int iGold;

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
    void MinusDs(int value);
    void SetDigimonVector(CDigimon* digimon);
    void RenderDigimonList();
    void ChangeDigimon(int index); // 디지몬 교체
    void PrintHasDigimon(); // 가지고있는 디지몬 출력
    const vector<CDigimon*> GetDigimonVec() const { return m_digimonVec; }
public:
    void PrintEquip();
    void Equip(Item* item);
    void UnEquip(ITEM_REGION eType);
    void ApplyEquip(Item* item);
    void PrintItemStat(Item* item);

public:
    virtual void Save(class FileStream& stream);
    virtual void Load(class FileStream& stream);
 

 

};

