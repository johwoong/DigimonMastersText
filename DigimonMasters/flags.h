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
	MT_DART, // ��Ʈ����
	MT_START, // �����Ǹ���
	MT_SNOW, // ��������
	MT_SAND, // ���θ���
	MT_BACK
};

// ITEM TYPE
enum ITEM_TYPE
{
	IT_NONE,
	IT_EQ, // ���̸� ���
	IT_GENERIC, //����
	IT_EGG // ������ ��
};

enum ITEM_REGION // ��� Ÿ��
{
	HEAD,
	SHIRT,
	GLOVE,
	PANT,
	SHOES,
};
