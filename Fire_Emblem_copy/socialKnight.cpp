#include "stdafx.h"
#include "socialKnight.h"

HRESULT socialKnight::init(int idx, int idy, TYPE type)
{
	unit::init(idx, idy,type);
	switch (type)
	{
	case PLAYER:
		_img = IMAGEMANAGER->findImage("¼Ò¼È³ªÀÌÆ®Idle");
		break;
	case ENEMY:
		_img = IMAGEMANAGER->findImage("enemy¼Ò¼È³ªÀÌÆ®Idle");
		break;
	}
	return S_OK;

}

void socialKnight::update()
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

void socialKnight::release()
{
}

void socialKnight::render()
{
	_img->frameRender(_map->getMapDC(), stageX - (TILESIZE / 2), stageY - (TILESIZE), stageRenderX, stageRenderY);
}
