#include "pch.h"
#include "ItemEgg.h"
#include "CDigimon.h"
#include "Skill.h"

ItemEgg::ItemEgg()
{
}

ItemEgg::ItemEgg(const ItemEgg& item) : Item(item)
{
    p_digimon = item.p_digimon;
}

ItemEgg::~ItemEgg()
{
}

void ItemEgg::SetDigimonInfo(const string& name, int attackMin, int attackMax, int armorMin, int armorMax, int hpMax, int dsMax, int level, int exp, int fat, int speed, int attributeType, const vector<pair<string, pair<int, int>>>& skills, const vector<tuple<string, int, int, int, int>>& evolutions)
{
    p_digimon = new CDigimon();

    p_digimon->SetDigName(name);
    p_digimon->SetCharacterInfo(
        attackMin, attackMax,
        armorMin, armorMax,
        hpMax, dsMax,
        level, exp, fat, speed
    );
    p_digimon->SetAttributeType(attributeType);

    for (const auto& skill : skills)
    {
        p_digimon->AddSKill(new Skill(skill.first, skill.second.first, skill.second.second));
    }

    for (const auto& evo : evolutions)
    {
        p_digimon->SetEvaultionList(
            get<0>(evo),
            get<1>(evo),
            get<2>(evo),
            get<3>(evo),
            get<4>(evo)
        );
    }

    p_digimon->UpdateSkill();
}



bool ItemEgg::Init()
{
    return true;
}

void ItemEgg::Render()
{
	cout << "[아이템 정보] " << endl;
	cout << "알 이름 : " << m_tInfo.strName << endl;
	cout << "용량 : " << m_tInfo.iWeight << "\t설명 : " << m_tInfo.strDesc << endl;
	cout << endl << endl;
}

Item* ItemEgg::Clone()
{
    return new ItemEgg(*this);
}

void ItemEgg::Save(FileStream* pFile)
{
    // 현재 디지몬 정보 읽기
    if (p_digimon == nullptr)
        p_digimon = new CDigimon;
    p_digimon->Save(pFile);
}

void ItemEgg::Load(FileStream* pFile)
{
    // 현재 디지몬 정보 읽기
    if (p_digimon == nullptr)
        p_digimon = new CDigimon;
    p_digimon->Load(pFile);
}
