#pragma once
#include <D3DX9.h>
#pragma comment(lib, "D3DX9.lib")
#pragma comment(lib, "D3D9.lib")
#pragma comment(lib, "winmm.lib")

const D3DXCOLOR   WHITE( D3DCOLOR_XRGB(255, 255, 255) );
const D3DXCOLOR   BLACK( D3DCOLOR_XRGB(  0,   0,   0) );
const D3DXCOLOR   RED( D3DCOLOR_XRGB(255,   0,   0) );
const D3DXCOLOR   GREEN( D3DCOLOR_XRGB(  0, 255,   0) );
const D3DXCOLOR   BLUE( D3DCOLOR_XRGB(  0,   0, 255) );
const D3DXCOLOR   YELLOW( D3DCOLOR_XRGB(255, 255,   0) );
const D3DXCOLOR   CYAN( D3DCOLOR_XRGB(  0, 255, 255) );
const D3DXCOLOR   MAGENTA( D3DCOLOR_XRGB(255,   0, 255) );

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
	static D3DMATERIAL9 InitMaterial(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p);
	static D3DLIGHT9    InitPointLight(D3DXVECTOR3* position, D3DXCOLOR* color);
	static D3DLIGHT9    InitDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color);

protected:
	IDirect3DDevice9*	m_pDirect3DDevice;
};

const D3DMATERIAL9 WHITE_MTRL  = CD3DBase::InitMaterial(WHITE, WHITE, WHITE, BLACK, 2.0f);
const D3DMATERIAL9 RED_MTRL    = CD3DBase::InitMaterial(RED, RED, RED, BLACK, 2.0f);
const D3DMATERIAL9 GREEN_MTRL  = CD3DBase::InitMaterial(GREEN, GREEN, GREEN, BLACK, 2.0f);
const D3DMATERIAL9 BLUE_MTRL   = CD3DBase::InitMaterial(BLUE, BLUE, BLUE, BLACK, 2.0f);
const D3DMATERIAL9 YELLOW_MTRL = CD3DBase::InitMaterial(YELLOW, YELLOW, YELLOW, BLACK, 2.0f);
