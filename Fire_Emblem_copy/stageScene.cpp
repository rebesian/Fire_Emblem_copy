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
		if(_pt.indexX > 0 ) _pt.indexX -= 1;
		_pt._rc = _tileSet->getRect(_pt.indexX, _pt.indexY);
		//CAMERAMANAGER->setCameraCenterX(CAMERAMANAGER->getCameraCenterX() - 5);
		if (CAMERAMANAGER->getCameraLEFT() <= 0)
		{
			CAMERAMANAGER->setCameraX(0);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (_pt.indexX <= _tileSet->getSizeX()) _pt.indexX += 1;
		_pt._rc = _tileSet->getRect(_pt.indexX, _pt.indexY);
		//CAMERAMANAGER->setCameraCenterX(CAMERAMANAGER->getCameraCenterX() + 5);
		if (CAMERAMANAGER->getCameraRIGHT() >= mapSizeX * TILESIZE && mapSizeX*TILESIZE >= CAMERAX)
		{
			CAMERAMANAGER->setCameraX(mapSizeX*TILESIZE - CAMERAX);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{

		if (_pt.indexY > 0)_pt.indexY -= 1;
		_pt._rc = _tileSet->getRect(_pt.indexX, _pt.indexY);
		//CAMERAMANAGER->setCameraCenterY(CAMERAMANAGER->getCameraCenterY() - 5);
		if (CAMERAMANAGER->getCameraTOP() <= 0)
		{
			CAMERAMANAGER->setCameraY(0);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (_pt.indexY < _tileSet->getSizeY()) _pt.indexY += 1;
		_pt._rc = _tileSet->getRect(_pt.indexX, _pt.indexY);
		//CAMERAMANAGER->setCameraCenterY(CAMERAMANAGER->getCameraCenterY() + 5);
		if (CAMERAMANAGER->getCameraBOTTOM() >= mapSizeY * TILESIZE && mapSizeY*TILESIZE >= CAMERAY)
		{
			CAMERAMANAGER->setCameraY(mapSizeY*TILESIZE - CAMERAY);
		}
	}
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (_roy->getPlayerSelect())
		{
			_roy->setMoveSelect(true);
		}
		if (_pt.indexX == _warrior->getIndexX() && _pt.indexY == _warrior->getIndexY())
		{
			if (!_warrior->getPlayerSelect())
				_warrior->setPlayerSelect(true);
		}
		if (_pt.indexX == _roy->getIndexX() && _pt.indexY == _roy->getIndexY())
		{
			if (!_roy->getPlayerSelect())
				_roy->setPlayerSelect(true);
		}

	}
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		if (_warrior->getPlayerSelect())
			_warrior->setPlayerSelect(false);
	
		if (_roy->getPlayerSelect())
			_roy->setPlayerSelect(false);
	}
	if (_pt.indexX == _roy->getIndexX() && _pt.indexY == _roy->getIndexY())
	{
		_roy->setpointing(true);
	}
	else
	{
		_roy->setpointing(false);
	}
	_warrior->update(_pt.indexX,_pt.indexY);
	_roy->update(_pt.indexX, _pt.indexY);

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
