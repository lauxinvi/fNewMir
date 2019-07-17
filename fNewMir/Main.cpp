#include "ÓÎÏ·Âß¼­\MirGame.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	MirGame *game = new MirGame;
	game->GameEj()->SetWndName(L"ÌıÓê´«Ææ");
	game->GameEj()->SethInstance(hInstance);
	game->GameEj()->SetIcon(L"Pics/mir.ico");
	game->GameEj()->SetWinded(true);
	game->GameEj()->SetFPS(25);
	if (game->Init())
	{
		game->Run();
	}
	else
	{
		MessageBox(NULL, L"ÓÎÏ·³õÊ¼»¯Ê§°Ü£¡", L"´íÎó", MB_OK | MB_ICONERROR);
	}
	game->ShutDown();
	game->Release();
	return 0;
}