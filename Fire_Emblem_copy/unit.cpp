#include "stdafx.h"
#include "unit.h"

HRESULT unit::init(int idx, int idy)
{
	indexX = idx;
	indexY = idy;
	exp = 0;
	stageRenderCount = 0;
	battleRenderCount = 0;
	return S_OK;
}

void unit::update()
{

}

void unit::release()
{

}

void unit::render()
{

}
