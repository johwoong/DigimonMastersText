#include "pch.h"
#include "Item.h"
#include "FileStream.h"

Item::Item()
{
}

Item::Item(const Item& item)
{
	m_tInfo = item.m_tInfo;
}

Item::~Item()
{

}

bool Item::Init()
{
	return true;
}

void Item::Render()
{
}

Item* Item::Clone()
{
	return new Item(*this);
}

void Item::SetItemInfo(ITEM_TYPE itemType, string strName, int iPrice, int iWeight, string strDesc)
{
	m_tInfo.eType = itemType;
	m_tInfo.strName = strName;
	m_tInfo.iPrice = iPrice;
	m_tInfo.iWeight = iWeight;
	m_tInfo.strDesc = strDesc;
}

void Item::Save(FileStream& stream)
{
    // 아이템의 타입 불러오기
    stream.Read(&m_tInfo.eType, sizeof(m_tInfo.eType));

    // 아이템의 이름 불러오기
    int nameLength;
    stream.Read(&nameLength, sizeof(nameLength));  // 이름의 길이 불러오기
    char* nameBuffer = new char[nameLength + 1];
    stream.Read(nameBuffer, nameLength);  // 이름 문자열 불러오기
    nameBuffer[nameLength] = '\0';  // 문자열 종료 문자 추가
    m_tInfo.strName = nameBuffer;  // 이름 저장
    delete[] nameBuffer;  // 동적 메모리 해제

    // 아이템의 가격 불러오기
    stream.Read(&m_tInfo.iPrice, sizeof(m_tInfo.iPrice));

    // 아이템의 무게 불러오기
    stream.Read(&m_tInfo.iWeight, sizeof(m_tInfo.iWeight));

    // 아이템의 설명 불러오기
    int descLength;
    stream.Read(&descLength, sizeof(descLength));  // 설명의 길이 불러오기
    char* descBuffer = new char[descLength + 1];
    stream.Read(descBuffer, descLength);  // 설명 문자열 불러오기
    descBuffer[descLength] = '\0';  // 문자열 종료 문자 추가
    m_tInfo.strDesc = descBuffer;  // 설명 저장
    delete[] descBuffer;  // 동적 메모리 해제
}

void Item::Load(FileStream& stream)
{
    // 아이템의 타입 불러오기
    stream.Read(&m_tInfo.eType, sizeof(m_tInfo.eType));

    // 아이템의 이름 불러오기
    int nameLength;
    stream.Read(&nameLength, sizeof(nameLength));  // 이름의 길이 불러오기
    char* nameBuffer = new char[nameLength + 1];
    stream.Read(nameBuffer, nameLength);  // 이름 문자열 불러오기
    nameBuffer[nameLength] = '\0';  // 문자열 종료 문자 추가
    m_tInfo.strName = nameBuffer;  // 이름 저장
    delete[] nameBuffer;  // 동적 메모리 해제

    // 아이템의 가격 불러오기
    stream.Read(&m_tInfo.iPrice, sizeof(m_tInfo.iPrice));

    // 아이템의 무게 불러오기
    stream.Read(&m_tInfo.iWeight, sizeof(m_tInfo.iWeight));

    // 아이템의 설명 불러오기
    int descLength;
    stream.Read(&descLength, sizeof(descLength));  // 설명의 길이 불러오기
    char* descBuffer = new char[descLength + 1];
    stream.Read(descBuffer, descLength);  // 설명 문자열 불러오기
    descBuffer[descLength] = '\0';  // 문자열 종료 문자 추가
    m_tInfo.strDesc = descBuffer;  // 설명 저장
    delete[] descBuffer;  // 동적 메모리 해제
}

