#pragma once


enum TAYMER
{
	T_NONE,
	T_TAIL,
	T_METU,
	T_MINA,
	T_LIKI,
	T_BACK,
	T_END
};

enum OBJECT_TYPE
{
	OT_PLAYER,
	OT_DIGIMON,
	OT_ENEMYDIGIMON,
	OT_ITEM
};

// MAP TYPE
enum MAP_TYPE
{
	MT_NONE,
	MT_DART, // 닷트본부
	MT_START, // 시작의마을
	MT_SNOW, // 눈보라마을
	MT_SAND, // 서부마을
	MT_BACK
};

// ITEM TYPE
enum ITEM_TYPE
{
	IT_NONE,
	IT_EQ, // 테이머 장비
	IT_GENERIC, //포션
	IT_EGG // 디지몬 알
};

enum ITEM_REGION // 장비 타입
{
	HEAD,
	SHIRT,
	GLOVE,
	PANT,
	SHOES,
};
