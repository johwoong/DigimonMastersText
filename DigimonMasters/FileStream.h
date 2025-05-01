#pragma once
class FileStream
{
public:
	FileStream();
	FileStream(const char* pFileName, const char* pMode);
	~FileStream();

private:
	enum FILE_MODE
	{
		FM_READ,
		FM_WRITE,
	};

private:
	FILE* m_pFile;
	bool m_bOpen;
	FILE_MODE m_eMode;
	int	m_iFileSize;
	int m_iCurrent;

public:
	bool GetOpen() const
	{
		return m_bOpen;
	}

	int GetFileSize() const { return m_iFileSize; }

public:
	bool Open(const char* pFileName, const char* pMode);
	bool Close();
	bool Read(void* pData, int iSize);
	bool ReadLine(void* pData, int* pSize);
	bool Write(void* pData, int iSize);

};

