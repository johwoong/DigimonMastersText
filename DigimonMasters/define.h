#pragma once
#define SAFE_DELETE(p) if(p) {delete p; p = nullptr;}
#define SAFE_DELETE_ARR(p) if(p) {delete[] p; p = nullptr;}

#define DECLARE_SINGLE(Type)	\
	private:\
		static Type* m_pInst; \
	public:\
		static Type* GetInst()\
	{\
		if (!m_pInst)\
			m_pInst = new Type; \
			return m_pInst; \
	}\
		static void DestoryInst()\
		{\
			SAFE_DELETE(m_pInst); \
		}\
	private:\
			Type(); \
			~Type();

#define DEFINITION_SINGLE(Type) Type* Type::m_pInst = NULL;

#define GET_SINGLE(Type)	Type::GetInst()
#define DESTORY_SINGLE(Type)	Type::DestoryInst()
