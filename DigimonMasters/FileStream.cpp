#include "pch.h"
#include "FileStream.h"


FileStream::FileStream() : m_pFile(nullptr), m_bOpen(false), m_iFileSize(0)
{
}

FileStream::FileStream(const char* pFileName, const char* pMode)
{
}

FileStream::~FileStream()
{
}

bool FileStream::Open(const char* pFileName, const char* pMode)
{
    fopen_s(&m_pFile, pFileName, pMode);
    if (!m_pFile)
        return false;

    m_bOpen = true;

    if (pMode[0] == 'r')
        m_eMode = FM_READ;
    if (pMode[0] == 'w')
        m_eMode = FM_WRITE;

    fseek(m_pFile, 0, SEEK_END);
    m_iFileSize = ftell(m_pFile);
    fseek(m_pFile, 0, SEEK_SET);
    return true;
}

bool FileStream::Close()
{
    if (!m_bOpen)
        return false;
    fclose(m_pFile);
    m_pFile = nullptr;
    m_bOpen = false;
    m_iFileSize = 0;
    return true;
}

bool FileStream::Read(void* pData, int iSize)
{
    if (!m_bOpen || m_eMode != FM_READ)
        return false;
    fread(pData, iSize, 1, m_pFile);

    m_iCurrent += iSize;
    return true;
}

bool FileStream::ReadLine(void* pData, int* pSize)
{
    if (!m_bOpen || m_eMode != FM_READ)
        return false;

    char cBuffer = 0;
    vector<char> vec;
    vec.reserve(128);
    while (feof(m_pFile) == 0)
    {
        fread(&cBuffer, 1, 1, m_pFile);

        if (cBuffer == '\n')
            break;
        vec.push_back(cBuffer);
    }

    *pSize = vec.size();
    memcpy(pData, &vec[0], vec.size());
    m_iCurrent += vec.size();
    return true;
}

bool FileStream::Write(void* pData, int iSize)
{
    if (!m_bOpen || m_eMode != FM_WRITE)
        return false;
    fwrite(pData, iSize, 1, m_pFile);
    return false;
}
