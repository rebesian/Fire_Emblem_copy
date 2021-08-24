#include "stdafx.h"
#include "stageScene.h"

HRESULT stageScene::init()
{

	_tileSet = new tileSet;
	_tileSet->init();
	_tileSet->load();

	mapSizeX = _tileSet->getSizeX();
	mapSizeY = _tileSet->getSizeY();

	_warrior = new warrior;
	_warrior->setLinkMap(_tileSet);
	_warrior->init(6, 5,ENEMY);
	
	_roy = new Roy;
	_roy->setLinkMap(_tileSet);
	_roy->init(2, 10);

	_pt.indexX = _roy->getIndexX();
	_pt.indexY = _roy->getIndexY();
	_pt._rc = _tileSet->getRect(_pt.indexX, _pt.indexY);

	return S_OK;
}

void stageScene::update()
{

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{	
		_pt.indexX -= 1;
		_pt._rc = _tileSet->getRect(_pt.indexX, _pt.indexY);
		//CAMERAMANAGER->setCameraCenterX(CAMERAMANAGER->getCameraCenterX() - 5);
		if (CAMERAMANAGER->getCameraLEFT() <= 0)
		{
			CAMERAMANAGER->setCameraX(0);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_pt.indexX += 1;
		_pt._rc = _tileSet->getRect(_pt.indexX, _pt.indexY);
		//CAMERAMANAGER->setCameraCenterX(CAMERAMANAGER->getCameraCenterX() + 5);
		if (CAMERAMANAGER->getCameraRIGHT() >= mapSizeX * TILESIZE && mapSizeX*TILESIZE >= CAMERAX)
		{
			CAMERAMANAGER->setCameraX(mapSizeX*TILESIZE - CAMERAX);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{

		_pt.indexY -= 1;
		_pt._rc = _tileSet->getRect(_pt.indexX, _pt.indexY);
		//CAMERAMANAGER->setCameraCenterY(CAMERAMANAGER->getCameraCenterY() - 5);
		if (CAMERAMANAGER->getCameraTOP() <= 0)
		{
			CAMERAMANAGER->setCameraY(0);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_pt.indexY += 1;
		_pt._rc = _tileSet->getRect(_pt.indexX, _pt.indexY);
		//CAMERAMANAGER->setCameraCenterY(CAMERAMANAGER->getCameraCenterY() + 5);
		if (CAMERAMANAGER->getCameraBOTTOM() >= mapSizeY * TILESIZE && mapSizeY*TILESIZE >= CAMERAY)
		{
			CAMERAMANAGER->setCameraY(mapSizeY*TILESIZE - CAMERAY);
		}
	}
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (_pt.indexX == _warrior->getIndexX() && _pt.indexY == _warrior->getIndexY())
		{
			if (_warrior->getPointing())
				_warrior->setpointing(false);
			else
				_warrior->setpointing(true);
		}
		if (_pt.indexX == _roy->getIndexX() && _pt.indexY == _roy->getIndexY())
		{
			if (_roy->getPointing())
				_roy->setpointing(false);
			else
				_roy->setpointing(true);
		}
	}
	if (_pt.indexX == _roy->getIndexX() && _pt.indexY == _roy->getIndexY())
	{
		
	}
	_warrior->update();
	_roy->update();

}

void stageScene::release()
{

}

void stageScene::render()
{
	

	_tileSet->render();
	_warrior->render();
	_roy->render();
	_pt._img->render(_tileSet->getMapDC() , _pt._rc.left,_pt._rc.top);

	CAMERAMANAGER->render(_tileSet->getTileBuffer(), getMemDC());

}
