#pragma once

class CWindowBase
{
public:
	CWindowBase(HINSTANCE hInstance);
	virtual ~CWindowBase(void);

public:
	bool Create(int nWidth = 1920, int nHeight = 1080);
	void Destroy();

public:
	HWND GetHWnd();
	int  GetWidth(bool bClient = true);
	int  GetHeight(bool bClient = true);

protected:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

protected:
	int			m_nWidth, m_nHeight;
	HINSTANCE	m_hInstance;
	HWND		m_hWnd;
};
