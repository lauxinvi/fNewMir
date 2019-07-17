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
			if (dwTime >= _dwFixedDelta)		// 间隔达到要求
			{
				_Timer.Stop();// 重置计时器
				_Timer.Play();
				if (dwTime != 0) { _nFps = TIMER_PRECISION / dwTime; }// 计算FPS
				else { _nFps = TIMER_PRECISION; }
				_fDelta = (float)dwTime / TIMER_PRECISION;// 计算间隔
				// 执行程序逻辑
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
	// 注册窗口
	WNDCLASSEX wndClass = { 0 };							//用WINDCLASSEX定义了一个窗口类
	wndClass.cbSize = sizeof(WNDCLASSEX);			//设置结构体的字节数大小
	wndClass.style = CS_HREDRAW | CS_VREDRAW;	//设置窗口的样式
	wndClass.lpfnWndProc = WndProc;					//设置指向窗口过程函数的指针
	wndClass.cbClsExtra = 0;								//窗口类的附加内存，取0就可以了
	wndClass.cbWndExtra = 0;							//窗口的附加内存，依然取0就行了
	wndClass.hInstance = _hInstance;						//指定包含窗口过程的程序的实例句柄。
	wndClass.hIcon = _hicon;								//	制定图标
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);    //指定窗口类的光标句柄。
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName = NULL;						//用一个以空终止的字符串，指定菜单资源的名字。
	wndClass.lpszClassName = _wndName;		//用一个以空终止的字符串，指定窗口类的名字。WNDCLASS wc;

	RegisterClassEx(&wndClass);			//设计完窗口后，需要对窗口类进行注册，这样才能创建该类型的窗口
}

void MirEj::SetStyle()
{
	// 根据是否全屏设置不同的分辨率.
	if (!_winded)
	{
		//全屏模式下，设置窗口大小为windows桌面分辨率.
		memset(&_dmScreenSettings, 0, sizeof(_dmScreenSettings));
		_dmScreenSettings.dmSize = sizeof(_dmScreenSettings);
		_dmScreenSettings.dmPelsWidth = (unsigned long)WINDOWWIDTH;
		_dmScreenSettings.dmPelsHeight = (unsigned long)WINDOWHEIGHT;
		_dmScreenSettings.dmBitsPerPel = 32;
		_dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// 临时设置显示设备为全屏模式，注意：应用程序退出时候，将恢复系统默认设置。
		ChangeDisplaySettings(&_dmScreenSettings, CDS_FULLSCREEN);

		// 设置窗口的默认位置为(0,0).
		_posX = _posY = 0;
	}
	else
	{
		// 窗口位置,posX, posY窗口左上角坐标
		_posX = (GetSystemMetrics(SM_CXSCREEN) - WINDOWWIDTH) / 2;
		_posY = (GetSystemMetrics(SM_CYSCREEN) - WINDOWHEIGHT) / 2;
	}

	// 全屏和窗口使用不同的参数.
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
	// 显示窗口并设置其为焦点.
	ShowWindow(_hWnd, SW_SHOW);
	SetForegroundWindow(_hWnd);
	SetFocus(_hWnd);
	ShowCursor(true);
	UpdateWindow(_hWnd);
}