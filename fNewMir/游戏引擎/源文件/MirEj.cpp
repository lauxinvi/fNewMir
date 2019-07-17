#include "..\MirEj.h"

MirEj::MirEj()
{
	audio = new MirEjAudio;
}

MirEj::~MirEj()
{
}

bool MirEj::Init()
{
	RegWnd();
	SetStyle();
	return true;
}

void MirEj::Run()
{
	MSG msg = { 0 };
	_Timer.Play();
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			DWORD dwTime = _Timer.GetTime();
			if (dwTime >= _dwFixedDelta)		// ����ﵽҪ��
			{
				_Timer.Stop();// ���ü�ʱ��
				_Timer.Play();
				if (dwTime != 0) { _nFps = TIMER_PRECISION / dwTime; }// ����FPS
				else { _nFps = TIMER_PRECISION; }
				_fDelta = (float)dwTime / TIMER_PRECISION;// ������
				// ִ�г����߼�
				//INPUT.Update();
				//GUI.Update();
			}
		}
	}
}

LRESULT CALLBACK MirEj::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:PostQuitMessage(0);break;
	case WM_LBUTTONDOWN://mirej->OnLBtnDown(wParam, lParam);break;
	case WM_LBUTTONUP://mirej->OnLBtnUp(wParam, lParam);break;
	//case WM_MY_MSG:
	//	switch (wParam)
	//	{
	//	case BTN_LOGIN_CLOSE:PostQuitMessage(0);break;
	//	case BTN_LOGIN_SUBMIT:mirej->ChangScene(lParam, SCENE_SELECT);break;
	//	case BTN_NEWUSER_SUBMIT:break;
	//	case BTN_REPASS_SUBMIT:break;
	//	case BTN_LOGIN_NEWUSER:mirej->ChangeFrm(lParam, LOGIN_NEWUSER);break;
	//	case BTN_LOGIN_REPASS:mirej->ChangeFrm(lParam, LOGIN_REPASS);break;
	//	case BTN_NEWUSER_CANEL:
	//	case BTN_NEWUSER_CLOSE:mirej->ChangeFrm(lParam, LOGIN_LOGIN);break;
	//	case BTN_REPASS_CANEL:mirej->ChangeFrm(lParam, LOGIN_LOGIN);break;
	//	}
	//	break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}

void MirEj::ShutDown()
{

}

void MirEj::Release()
{
	audio->Release();
}

void MirEj::RegWnd()
{
	// ע�ᴰ��
	WNDCLASSEX wndClass = { 0 };							//��WINDCLASSEX������һ��������
	wndClass.cbSize = sizeof(WNDCLASSEX);			//���ýṹ����ֽ�����С
	wndClass.style = CS_HREDRAW | CS_VREDRAW;	//���ô��ڵ���ʽ
	wndClass.lpfnWndProc = WndProc;					//����ָ�򴰿ڹ��̺�����ָ��
	wndClass.cbClsExtra = 0;								//������ĸ����ڴ棬ȡ0�Ϳ�����
	wndClass.cbWndExtra = 0;							//���ڵĸ����ڴ棬��Ȼȡ0������
	wndClass.hInstance = _hInstance;						//ָ���������ڹ��̵ĳ����ʵ�������
	wndClass.hIcon = _hicon;								//	�ƶ�ͼ��
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);    //ָ��������Ĺ������
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName = NULL;						//��һ���Կ���ֹ���ַ�����ָ���˵���Դ�����֡�
	wndClass.lpszClassName = _wndName;		//��һ���Կ���ֹ���ַ�����ָ������������֡�WNDCLASS wc;

	RegisterClassEx(&wndClass);			//����괰�ں���Ҫ�Դ��������ע�ᣬ�������ܴ��������͵Ĵ���
}

void MirEj::SetStyle()
{
	// �����Ƿ�ȫ�����ò�ͬ�ķֱ���.
	if (!_winded)
	{
		//ȫ��ģʽ�£����ô��ڴ�СΪwindows����ֱ���.
		memset(&_dmScreenSettings, 0, sizeof(_dmScreenSettings));
		_dmScreenSettings.dmSize = sizeof(_dmScreenSettings);
		_dmScreenSettings.dmPelsWidth = (unsigned long)WINDOWWIDTH;
		_dmScreenSettings.dmPelsHeight = (unsigned long)WINDOWHEIGHT;
		_dmScreenSettings.dmBitsPerPel = 32;
		_dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// ��ʱ������ʾ�豸Ϊȫ��ģʽ��ע�⣺Ӧ�ó����˳�ʱ�򣬽��ָ�ϵͳĬ�����á�
		ChangeDisplaySettings(&_dmScreenSettings, CDS_FULLSCREEN);

		// ���ô��ڵ�Ĭ��λ��Ϊ(0,0).
		_posX = _posY = 0;
	}
	else
	{
		// ����λ��,posX, posY�������Ͻ�����
		_posX = (GetSystemMetrics(SM_CXSCREEN) - WINDOWWIDTH) / 2;
		_posY = (GetSystemMetrics(SM_CYSCREEN) - WINDOWHEIGHT) / 2;
	}

	// ȫ���ʹ���ʹ�ò�ͬ�Ĳ���.
	if (!_winded)
	{
		_hWnd = CreateWindowEx(WS_EX_APPWINDOW, _wndName, _wndName,
			WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
			_posX, _posY, WINDOWWIDTH, WINDOWHEIGHT, NULL, NULL, _hInstance, NULL);
	}
	else
	{
		_hWnd = CreateWindowEx(WS_EX_APPWINDOW, _wndName, _wndName,
			WS_POPUPWINDOW | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
			_posX, _posY, WINDOWWIDTH, WINDOWHEIGHT, NULL, NULL, _hInstance, NULL);
	}
	RECT crec, wrec;
	GetClientRect(_hWnd, &crec);
	GetWindowRect(_hWnd, &wrec);
	int x = (wrec.right - wrec.left) - (crec.right - crec.left);
	int y = (wrec.bottom - wrec.top) - (crec.bottom - crec.top);
	SetWindowPos(_hWnd, 0, 0, 0, WINDOWWIDTH + x, WINDOWHEIGHT + y, SWP_NOMOVE | SWP_NOZORDER);
	// ��ʾ���ڲ�������Ϊ����.
	ShowWindow(_hWnd, SW_SHOW);
	SetForegroundWindow(_hWnd);
	SetFocus(_hWnd);
	ShowCursor(true);
	UpdateWindow(_hWnd);
}