#pragma once

class CGame
{
private:
	bool isPlayer;
public:
	DECLARE_SINGLE(CGame)

public:
	bool Initialize();
	void Update();
	void Release();
	void CheckGameMode();
	void SetPlayer();
};

