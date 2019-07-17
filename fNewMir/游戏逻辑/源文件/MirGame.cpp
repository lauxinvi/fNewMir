#include "..\MirGame.h"

MirGame::MirGame()
{
	mirej = new MirEj;
}

MirGame::~MirGame()
{
}

bool MirGame::Init()
{
	mirej->Init();
	return true;
}

void MirGame::Run()
{
	mirej->Run();
}

void MirGame::ShutDown()
{

}

void MirGame::Release()
{
	mirej->Release();
}