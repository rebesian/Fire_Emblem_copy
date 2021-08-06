#include "stdafx.h"
#include "mapTool.h"

HRESULT mapTool::init()
{
	_ctrSelect = CTRL_TERRAINDRAW;

	return S_OK;
}

void mapTool::update()
{

}

void mapTool::release()
{

}

void mapTool::render()
{

}

void mapTool::selectTileSet()
{
	for (int i = 0; i < SAMPLEGRASSY*SAMPLEGRASSX; ++i)
	{

		if (PtInRect(&_TR_GRASS[i].tileRc, _ptMouse))
		{

		}
	}

}
