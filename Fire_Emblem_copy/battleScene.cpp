#include "stdafx.h"
#include "battleScene.h"
#include "tileSet.h"

battleScene::battleScene()
{
}


battleScene::~battleScene()
{
}

HRESULT battleScene::init()
{
	battleStage = IMAGEMANAGER->findImage("ÀüÅõHud");
	return S_OK;
}

void battleScene::release()
{
}

void battleScene::update()
{
	if (action)
	{
		_playerCount++;
		_enemyCount++;

		if (_playerCount % 5 == 0)
		{
			_playerIndex++;
			if (_playerIndex > playerimage->getMaxFrameX())
			{
				action = false;
				_playerIndex = 0;
			}
			_playerCount = 0;
		}
	}
	else
	{
		_playerIndex = 0;
		_playerCount = 0;
		_enemyIndex = 0;
		_enemyCount = 0;
	}
}

void battleScene::render(int x , int y)
{
	battleStage->render(_map->getMapDC() , x ,y);
	playerimage->frameRender(_map->getMapDC(), CAMERAMANAGER->getCameraCenterX() , CAMERAMANAGER->getCameraCenterY() - 150 , _playerIndex,0);
	enemyimage->frameRender(_map->getMapDC(), CAMERAMANAGER->getCameraCenterX() - enemyimage->getFrameWidth() , CAMERAMANAGER->getCameraCenterY() - 150 , _enemyIndex,0);

}
