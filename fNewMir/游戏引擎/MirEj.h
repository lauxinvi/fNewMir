#ifndef MIREJ_H
#define MIREJ_H
#pragma once

#include "MirEjHead.h"
#include "MirEjTimer.h"
#include "MirEjAudio.h"

class MirEj
{
public:
	MirEj();
	~MirEj();

	bool			Init();
	void			Run();
	void			ShutDown();
	void			Release();

	void			SetWndName(LPWSTR name = L"��紫��") { _wndName = name; }
	void			SethInstance(HINSTANCE hinstance) { _hInstance = hinstance; }
	void			SetIcon(LPCWSTR hicon) { _hicon = (HICON)::LoadImage(NULL, hicon, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE); }
	void			SetWinded(bool winded = true) { _winded = winded; }
	void			SetFPS(int fps) { _dwFixedDelta = fps > 0 ? TIMER_PRECISION / fps : 0; }
	int				SetFPS() { return _nFps; }
private:
	void			RegWnd();
	void			SetStyle();

	HWND			_hWnd;
	LPWSTR			_wndName;
	HINSTANCE		_hInstance;
	HICON			_hicon;
	bool			_winded;
	MirEjTimer		_Timer;					// ��ʱ��
	DEVMODE			_dmScreenSettings;
	int				_posX, _posY;
	DWORD			_dwFixedDelta;			// �趨��֡���
	int				_nFps;					// ʵ��ÿ��֡��
	float			_fDelta;				// ʵ��֡���

	MirEjAudio*		audio;

	static const int TIMER_PRECISION = 10000;
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);// ��Ϣ����ص�����
};
#endif // !MIREJ_H