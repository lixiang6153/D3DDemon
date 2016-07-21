#pragma once
#include <D3DX9.h>
#pragma comment(lib, "D3DX9.lib")
#pragma comment(lib, "D3D9.lib")
#pragma comment(lib, "winmm.lib")

class CD3DBase
{
public:
	CD3DBase(void);
	virtual ~CD3DBase(void);

public:
	virtual bool Init(HWND hWnd, int nWidth, int nHeight, bool bFullScreen = true);
	virtual void UnInit();
	virtual void Draw();

public:
	void Setup(int nWidth, int nHeight);

protected:
	IDirect3DDevice9*	m_pDirect3DDevice;
};
