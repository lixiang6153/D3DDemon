// MaterialAlpha.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "MaterialAlpha.h"

#include "WindowBase.h"
#include "D3DWindow.h"
#include "D3DAphla.h"


int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine); 

	CD3DAphla* pD3DObjct = new CD3DAphla;
	CD3DWindow objWindow(hInstance, pD3DObjct);
	objWindow.Create(1920, 1080);	
	objWindow.Show();

	delete pD3DObjct;
	pD3DObjct = NULL;

	return 0;
}
