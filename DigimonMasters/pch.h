// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가
#include <iostream>
#include <time.h>
#include <unordered_map>
#include <vector>
#include "Windows.h"
using namespace std;

// 사용자 정의 헤더
#include "define.h"
#include "flags.h"



template<typename T>
T Input()
{
	T data;
	cin >> data;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1024, '\n');
		return 0;
	}
	return data;
}

template<typename T>
void Safe_Delete_VecList(T& p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_DELETE(*iter);
	}

	p.clear();
}


template<typename T>
void Safe_Delete_MapList(T& p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter == p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}

typedef struct _tagCharacterInfo
{
	int iAttackMin;
	int iAttackMax;
	int iArmorMin;
	int iArmorMax;
	int iHp;
	int iHpMax;
	int iDs;
	int iDsMax;
	int iLevel;
	int iExp;
	int iFat; // 피로도
	int iSpeed;
}CHARACTERINFO;

typedef struct _tagItemInfo
{
	ITEM_TYPE eType;
	string strName;
	int iPrice;
	int iWeight;
	string strDesc;

}ITEMINFO;

typedef struct _tagItemStatInfo
{
	int iAttack; // 공격 증가
	int iArmor; // 방어 증가
	int iDs; // DS 증가
	int iSpeed; // 이동속도 증가
	int iSkillDamage; // 스킬데미지 증가
}ITEMSTAT;

#endif //PCH_H
