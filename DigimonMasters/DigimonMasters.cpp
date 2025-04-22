// DigimonMasters.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include "CGame.h"
int main()
{
	if (!GET_SINGLE(CGame)->Initialize())
	{
		DESTORY_SINGLE(CGame);
		return 0;
	}

	GET_SINGLE(CGame)->Update();

	DESTORY_SINGLE(CGame);
	
}

