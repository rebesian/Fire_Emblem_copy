#include "stdafx.h"
#include "Roy.h"

HRESULT Roy::init(int idx, int idy, TYPE type)
{
	unit::init(idx, idy, type);
	_img = IMAGEMANAGER->findImage("·ÎÀÌIdle");
	return S_OK;
}

void Roy::update()
{
	stageRenderCount++;
	if (stageRenderCount % 7 == 0)
	{
		if (stageRenderX == 2)
		{
			if(stageRenderCount>20)
			stageRenderX = 0;
		}
		else
		{
			stageRenderX++;
			stageRenderCount = 0;
		}
	}
}

void Roy::release()
{

}

void Roy::render()
{
	_img->frameRender(_map->getMapDC(), stageX-(TILESIZE/2), stageY-(TILESIZE), stageRenderX, stageRenderY);


}
