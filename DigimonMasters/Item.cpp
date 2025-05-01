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
    // �������� Ÿ�� �ҷ�����
    stream.Read(&m_tInfo.eType, sizeof(m_tInfo.eType));

    // �������� �̸� �ҷ�����
    int nameLength;
    stream.Read(&nameLength, sizeof(nameLength));  // �̸��� ���� �ҷ�����
    char* nameBuffer = new char[nameLength + 1];
    stream.Read(nameBuffer, nameLength);  // �̸� ���ڿ� �ҷ�����
    nameBuffer[nameLength] = '\0';  // ���ڿ� ���� ���� �߰�
    m_tInfo.strName = nameBuffer;  // �̸� ����
    delete[] nameBuffer;  // ���� �޸� ����

    // �������� ���� �ҷ�����
    stream.Read(&m_tInfo.iPrice, sizeof(m_tInfo.iPrice));

    // �������� ���� �ҷ�����
    stream.Read(&m_tInfo.iWeight, sizeof(m_tInfo.iWeight));

    // �������� ���� �ҷ�����
    int descLength;
    stream.Read(&descLength, sizeof(descLength));  // ������ ���� �ҷ�����
    char* descBuffer = new char[descLength + 1];
    stream.Read(descBuffer, descLength);  // ���� ���ڿ� �ҷ�����
    descBuffer[descLength] = '\0';  // ���ڿ� ���� ���� �߰�
    m_tInfo.strDesc = descBuffer;  // ���� ����
    delete[] descBuffer;  // ���� �޸� ����
}

void Item::Load(FileStream& stream)
{
    // �������� Ÿ�� �ҷ�����
    stream.Read(&m_tInfo.eType, sizeof(m_tInfo.eType));

    // �������� �̸� �ҷ�����
    int nameLength;
    stream.Read(&nameLength, sizeof(nameLength));  // �̸��� ���� �ҷ�����
    char* nameBuffer = new char[nameLength + 1];
    stream.Read(nameBuffer, nameLength);  // �̸� ���ڿ� �ҷ�����
    nameBuffer[nameLength] = '\0';  // ���ڿ� ���� ���� �߰�
    m_tInfo.strName = nameBuffer;  // �̸� ����
    delete[] nameBuffer;  // ���� �޸� ����

    // �������� ���� �ҷ�����
    stream.Read(&m_tInfo.iPrice, sizeof(m_tInfo.iPrice));

    // �������� ���� �ҷ�����
    stream.Read(&m_tInfo.iWeight, sizeof(m_tInfo.iWeight));

    // �������� ���� �ҷ�����
    int descLength;
    stream.Read(&descLength, sizeof(descLength));  // ������ ���� �ҷ�����
    char* descBuffer = new char[descLength + 1];
    stream.Read(descBuffer, descLength);  // ���� ���ڿ� �ҷ�����
    descBuffer[descLength] = '\0';  // ���ڿ� ���� ���� �߰�
    m_tInfo.strDesc = descBuffer;  // ���� ����
    delete[] descBuffer;  // ���� �޸� ����
}

