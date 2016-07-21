// StencilMirror.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "StencilMirror.h"

#include "WindowBase.h"
#include "D3DWindow.h"
#include "D3DMirror.h"


int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine); 

	CD3DMirror* pD3DObjct = new CD3DMirror;
	CD3DWindow objWindow(hInstance, pD3DObjct);
	objWindow.Create(1920, 1080);	
	objWindow.Show();

	delete pD3DObjct;
	pD3DObjct = NULL;

	return 0;
}