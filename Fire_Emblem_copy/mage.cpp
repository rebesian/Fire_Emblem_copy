#include "stdafx.h"
#include "mage.h"

HRESULT mage::init(int idx, int idy, TYPE type)
{
	unit::init(idx, idy, type);

	_img = IMAGEMANAGER->findImage("¸ÞÀÌÁöIdle");
	return S_OK;
}

void mage::update()
{
	stageRenderCount++;
	if (stageRenderCount % 7 == 0)
	{
		if (stageRenderX == 2)
		{
			if (stageRenderCount > 20)
				stageRenderX = 0;
		}
		else
		{
			stageRenderX++;
			stageRenderCount = 0;
		}
	}
}

void mage::release()
{
}

void mage::render()
{
	_img->frameRender(_map->getMapDC(), stageX - (TILESIZE / 2), stageY - (TILESIZE), stageRenderX, stageRenderY);
}
