#include "��Ϸ�߼�\MirGame.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	MirGame *game = new MirGame;
	game->GameEj()->SetWndName(L"���괫��");
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
		MessageBox(NULL, L"��Ϸ��ʼ��ʧ�ܣ�", L"����", MB_OK | MB_ICONERROR);
	}
	game->ShutDown();
	game->Release();
	return 0;
}