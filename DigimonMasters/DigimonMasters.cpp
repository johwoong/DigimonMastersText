

#include "pch.h"
#include "CGame.h"
int main()
{
	_CrtDumpMemoryLeaks();
	if (!GET_SINGLE(CGame)->Initialize())
	{
		DESTORY_SINGLE(CGame);
		return 0;
	}

	GET_SINGLE(CGame)->Update();

	DESTORY_SINGLE(CGame);
	
}

