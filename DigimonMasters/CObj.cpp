#include "pch.h"
#include "CObj.h"
#include "FileStream.h"

CObj::CObj() 
{
}

CObj::CObj(const CObj& obj)
{
	strName = obj.strName;
	m_eType = obj.m_eType;
}

CObj::~CObj()
{

}

void CObj::Save(FileStream* pFile)
{
	pFile->Write(&m_eType, 4);
	int iLength = strName.length();
	pFile->Write(&iLength, 4);

	pFile->Write((void*)strName.c_str(), iLength);
}

void CObj::Load(FileStream* pFile)
{
	pFile->Read(&m_eType, sizeof(OBJECT_TYPE));
	
	int iLength = 0;
	pFile->Read(&iLength, 4);

	// 여기서 문자열 읽기 오류 발생
	char* pName = new char[iLength + 1];
	memset(pName, 0, iLength + 1);

	pFile->Read(pName, iLength);
	pName[iLength] = 0;
	strName = pName;
}


