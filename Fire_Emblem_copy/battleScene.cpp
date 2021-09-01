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
	battleStage = IMAGEMANAGER->findImage("����Hud");
	playerimage = IMAGEMANAGER->findImage("�Ҽȳ���Ʈattack");
	enemyimage = IMAGEMANAGER->findImage("enemy����attack");
	return S_OK;
}

void battleScene::release()
{
}

void battleScene::update(TYPE type)
{
	if (action)
	{
		if (type == PLAYER)
		{
			_playerCount++;
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
			playerAction(_playerName);
		}
		else if (type == ENEMY)
		{
			enemyAction(_enemyName);
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
	playerimage->frameRender(_map->getMapDC(), _playerActionX, _playerActionY, _playerIndex, 0);
	enemyimage->frameRender(_map->getMapDC(), _enemyActionX, _enemyActionY, _enemyIndex, 0);
}

void battleScene::playerStart(string name)
{
	if (name == "����attack")
	{
		_playerActionX = CAMERAMANAGER->getCameraCenterX();
		_playerActionY = 546 - playerimage->getFrameWidth();
	}
	else if (name == "�Ҽȳ���Ʈattack")
	{
		_playerActionX = CAMERAMANAGER->getCameraCenterX() - 80;
		_playerActionY = 546 - playerimage->getFrameWidth();
	}
	else if (name == "����attack")
	{
		_playerActionX = CAMERAMANAGER->getCameraCenterX() - 48;
		_playerActionY = 546 - playerimage->getFrameWidth() + 48;
	}
	else if (name == "�ȶ��attack")
	{
		_playerActionX = CAMERAMANAGER->getCameraCenterX() - 90;
		_playerActionY = 546 - playerimage->getFrameWidth() - 15;
	}
	else if (name == "�Ƹӳ���Ʈattack")
	{
		_playerActionX = CAMERAMANAGER->getCameraCenterX() - 80;
		_playerActionY = 546 - playerimage->getFrameWidth() - 20;
	}

}

void battleScene::enemyStart(string name)
{
	if (name == "enemy�Ҽȳ���Ʈattack")
	{
		_enemyActionX = CAMERAMANAGER->getCameraCenterX() - enemyimage->getFrameWidth() + 80;
		_enemyActionY = 546 - enemyimage->getFrameWidth();
	}
	else if (name == "enemy����attack")
	{
		_enemyActionX = CAMERAMANAGER->getCameraCenterX() - enemyimage->getFrameWidth() + 50;
		_enemyActionY = 546 - enemyimage->getFrameWidth() + 48;
	}
	else if (name == "enemy����attack")
	{
		_enemyActionX = CAMERAMANAGER->getCameraCenterX() - enemyimage->getFrameWidth() + 20;
		_enemyActionY = 546 - enemyimage->getFrameWidth();
	}
	else if (name == "enemy�Ƹӳ���Ʈattack")
	{
		_enemyActionX = CAMERAMANAGER->getCameraCenterX() - enemyimage->getFrameWidth() + 80;
		_enemyActionY = 546 - enemyimage->getFrameWidth() - 20;
	}
}

void battleScene::playerAction(string name)
{
	if (name == "����attack")
	{
		//if (_playerIndex == 0)
		//{
		//	_playerCount++;
		//	if (_playerCount % 5 == 0)
		//	{
		//		_playerIndex++;
		//		if (_playerIndex > playerimage->getMaxFrameX())
		//		{
		//			//action = false;
		//			_playerIndex = 0;
		//		}
		//		_playerCount = 0;
		//	}
		//}
		//else
		//
	}
	else if(name == "�Ҽȳ���Ʈattack")
	{

	}
	else if (name == "����attack")
	{

	}
	else if (name == "�ȶ��attack")
	{

	}
	else if (name == "�Ƹӳ���Ʈattack")
	{

	}


}

void battleScene::enemyAction(string name)
{

	if (name == "enemy�Ҽȳ���Ʈattack")
	{

	}
	else if (name == "enemy����attack")
	{

	}
	else if (name == "enemy�ȶ��attack")
	{

	}
	else if (name == "enemy�Ƹӳ���Ʈattack")
	{

	}

}
