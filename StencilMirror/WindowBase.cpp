#include "StdAfx.h"
#include "WindowBase.h"
#include "Resource.h"

CWindowBase::CWindowBase(HINSTANCE hInstance)
: m_hWnd(NULL)
, m_hInstance(hInstance)
, m_nWidth(0)
, m_nHeight(0)
{
}

CWindowBase::~CWindowBase(void)
{
}

LRESULT CALLBACK CWindowBase::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch( message )
	{
	case WM_DESTROY:
		{
			::PostQuitMessage(0);
		}
		break;
	case WM_KEYDOWN:	
		{
			if( wParam == VK_ESCAPE )
			{
				::DestroyWindow(hWnd);
			}
		}
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

bool CWindowBase::Create(int nWidth /*= 1920*/, int nHeight /*= 1080*/)
{
	WNDCLASSEX stWndClass;
	ZeroMemory(&stWndClass, sizeof(stWndClass));

	stWndClass.cbSize = sizeof(WNDCLASSEX);
	stWndClass.style			= CS_HREDRAW | CS_VREDRAW;
	stWndClass.lpfnWndProc		= WndProc;
	stWndClass.cbClsExtra		= 0;
	stWndClass.cbWndExtra		= 0;
	stWndClass.hInstance		= m_hInstance;
	stWndClass.hIcon			= LoadIcon(0, IDI_APPLICATION);
	stWndClass.hCursor			= LoadCursor(0, IDC_ARROW);
	stWndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	stWndClass.lpszClassName	= _T("CWindowBase");
	stWndClass.hIconSm			= LoadIcon(stWndClass.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	stWndClass.lpszMenuName		= 0;
	if (!RegisterClassEx(&stWndClass))
		return false;

	m_hWnd = CreateWindow(_T("CWindowBase"), _T("lixiang6153@126.com-D3D Game"), WS_EX_TOPMOST,
						  0, 0, nWidth, nHeight, NULL, NULL, 
						  m_hInstance, NULL);

	if (!m_hWnd)
	{
		return FALSE;
	}

// 	int nSWidth = GetSystemMetrics(SM_CXSCREEN);
// 	int nSHeight = GetSystemMetrics(SM_CYSCREEN);
// 	::MoveWindow(m_hWnd, (nSWidth-nWidth)/2, (nSHeight-nHeight)/2, nWidth, nHeight, TRUE);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	m_nWidth = nWidth;
	m_nHeight = nHeight;

	return true;
}

void CWindowBase::Destroy()
{
	if (NULL != m_hWnd)
	{
		::DestroyWindow(m_hWnd);
		m_hWnd = NULL;
	}
}

HWND CWindowBase::GetHWnd()
{
	return m_hWnd;
}

int  CWindowBase::GetWidth(bool bClient/* = true*/)
{
	return m_nWidth;
}

int  CWindowBase::GetHeight(bool bClient/* = true*/)
{
	return m_nHeight;
}
