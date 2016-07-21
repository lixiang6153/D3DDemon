#pragma once
#include "windowbase.h"
#include "D3DBase.h"

class CD3DWindow :
	public CWindowBase
{
public:
	CD3DWindow(HINSTANCE hInstance,CD3DBase* pD3DBase);
	virtual ~CD3DWindow(void);

public:
	void Show();

protected:
	CD3DBase*	m_pD3DBase;
};
