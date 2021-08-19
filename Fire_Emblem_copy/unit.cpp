#include "stdafx.h"
#include "unit.h"
#include "aStarTest.h"

HRESULT unit::init(int idx, int idy ,TYPE type)
{
	_type = type;
	indexX = idx;
	indexY = idy;
	exp = 0;
	stageRenderCount = 0;
	battleRenderCount = 0;
	return S_OK;
}

void unit::update()
{
	if (_type == PLAYER)
	{

	}
	else if (_type  == ENEMY)
	{

	}
}

void unit::release()
{

}

void unit::render()
{

}
