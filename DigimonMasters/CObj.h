#pragma once
class CObj
{
protected:
	CObj();
	CObj(const CObj& obj);
	virtual ~CObj() = 0;
private:
	friend class ObjectManager;
private:
	string strName;
protected:
	OBJECT_TYPE m_eType;

public:
	virtual bool Init() = 0;
	virtual void Render() = 0;
	virtual CObj* Clone() = 0;

public:
	void SetName(string name) { strName = name; }
	string GetName() const { return strName; }
	OBJECT_TYPE GetObjectType() const { return m_eType; }
};

