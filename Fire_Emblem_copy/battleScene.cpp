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
	battleStage = IMAGEMANAGER->findImage("전투Hud");
	playerimage = IMAGEMANAGER->findImage("팔라딘attack");
	enemyimage = IMAGEMANAGER->findImage("enemy군인attack");
	_playerName = "로이attack";
	_enemyName = "enemy군인attack";
	playerStart(_playerName);
	enemyStart(_enemyName);
	action = true;
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
		if (KEYMANAGER->isOnceKeyDown('R'))
		{
			action = true;
		}
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
	if (name == "로이attack")
	{
		_playerActionX = CAMERAMANAGER->getCameraCenterX();
		_playerActionY = 546 - playerimage->getFrameWidth();
	}
	else if (name == "소셜나이트attack")
	{
		_playerActionX = CAMERAMANAGER->getCameraCenterX() - 80;
		_playerActionY = 546 - playerimage->getFrameWidth();
	}
	else if (name == "전사attack")
	{
		_playerActionX = CAMERAMANAGER->getCameraCenterX() - 48;
		_playerActionY = 546 - playerimage->getFrameWidth() + 48;
	}
	else if (name == "팔라딘attack")
	{
		_playerActionX = CAMERAMANAGER->getCameraCenterX() - 90;
		_playerActionY = 546 - playerimage->getFrameWidth() - 15;
	}
	else if (name == "아머나이트attack")
	{
		_playerActionX = CAMERAMANAGER->getCameraCenterX() - 80;
		_playerActionY = 546 - playerimage->getFrameWidth() - 20;
	}

}

void battleScene::enemyStart(string name)
{
	if (name == "enemy소셜나이트attack")
	{
		_enemyActionX = CAMERAMANAGER->getCameraCenterX() - enemyimage->getFrameWidth() + 80;
		_enemyActionY = 546 - enemyimage->getFrameWidth();
	}
	else if (name == "enemy전사attack")
	{
		_enemyActionX = CAMERAMANAGER->getCameraCenterX() - enemyimage->getFrameWidth() + 50;
		_enemyActionY = 546 - enemyimage->getFrameWidth() + 48;
	}
	else if (name == "enemy군인attack")
	{
		_enemyActionX = CAMERAMANAGER->getCameraCenterX() - enemyimage->getFrameWidth() + 20;
		_enemyActionY = 546 - enemyimage->getFrameWidth();
	}
	else if (name == "enemy아머나이트attack")
	{
		_enemyActionX = CAMERAMANAGER->getCameraCenterX() - enemyimage->getFrameWidth() + 80;
		_enemyActionY = 546 - enemyimage->getFrameWidth() - 20;
	}
}

void battleScene::playerAction(string name)
{
	if (name == "로이attack")
	{
		if (_playerIndex == 0)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 1 && _playerIndex <=2)
		{
			_playerCount++;
			if (_playerCount % 5 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex == 3)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 4 && _playerIndex <= 5)
		{

			_playerCount++;
			if (_playerIndex == 5)
			{
				if (_playerCount > 30)
				{
					_playerIndex++;
					_playerCount = 0;
				}
			}
			else if (_playerCount % 5 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}

		}
		else if (_playerIndex >= 6 && _playerIndex <= 7)
		{

			_playerCount++;
			if (_playerCount % 5 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex == 8)
		{

			_playerCount++;
			if (_playerCount > 30)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 9 && _playerIndex <= 12)
		{

			_playerCount++;
			if (_playerCount % 5 ==0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 13 && _playerIndex<=23)
		{

			_playerCount++;
			if (_playerCount % 5 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex == 24)
		{
			_playerCount++;
			if (_playerCount >30)
			{
				action = false;
				_playerCount = 0;
			}
		}
	}
	else if(name == "소셜나이트attack")
	{
		if (_playerIndex == 0)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 1 && _playerIndex <= 2)
		{
			_playerCount++;
			if (_playerCount % 10 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex == 3)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 4 && _playerIndex <=10)
		{
			_playerCount++;
			if (_playerCount % 5 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if ( _playerIndex == 11)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 12 && _playerIndex<=13)
		{
			_playerCount++;
			if (_playerCount % 10 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex == 14)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				action = false;
				_playerCount = 0;
			}
		}
	}
	else if (name == "전사attack")
	{
		if (_playerIndex == 0)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 1 && _playerIndex <= 4)
		{
			_playerCount++;
			if (_playerCount % 7 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex == 5)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 6 && _playerIndex <= 7)
		{
			_playerCount++;
			if (_playerCount % 15 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 8 && _playerIndex <= 10)
		{
			_playerCount++;
			if (_playerCount % 10 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex == 11)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				action = false;
				_playerCount = 0;
			}
		}
	}
	else if (name == "팔라딘attack")
	{
		if (_playerIndex == 0)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 1 && _playerIndex <= 3)
		{
			_playerCount++;
			if (_playerCount % 10 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex == 4)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 5 && _playerIndex <= 6)
		{
			_playerCount++;
			if (_playerCount % 5 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex == 7)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 8 && _playerIndex <= 12)
		{
			_playerCount++;
			if (_playerCount % 3 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 13 && _playerIndex <= 20)
		{
			_playerCount++;
			if (_playerCount % 5 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 21 && _playerIndex <= 25)
		{
			_playerCount++;
			if (_playerCount % 7 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex == 26)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 27 && _playerIndex <= 29)
		{
			_playerCount++;
			if (_playerCount % 7 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex == 30)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				action = false;
				_playerCount = 0;
			}
		}
	}
	else if (name == "아머나이트attack")
	{
		if (_playerIndex == 0)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 1 && _playerIndex <= 5)
		{
			_playerCount++;
			if (_playerCount % 7 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 6 && _playerIndex <= 8)
		{
			_playerCount++;
			if (_playerCount % 5 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex == 9)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 10 && _playerIndex <= 12)
		{
			_playerCount++;
			if (_playerCount % 10 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 13 && _playerIndex <= 17)
		{
			_playerCount++;
			if (_playerCount % 10 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex == 18)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				action = false;
				_playerCount = 0;
			}
		}
	}


}

void battleScene::enemyAction(string name)
{

	if (name == "enemy소셜나이트attack")
	{
		if (_enemyIndex == 0)
		{
			_enemyIndex++;
			if (_enemyCount > 30)
			{
				_enemyIndex++;
				_enemyCount = 0;
			}
		}
		else if (_enemyIndex >= 1 && _enemyIndex <= 2)
		{
			_enemyCount++;
			if (_enemyCount % 10 == 0)
			{
				_enemyIndex++;
				_enemyCount = 0;
			}
		}
		else if (_enemyIndex == 3)
		{
			_enemyCount++;
			if (_enemyCount > 30)
			{
				_enemyIndex++;
				_enemyCount = 0;
			}
		}
		else if (_enemyIndex >= 4 && _enemyIndex <= 10)
		{
			_enemyCount++;
			if (_enemyCount % 5 == 0)
			{
				_enemyIndex++;
				_enemyCount = 0;
			}
		}
		else if (_enemyIndex == 11)
		{
			_enemyCount++;
			if (_enemyCount > 30)
			{
				_enemyIndex++;
				_enemyCount = 0;
			}
		}
		else if (_enemyIndex >= 12 && _enemyIndex <= 13)
		{
			_enemyCount++;
			if (_enemyCount % 10 == 0)
			{
				_enemyIndex++;
				_enemyCount = 0;
			}
		}
		else if (_playerIndex == 14)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				action = false;
				_playerCount = 0;
			}
		}
	}
	else if (name == "enemy전사attack")
	{
		if (_playerIndex == 0)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 1 && _playerIndex <= 4)
		{
			_playerCount++;
			if (_playerCount % 7 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex == 5)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 6 && _playerIndex <= 7)
		{
			_playerCount++;
			if (_playerCount % 15 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 8 && _playerIndex <= 10)
		{
			_playerCount++;
			if (_playerCount % 10 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex == 11)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				action = false;
				_playerCount = 0;
			}
		}
	}
	else if (name == "enemy군인attack")
	{
		if (_playerIndex == 0)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 1 && _playerIndex <= 4)
		{
			_playerCount++;
			if (_playerCount % 7 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex == 5)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 6 && _playerIndex <= 10)
		{
			_playerCount++;
			if (_playerCount % 7 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
	}
	else if (name == "enemy아머나이트attack")
	{
		if (_playerIndex == 0)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 1 && _playerIndex <= 5)
		{
			_playerCount++;
			if (_playerCount % 7 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 6 && _playerIndex <= 8)
		{
			_playerCount++;
			if (_playerCount % 5 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex == 9)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 10 && _playerIndex <= 12)
		{
			_playerCount++;
			if (_playerCount % 10 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 13 && _playerIndex <= 17)
		{
			_playerCount++;
			if (_playerCount % 10 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex == 18)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				action = false;
				_playerCount = 0;
			}
		}
	}

}
