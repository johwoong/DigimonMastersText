#pragma once
class CObj;


class ObjectManager
{
private:
	unordered_map<string, CObj*> m_mapObj; // ������Ʈ�� ��Ƶ� ����
public:
	bool Init();
	CObj* CreateObject(const string& strKey, OBJECT_TYPE eType);
	CObj* FindObject(const string& strKey);
	CObj* CloneObject(const string& strKey);
	CObj* CloneObject(OBJECT_TYPE eType);
	DECLARE_SINGLE(ObjectManager)
};

