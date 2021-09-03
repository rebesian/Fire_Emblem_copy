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
	
	action = false;
	return S_OK;
}

void battleScene::release()
{
}

void battleScene::update(TYPE _type)
{
	type = _type;
	if (action)
	{
		if(_truePlayerFalseEnemy)
			playerAction(_playerimageName);
		else
			enemyAction(_enemyimageName);
	}
}

void battleScene::render(int x , int y , bool truePlayerFalseEnemy)
{
	battleStage->render(_map->getMapDC() , x ,y);
	_enemy.hit->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 125, CAMERAMANAGER->getCameraTOP() + 433);
	_enemy.damage->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 125, CAMERAMANAGER->getCameraTOP() + 461);
	_enemy.crit->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 125, CAMERAMANAGER->getCameraTOP() + 488);
	_enemy.hp2->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 195, CAMERAMANAGER->getCameraTOP() + 547);
	_enemy.hp1->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 195, CAMERAMANAGER->getCameraTOP() + 547 , 0, 0, (_enemyCurrentHp / 20.0) * 256, 26);
	_player.hit->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 799, CAMERAMANAGER->getCameraTOP() + 433);
	_player.damage->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 796, CAMERAMANAGER->getCameraTOP() + 461);
	_player.crit->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 799, CAMERAMANAGER->getCameraTOP() + 488);
	_player.hp2->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 505, CAMERAMANAGER->getCameraTOP() + 547);
	_player.hp1->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 505, CAMERAMANAGER->getCameraTOP() + 547,  0 , 0,  (_playerCurrentHp / 20.0)*256 , 26);

	HFONT font, oldFont;
	font = CreateFont(50, 0, 0, 0, 100, false, false, false, HANGUL_CHARSET,
		0, 0, 0, 0, TEXT("HY얕은샘물M"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);
	
	//TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() +  890, CAMERAMANAGER->getCameraTOP(), (char)_playerName, strlen(_playerName));
	
	DeleteObject(font);


	if (_enemyHit >= 10)
	{
		char str[12];
		sprintf_s(str, "%d", _enemyHit / 10);
		IMAGEMANAGER->findImage(str)->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 186, CAMERAMANAGER->getCameraTOP() + 433);
		sprintf_s(str, "%d", _enemyHit % 10);
		IMAGEMANAGER->findImage(str)->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT()  + 210, CAMERAMANAGER->getCameraTOP() + 433);
	}
	else
	{
		char str[12];
		sprintf_s(str, "%d", _enemyHit);
		IMAGEMANAGER->findImage(str)->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 210, CAMERAMANAGER->getCameraTOP() + 433);
	}

	if (_enemyAttack >= 10)
	{
		char str[12];
		sprintf_s(str, "%d", _enemyAttack / 10);
		IMAGEMANAGER->findImage(str)->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 186, CAMERAMANAGER->getCameraTOP() + 461);
		sprintf_s(str, "%d", _enemyAttack % 10);
		IMAGEMANAGER->findImage(str)->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 210, CAMERAMANAGER->getCameraTOP() + 461);
	}
	else
	{
		char str[12];
		sprintf_s(str, "%d", _enemyAttack);
		IMAGEMANAGER->findImage(str)->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 210, CAMERAMANAGER->getCameraTOP() + 461);
	}

	if (_enemyCrit >= 10)
	{
		char str[12];
		sprintf_s(str, "%d", _enemyCrit / 10);
		IMAGEMANAGER->findImage(str)->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 186, CAMERAMANAGER->getCameraTOP() + 488);
		sprintf_s(str, "%d", _enemyCrit % 10);
		IMAGEMANAGER->findImage(str)->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 210, CAMERAMANAGER->getCameraTOP() + 488);
	}
	else
	{
		char str[12];
		sprintf_s(str, "%d", _playerCrit);
		IMAGEMANAGER->findImage(str)->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 210, CAMERAMANAGER->getCameraTOP() + 488);
	}


	if (_playerHit >= 10)
	{
		char str[12];
		sprintf_s(str, "%d", _playerHit / 10);
		IMAGEMANAGER->findImage(str)->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 729, CAMERAMANAGER->getCameraTOP() + 433);
		sprintf_s(str, "%d", _playerHit % 10);
		IMAGEMANAGER->findImage(str)->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 753, CAMERAMANAGER->getCameraTOP() + 433);
	}
	else
	{
		char str[12];
		sprintf_s(str, "%d", _playerHit);
		IMAGEMANAGER->findImage(str)->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 753, CAMERAMANAGER->getCameraTOP() + 433);
	}

	if (_playerAttack >= 10)
	{
		char str[12];
		sprintf_s(str, "%d", _playerAttack / 10);
		IMAGEMANAGER->findImage(str)->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 729, CAMERAMANAGER->getCameraTOP() + 461);
		sprintf_s(str, "%d", _playerAttack % 10);
		IMAGEMANAGER->findImage(str)->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 753, CAMERAMANAGER->getCameraTOP() + 461);
	}
	else
	{
		char str[12];
		sprintf_s(str, "%d", _playerAttack);
		IMAGEMANAGER->findImage(str)->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 753, CAMERAMANAGER->getCameraTOP() + 461);
	}

	if (_playerCrit >= 10)
	{
		char str[12];
		sprintf_s(str, "%d", _playerCrit / 10);
		IMAGEMANAGER->findImage(str)->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 729, CAMERAMANAGER->getCameraTOP() + 488);
		sprintf_s(str, "%d", _playerCrit % 10);
		IMAGEMANAGER->findImage(str)->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 753, CAMERAMANAGER->getCameraTOP() + 488);
	}
	else
	{
		char str[12];
		sprintf_s(str, "%d", _playerCrit);
		IMAGEMANAGER->findImage(str)->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 753, CAMERAMANAGER->getCameraTOP() + 488);
	}

	if (_enemyCurrentHp >= 10)
	{
		char str[12];
		sprintf_s(str, "%d", (int)(_enemyCurrentHp / 10));
		IMAGEMANAGER->findImage(str)->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 141, CAMERAMANAGER->getCameraTOP() + 547);
		sprintf_s(str, "%d", (int)((int)_enemyCurrentHp % 10));
		IMAGEMANAGER->findImage(str)->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 165, CAMERAMANAGER->getCameraTOP() + 547);
	}
	else
	{
		char str[12];
		sprintf_s(str, "%d", (int)_enemyCurrentHp);
		IMAGEMANAGER->findImage(str)->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 165, CAMERAMANAGER->getCameraTOP() + 547);
	}

	if (_playerCurrentHp >= 10)
	{
		char str[12];
		sprintf_s(str, "%d", (int)(_playerCurrentHp / 10));
		IMAGEMANAGER->findImage(str)->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 774, CAMERAMANAGER->getCameraTOP() + 547);
		sprintf_s(str, "%d", (int)((int)_playerCurrentHp % 10));
		IMAGEMANAGER->findImage(str)->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 798, CAMERAMANAGER->getCameraTOP() + 547);
	}
	else
	{
		char str[12];
		sprintf_s(str, "%d", (int)_playerCurrentHp);
		IMAGEMANAGER->findImage(str)->render(_map->getMapDC(), CAMERAMANAGER->getCameraLEFT() + 798, CAMERAMANAGER->getCameraTOP() + 547);
	}





	if (truePlayerFalseEnemy)
	{
		enemyimage->frameRender(_map->getMapDC(), _enemyActionX, _enemyActionY, _enemyIndex, 0);
		playerimage->frameRender(_map->getMapDC(), _playerActionX, _playerActionY, _playerIndex, 0);
	}
	else
	{
		playerimage->frameRender(_map->getMapDC(), _playerActionX, _playerActionY, _playerIndex, 0);
		enemyimage->frameRender(_map->getMapDC(), _enemyActionX, _enemyActionY, _enemyIndex, 0);
	}

}

void battleScene::playerStart(string name)
{
	if (name == "로이attack")
	{
		_playerActionX = CAMERAMANAGER->getCameraCenterX();
		_playerActionY = CAMERAMANAGER->getCameraTOP() + 524 - playerimage->getFrameWidth();
	}
	else if (name == "소셜나이트attack")
	{
		_playerActionX = CAMERAMANAGER->getCameraCenterX() - 80;
		_playerActionY = CAMERAMANAGER->getCameraTOP() + 524 - playerimage->getFrameWidth();
	}
	else if (name == "전사attack")
	{
		_playerActionX = CAMERAMANAGER->getCameraCenterX() - 48;
		_playerActionY = CAMERAMANAGER->getCameraTOP() + 524 - playerimage->getFrameWidth() + 48;
	}
	else if (name == "팔라딘attack")
	{
		_playerActionX = CAMERAMANAGER->getCameraCenterX() - 90;
		_playerActionY = CAMERAMANAGER->getCameraTOP() + 524 - playerimage->getFrameWidth() - 15;
	}
	else if (name == "아머나이트attack")
	{
		_playerActionX = CAMERAMANAGER->getCameraCenterX() - 80;
		_playerActionY = CAMERAMANAGER->getCameraTOP() + 524 - playerimage->getFrameWidth() - 20;
	}

}

void battleScene::enemyStart(string name)
{
	if (name == "enemy소셜나이트attack")
	{
		_enemyActionX = CAMERAMANAGER->getCameraCenterX() - enemyimage->getFrameWidth() + 80;
		_enemyActionY = CAMERAMANAGER->getCameraTOP() + 524 - enemyimage->getFrameWidth();
	}
	else if (name == "enemy전사attack")
	{
		_enemyActionX = CAMERAMANAGER->getCameraCenterX() - enemyimage->getFrameWidth() + 50;
		_enemyActionY = CAMERAMANAGER->getCameraTOP() + 524 - enemyimage->getFrameWidth() + 48;
	}
	else if (name == "enemy군인attack")
	{
		_enemyActionX = CAMERAMANAGER->getCameraCenterX() - enemyimage->getFrameWidth() + 20;
		_enemyActionY = CAMERAMANAGER->getCameraTOP() + 524 - enemyimage->getFrameWidth();
	}
	else if (name == "enemy아머나이트attack")
	{
		_enemyActionX = CAMERAMANAGER->getCameraCenterX() - enemyimage->getFrameWidth() + 80;
		_enemyActionY = CAMERAMANAGER->getCameraTOP() + 524 - enemyimage->getFrameWidth() - 20;
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
		else if (_playerIndex >= 1 && _playerIndex <=3)
		{
			_playerCount++;
		
			if (_playerIndex == 3)
			{
				if (_playerCount > 30)
				{
					_playerIndex++;
					_playerActionX -= 150;
					_playerCount = 0;
				}
			}
			else if (_playerCount % 5 == 0)
			{
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 4 && _playerIndex <= 5)
		{

			_playerCount++;
			//공격
			if (_playerIndex == 5)
			{
				_enemyCurrentHp -= 0.3;
				if (_enemyCurrentHp <= _enemyHp -_playerAttack)
				{
					_enemyCurrentHp = _enemyHp - _playerAttack;
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
		else if (_playerIndex >= 13 && _playerIndex<=18)
		{

			_playerCount++;
			if (_playerCount % 5 == 0)
			{
				_playerIndex++;
				_playerActionX += 25;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 19 && _playerIndex <= 23)
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
				if (_enemyCurrentHp <= 0)
				{
					action = false;
				}
				else
				{
					_truePlayerFalseEnemy = false;
				}
				if (type == ENEMY)
				{
					action = false;
				}
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
				_playerActionX -= 50;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 1 && _playerIndex <= 2)
		{
			_playerCount++;
			if (_playerIndex == 1)
			{
				if (_playerCount > 30)
				{
					_playerIndex++;
					_playerActionX -= 50;
					_playerCount = 0;
				}
			}
			else
			{
				if (_playerCount % 10 == 0)
				{
					_playerIndex++;
					_playerActionX -= 50;
					_playerCount = 0;
				}
			}
		}
		//공격
		else if (_playerIndex == 3)
		{
			_playerCount++;
			_enemyCurrentHp -= 0.3;
			if (_enemyCurrentHp <= _enemyHp - _playerAttack)
			{
				_enemyCurrentHp = _enemyHp - _playerAttack;
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
				_playerActionX += 20;
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
				_playerActionX += 5;
				_playerCount = 0;
			}
		}
		else if (_playerIndex == 14)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				if (_enemyCurrentHp <= 0)
				{
					action = false;
				}
				else
				{
					_truePlayerFalseEnemy = false;
				}
				if (type == ENEMY)
				{
					action = false;
				}
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
			if (_playerIndex == 4)
			{
				if (_playerCount > 30)
				{
					_playerIndex++;
					_playerActionX -= 75;
					_playerCount = 0;
				}
			}
			else
			{
				if (_playerCount % 5 == 0)
				{
					if (_playerIndex == 3)
					{
						_playerActionX -= 75;
					}
					_playerIndex++;
					_playerCount = 0;
				}
			}
		}
		//공격
		else if (_playerIndex == 5)
		{
			_playerCount++;
			_enemyCurrentHp -= 0.3;
			if (_enemyCurrentHp <= _enemyHp - _playerAttack)
			{
				_enemyCurrentHp = _enemyHp - _playerAttack;
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 6 && _playerIndex <= 7)
		{
			_playerCount++;
			if (_playerCount % 15 == 0)
			{
				if (_playerIndex == 6)
				{
					_playerActionX += 75;
				}
				_playerIndex++;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 8 && _playerIndex <= 10)
		{
			_playerCount++;
			if (_playerCount % 20 == 0)
			{
				_playerIndex++; 
				_playerActionX += 25;
				_playerCount = 0;
			}
		}
		else if (_playerIndex == 11)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				if (_enemyCurrentHp <= 0)
				{
					action = false;
				}
				else
				{
					_truePlayerFalseEnemy = false;
				}
				if (type == ENEMY)
				{
					action = false;
				}
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
				_playerActionX += 15;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 1 && _playerIndex <= 3)
		{
			_playerCount++;
			if (_playerCount % 10 == 0)
			{
				_playerIndex++;
				_playerActionX += 15;
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
				_playerActionX -= 90;
				_playerCount = 0;
			}
		}
		//공격
		else if (_playerIndex == 7)
		{
			_playerCount++;
			_enemyCurrentHp -= 0.3;
			if (_enemyCurrentHp <= _enemyHp - _playerAttack)
			{
				_enemyCurrentHp = _enemyHp - _playerAttack;
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
				_playerActionX += 20;
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
				_playerActionX -= 10;
				_playerCount = 0;
			}
		}
		else if (_playerIndex == 30)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				if (_enemyCurrentHp <= 0)
				{
					action = false;
				}
				else
				{
					_truePlayerFalseEnemy = false;
				}
				if (type == ENEMY)
				{
					action = false;
				}
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
				_playerActionX -= 30;
				_playerCount = 0;
			}
		}
		else if (_playerIndex >= 1 && _playerIndex <= 5)
		{
			_playerCount++;
			if (_playerCount % 7 == 0)
			{
				_playerIndex++;
				if (_playerIndex == 5)
				{
					_playerActionX -= 120;
				}
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
		//공격
		else if (_playerIndex == 9)
		{
			_playerCount++;
			_enemyCurrentHp -= 0.3;
			if (_enemyCurrentHp <= _enemyHp - _playerAttack)
			{
				_enemyCurrentHp = _enemyHp - _playerAttack;
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
				if (_playerIndex == 13)
				{
					_playerActionX += 120;
				}
				else
					_playerActionX += 30;
				_playerCount = 0;
			}
		}
		else if (_playerIndex == 18)
		{
			_playerCount++;
			if (_playerCount > 30)
			{
				if (_enemyCurrentHp <= 0)
				{
					action = false;
				}
				else
				{
					_truePlayerFalseEnemy = false;
				}
				if (type == ENEMY)
				{
					action = false;
				}
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
			_enemyCount++;
			if (_enemyCount > 30)
			{
				_enemyIndex++;
				_enemyActionX += 50;
				_enemyCount = 0;
			}
		}
		else if (_enemyIndex >= 1 && _enemyIndex <= 2)
		{
			_enemyCount++;
			if (_enemyIndex == 1)
			{
				if (_enemyCount > 30)
				{
					_enemyIndex++;
					_enemyActionX += 50;
					_enemyCount = 0;
				}
			}
			else
			{
				if (_enemyCount % 10 == 0)
				{
					_enemyIndex++;
					_enemyActionX += 50;
					_enemyCount = 0;
				}
			}
		}
		//공격
		else if (_enemyIndex == 3)
		{
			_enemyCount++;
			_playerCurrentHp -= 0.3;
			if (_playerCurrentHp <= _playerHp - _enemyAttack)
			{
				_playerCurrentHp = _playerHp - _enemyAttack;
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
				_enemyActionX -= 20;
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
				_enemyActionX -= 5;
				_enemyCount = 0;
			}
		}
		else if (_enemyIndex == 14)
		{
			_enemyCount++;
			if (_enemyCount > 30)
			{
				if (_playerCurrentHp <= 0)
				{
					action = false;
				}
				else
				{
					_truePlayerFalseEnemy = true;
				}
				if (type == PLAYER)
				{
					action = false;
				}
				_enemyCount = 0;
			}
		}
	}
	else if (name == "enemy전사attack")
	{
		if (_enemyIndex == 0)
		{
			_enemyCount++;
			if (_enemyCount > 30)
			{
				_enemyIndex++;
				_enemyCount = 0;
			}
		}
		else if (_enemyIndex >= 1 && _enemyIndex <= 4)
		{
			_enemyCount++;
			if (_enemyIndex == 4)
			{
				if (_enemyCount > 30 )
				{
					_enemyIndex++;
					_enemyActionX += 75;
					_enemyCount = 0;
				}
			}
			else
			{
				if (_enemyCount % 3 == 0)
				{
					_enemyIndex++;
					if (_enemyIndex == 3)
					{
						_enemyActionX += 75;
					}
					_enemyCount = 0;
				}
			}
		}
		//공격
		else if (_enemyIndex == 5)
		{
			_enemyCount++;
			_playerCurrentHp -= 0.3;
			if (_playerCurrentHp <= _playerHp - _enemyAttack)
			{
				_playerCurrentHp = _playerHp - _enemyAttack;
				_enemyIndex++;
				_enemyCount = 0;
			}
		}
		else if (_enemyIndex >= 6 && _enemyIndex <= 7)
		{
			_enemyCount++;
			if (_enemyCount % 15 == 0)
			{
				if (_enemyIndex == 6)
				{
					_enemyActionX -= 75;
				}
				_enemyIndex++;
				_enemyCount = 0;
			}
		}
		else if (_enemyIndex >= 8 && _enemyIndex <= 10)
		{
			_enemyCount++;
			if (_enemyCount % 20 == 0)
			{
				_enemyIndex++;
				_enemyActionX -= 25;
				_enemyCount = 0;
			}
		}
		else if (_enemyIndex == 11)
		{
			_enemyCount++;
			if (_enemyCount > 30)
			{
				if (_playerCurrentHp <= 0)
				{
					action = false;
				}
				else
				{
					_truePlayerFalseEnemy = true;
				}
				if (type == PLAYER)
				{
					action = false;
				}
				_enemyCount = 0;
			}
		}
	}
	else if (name == "enemy군인attack")
	{
		if (_enemyIndex == 0)
		{
			_enemyCount++;
			if (_enemyCount > 30)
			{
				_enemyIndex++;
				_enemyCount = 0;
			}
		}
		else if (_enemyIndex >= 1 && _enemyIndex <=2)
		{
			_enemyCount++;
			if (_enemyCount % 7 == 0)
			{
				_enemyIndex++;
				_enemyActionX += 45;
				_enemyCount = 0;
			}
		}
		else if (_enemyIndex >= 3 && _enemyIndex <= 4)
		{
			_enemyCount++;
			if (_enemyIndex == 3)
			{
				if (_enemyCount > 30)
				{
					_enemyIndex++;
					_enemyActionX += 55;
					_enemyCount = 0;
				}
			}
			else
			{
				if (_enemyCount % 7 == 0)
				{
					_enemyIndex++;
					_enemyCount = 0;
				}
			}
		}
		//공격
		else if (_enemyIndex == 5)
		{
			_enemyCount++;
			_playerCurrentHp -= 0.3;
			if (_playerCurrentHp <= _playerHp - _enemyAttack)
			{
				_playerCurrentHp = _playerHp - _enemyAttack;
				_enemyIndex++;
				_enemyCount = 0;
			}
		}
		else if (_enemyIndex >= 6 && _enemyIndex <= 7)
		{
			_enemyCount++;	
			if (_enemyCount % 7 == 0)
			{
				_enemyIndex++;
				_enemyActionX -= 45;
				_enemyCount = 0;
			}
			
		}
		else if (_enemyIndex >= 8 && _enemyIndex <= 11)
		{
			_enemyCount++;
			if (_enemyCount % 7 == 0)
			{
				_enemyIndex++;
				_enemyCount = 0;
			}
		}
		else if (_enemyIndex == 12)
		{
			_enemyCount++;
			if (_enemyCount > 30)
			{
				if (_playerCurrentHp <= 0)
				{
					action = false;
				}
				else
				{
					_truePlayerFalseEnemy = true;
				}
				if (type == PLAYER)
				{
					action = false;
				}
				_enemyCount = 0;
			}
		}
	}
	else if (name == "enemy아머나이트attack")
	{
		if (_enemyIndex == 0)
		{
			_enemyCount++;
			if (_enemyCount > 30)
			{
				_enemyIndex++;
				_enemyActionX += 30;
				_enemyCount = 0;
			}
		}
		else if (_enemyIndex >= 1 && _enemyIndex <= 5)
		{
			_enemyCount++;
			if (_enemyCount % 7 == 0)
			{
				_enemyIndex++;
				if (_enemyIndex == 5)
				{
					_enemyActionX += 120;
				}
				_enemyCount = 0;
			}
		}
		else if (_enemyIndex >= 6 && _enemyIndex <= 8)
		{
			_enemyCount++;
			if (_enemyCount % 5 == 0)
			{
				_enemyIndex++;
				_enemyCount = 0;
			}
		}
		//공격
		else if (_enemyIndex == 9)
		{
			_enemyCount++;
			_playerCurrentHp -= 0.3;
			if (_playerCurrentHp <= _playerHp - _enemyAttack)
			{
				_playerCurrentHp = _playerHp - _enemyAttack;
				_enemyIndex++;
				_enemyCount = 0;
			}
		}
		else if (_enemyIndex >= 10 && _enemyIndex <= 12)
		{
			_enemyCount++;
			if (_enemyCount % 10 == 0)
			{
				_enemyIndex++;
				_enemyCount = 0;
			}
		}
		else if (_enemyIndex >= 13 && _enemyIndex <= 17)
		{
			_enemyCount++;
			if (_enemyCount % 10 == 0)
			{
				_enemyIndex++;
				if (_enemyIndex == 13)
				{
					_enemyActionX -= 120;
				}
				else
					_enemyActionX -= 30;
				_enemyCount = 0;
			}
		}
		else if (_enemyIndex == 18)
		{
			_enemyCount++;
			if (_enemyCount > 30)
			{
				if (_playerCurrentHp <= 0)
				{
					action = false;
				}
				else
				{
					_truePlayerFalseEnemy = true;
				}
				if (type == PLAYER)
				{
					action = false;
				}
				_enemyCount = 0;
			}
		}
	}

}
