#pragma once
#include "d3dbase.h"

class CD3DLight :
	public CD3DBase
{
public:
	CD3DLight(void);
	virtual ~CD3DLight(void);

	virtual bool Init(HWND hWnd, int nWidth, int nHeight, bool bFullScreen = true);
	virtual void UnInit();
	virtual void Draw();

protected:
	IDirect3DVertexBuffer9*	m_pVertexBuffer;
	// 由于所有公共定点的法向量不相同，所以不适用与索引缓存
};
