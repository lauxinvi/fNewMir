#ifndef MIRGAME_H
#define MIRGAME_H
#pragma once

#include "MirGameHead.h"
#include "..\��Ϸ����\MirEj.h"

class MirGame
{
public:
	MirGame();
	~MirGame();

	bool		Init();
	void		Run();
	void		ShutDown();
	void		Release();

	MirEj*		GameEj() { return mirej; }
private:
	MirEj*		mirej;
};
#endif // !MIRGAME_H