#include "stdafx.h"
#include "mapToolScene.h"

HRESULT mapToolScene::init()
{
	_mapTool = new mapTool;
	_tileSet = new tileSet;
	_mapTool->init();
	_tileSet->init();
	_mapTool->setLinkMemoryTileSet(_tileSet);
	_mapTool->setUp();
	return S_OK;
}

void mapToolScene::release()
{

}

void mapToolScene::update()
{
	_mapTool->update();

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		CAMERAMANAGER->setCameraX(CAMERAMANAGER->getCameraLEFT() - 48);
		if (CAMERAMANAGER->getCameraLEFT() <= 0)
		{
			CAMERAMANAGER->setCameraX(0);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		CAMERAMANAGER->setCameraX(CAMERAMANAGER->getCameraLEFT() + 48);
		if (CAMERAMANAGER->getCameraRIGHT() >= _tileSet->getSizeX() * TILESIZE && _tileSet->getSizeX() *TILESIZE >= CAMERAX)
		{
			CAMERAMANAGER->setCameraX(_tileSet->getSizeX() *TILESIZE - CAMERAX);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		CAMERAMANAGER->setCameraY(CAMERAMANAGER->getCameraTOP() - 48);
		if (CAMERAMANAGER->getCameraTOP() <= 0)
		{
			CAMERAMANAGER->setCameraY(0);
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		CAMERAMANAGER->setCameraY(CAMERAMANAGER->getCameraTOP() + 48);
		if (CAMERAMANAGER->getCameraBOTTOM() >= _tileSet->getSizeY() * TILESIZE && _tileSet->getSizeY()*TILESIZE >= CAMERAY)
		{
			CAMERAMANAGER->setCameraY(_tileSet->getSizeY()*TILESIZE - CAMERAY);
		}
	}
}

void mapToolScene::render()
{
	
	_tileSet->render();
	CAMERAMANAGER->render(_tileSet->getTileBuffer(), getMemDC());
	_mapTool->render();
	
}
