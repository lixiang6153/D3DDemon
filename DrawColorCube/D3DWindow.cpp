#include "StdAfx.h"
#include "D3DWindow.h"
#include <stdio.h>
#include <MMSystem.h>
#pragma comment(lib, "winmm.lib")

CD3DWindow::CD3DWindow(HINSTANCE hInstance,CD3DBase* pD3DBase)
: CWindowBase(hInstance)
, m_pD3DBase(pD3DBase)
{
}

CD3DWindow::~CD3DWindow(void)
{
}

void CD3DWindow::Show()
{
	m_pD3DBase->Init(GetHWnd(), GetWidth(), GetHeight(), true);
	m_pD3DBase->Setup(GetWidth(), GetHeight());

	MSG msg = {0};
	while (msg.message != WM_QUIT)
	{
		static float lastTime = (float)timeGetTime();
		if (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			float currTime  = (float)timeGetTime();
			float timeDelta = (currTime - lastTime)*0.001f;

			m_pD3DBase->Draw();

			lastTime = currTime;
		}
	}

	m_pD3DBase->UnInit();
	Destroy();
}