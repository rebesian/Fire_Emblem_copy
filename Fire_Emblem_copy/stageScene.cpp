#include "stdafx.h"
#include "stageScene.h"
#include "playerManger.h"
#include "enemyManger.h"
HRESULT stageScene::init()
{

	_tileSet = new tileSet;
	_tileSet->init();
	_tileSet->load();

	mapSizeX = _tileSet->getSizeX();
	mapSizeY = _tileSet->getSizeY();

	_battleScene = new battleScene;
	_battleScene->init();
	_battleScene->setLinkMap(_tileSet);

	_pm = new playerManger;
	_pm->setLinkMap(_tileSet);
	_pm->init();

	_em = new enemyManger;
	_em->setLinkMap(_tileSet);
	_em->init();

	truePlayerFalseEnemy = true;
	_playerPoint = 0;
	_enemyPoint = 0;
	useCount = 0;
	isbattle = isAttackSelect = isMoveSelect = false;
	enemytargetOn = false;

	_pt.indexX = 2;
	_pt.indexY = 10;
	_pt._rc = _tileSet->getRect(_pt.indexX, _pt.indexY);

	return S_OK;
}

void stageScene::update()
{

	if (isbattle)
	{
		if (truePlayerFalseEnemy)
		{
			_battleScene->update(PLAYER);
			if (!_battleScene->getAction())
			{
				isbattle = false;
				_pm->setPlayerSelect(_playerPoint, false);
				_pm->setMoveSelect(_playerPoint, false);
				_pm->setAttackSelect(_playerPoint, false);
				_pm->setUse(_playerPoint, true);

				if (_battleScene->getPlayerCurrentHp() > 0)
				{
					_pm->sethp(_playerPoint, _battleScene->getPlayerCurrentHp());
				}
				else
				{
					_tileSet->setIsPlayer(_pm->getIndexX(_playerPoint), _pm->getIndexY(_playerPoint), false);
					_pm->dead(_playerPoint);
				}
				if (_battleScene->getEnemyCurrentHp()>0)
				{
					_em->sethp(_enemyPoint, _battleScene->getEnemyCurrentHp());
				}
				else
				{
					_tileSet->setIsEnemy(_em->getIndexX(_enemyPoint), _em->getIndexY(_enemyPoint), false);
					_em->dead(_enemyPoint);
				}

				isMoveSelect = false;
			}
		}
		else
		{
			_battleScene->update(ENEMY);
			if (!_battleScene->getAction())
			{
				isbattle = false;
				_em->setPlayerSelect(_enemyPoint, false);
				_em->setMoveSelect(_enemyPoint, false);
				_em->setAttackSelect(_enemyPoint, false);
				_em->setUse(_enemyPoint, true);

				if (_battleScene->getPlayerCurrentHp() > 0)
				{
					_pm->sethp(_playerPoint, _battleScene->getPlayerCurrentHp());
				}
				else
				{
					_tileSet->setIsPlayer(_pm->getIndexX(_playerPoint), _pm->getIndexY(_playerPoint), false);
					_pm->dead(_playerPoint);
				}
				if (_battleScene->getEnemyCurrentHp() > 0)
				{
					_em->sethp(_enemyPoint, _battleScene->getEnemyCurrentHp());
				}
				else
				{
					_tileSet->setIsEnemy(_em->getIndexX(_enemyPoint), _em->getIndexY(_enemyPoint), false);
					_em->dead(_enemyPoint);
				}

				isMoveSelect = false;
			}
		}
	}
	
	if (truePlayerFalseEnemy && !isbattle)
	{
		
		if (useCount >= _pm->getMaxPlayer())
		{
			truePlayerFalseEnemy = false;
			for (int i = 0; i < _pm->getMaxPlayer(); ++i)
			{
				_pm->setUse(i, false);
	
			}
			_enemyPoint = 0;
		}
		else
		{
			useCount = 0;
		}
	
		if (_playerPoint != 255 && _pm->getAttackSelect(_playerPoint))
		{
			isAttackSelect= true;
		}
	
		if (!isMoveSelect && !isAttackSelect)
		{
			_playerPoint = _pm->isPoint(_pt.indexX, _pt.indexY);
			//_enemyPoint = _em->isPoint(_pt.indexX, _pt.indexY);
		}
		else
		{
			if (_pm->getUse(_playerPoint))
			{
				isMoveSelect = false;
				isAttackSelect = false;
			}
		}
	
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
	
			if (_pt.indexX > 0) _pt.indexX -= 1;
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
	
			if (_playerPoint!= 255 && _pm->getAttackSelect(_playerPoint))
			{
				selectEnemy++;
				if (selectEnemy >= _pm->getEnemySize(_playerPoint) || _pm->getEnemySize(_playerPoint) == 1)
				{
					selectEnemy = 0;
				}
				_pt.indexX = _pm->getEnemyX(_playerPoint, selectEnemy);
				_pt.indexY = _pm->getEnemyY(_playerPoint, selectEnemy);
				_pt._rc = _tileSet->getRect(_pt.indexX, _pt.indexY);
			}
			else
			{
				if (_pt.indexY > 0)_pt.indexY -= 1;
				_pt._rc = _tileSet->getRect(_pt.indexX, _pt.indexY);
			}
			if (CAMERAMANAGER->getCameraTOP() <= 0)
			{
				CAMERAMANAGER->setCameraY(0);
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (_playerPoint != 255 && _pm->getAttackSelect(_playerPoint))
			{
				selectEnemy++;
				if (selectEnemy >= _pm->getEnemySize(_playerPoint) || _pm->getEnemySize(_playerPoint) == 1)
				{
					selectEnemy = 0;
				}
				_pt.indexX = _pm->getEnemyX(_playerPoint,selectEnemy);
				_pt.indexY = _pm->getEnemyY(_playerPoint,selectEnemy);
				_pt._rc = _tileSet->getRect(_pt.indexX, _pt.indexY);
			}
			else
			{
				if (_pt.indexY < _tileSet->getSizeY()) _pt.indexY += 1;
				_pt._rc = _tileSet->getRect(_pt.indexX, _pt.indexY);
			}
			//CAMERAMANAGER->setCameraCenterY(CAMERAMANAGER->getCameraCenterY() + 5);
			if (CAMERAMANAGER->getCameraBOTTOM() >= mapSizeY * TILESIZE && mapSizeY*TILESIZE >= CAMERAY)
			{
				CAMERAMANAGER->setCameraY(mapSizeY*TILESIZE - CAMERAY);
			}
		}
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			if (isMoveSelect)
			{
				if (_playerPoint != 255 && _pm->getPlayerSelect(_playerPoint))
				{
					_pm->setMoveSelect(_playerPoint, true);
					
					isMoveSelect = false;
					
				}
			}
			if (_playerPoint != 255 && _pm->getAttackSelect(_playerPoint))
			{
	
				if(_tileSet->getIsEnemy(_pt.indexX, _pt.indexY))
				{
					for (int i = 0; i < _em->getMaxEnemy(); ++i)
					{
						if (_em->getIndexX(i) == _pt.indexX && _em->getIndexY(i) == _pt.indexY)
						{
							_enemyPoint = i;
							break;
						}
					}
					isbattle = true;
					_pm->setAttackSelect(_playerPoint, false);
					_battleScene->setAction(true);
					_battleScene->getEnemy(_em->getName(_enemyPoint), _em->gethp(_enemyPoint), _em->getAttack(_enemyPoint), _em->getAvoid(_enemyPoint), _em->getCritcal(_enemyPoint));
					_battleScene->getPlayer(_pm->getName(_playerPoint), _pm->gethp(_playerPoint), _pm->getAttack(_playerPoint), _pm->getAvoid(_enemyPoint), _pm->getCritcal(_playerPoint));
				}
	
	
			}
			if (_playerPoint != 255)
			{
				if (!_pm->getPlayerSelect(_playerPoint)&& !_pm->getUse(_playerPoint))
				{
					_pm->setPlayerSelect(_playerPoint, true);
					_pm->setMoveTile(_playerPoint, _pm->getIndexX(_playerPoint), _pm->getIndexY(_playerPoint), PLAYER);
					isMoveSelect = true;
				}
			}
		}
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			if (_pm->getPlayerSelect(_playerPoint))
				_pm->setPlayerSelect(_playerPoint, false);
			
		}
	
		for (int i = 0; i < _pm->getMaxPlayer(); ++i)
		{
			if (_pm->getUse(i))
				useCount++;
		}
	
		_pm->update(_pt.indexX, _pt.indexY);
		_em->update(_pt.indexX, _pt.indexY);
	}
	else if(!truePlayerFalseEnemy && !isbattle)
	{
		if (!_em->getUse(_enemyPoint))
		{
			if (!enemytargetOn) {
				int random = RND->getInt(_pm->getMaxPlayer());
				_em->targetOn(_enemyPoint, _pm->getIndexX(random), _pm->getIndexY(random));
				_em->setRender(_enemyPoint, true);
				enemytargetOn = true;
			}
			if (_em->getBattle(_enemyPoint))
			{
				isbattle = true;
				for (int i = 0; i < _pm->getMaxPlayer(); i++)
				{
					if (_pm->getIndexX(i) == _em->getBattleX(_enemyPoint) && _pm->getIndexY(i) == _em->getBattleY(_enemyPoint))
					{
						_playerPoint = i;
						break;
					}
				}
				_battleScene->setAction(true);
				_battleScene->getPlayer(_pm->getName(_playerPoint), _pm->gethp(_playerPoint), _pm->getAttack(_playerPoint), _pm->getAvoid(_playerPoint), _pm->getCritcal(_playerPoint));
				_battleScene->getEnemy(_em->getName(_enemyPoint), _em->gethp(_enemyPoint), _em->getAttack(_enemyPoint), _em->getAvoid(_enemyPoint), _em->getCritcal(_enemyPoint));
				_em->setBattle(_enemyPoint, false);
			}
		}
		else
		{
			enemytargetOn = false;
			_em->setRender(_enemyPoint, false);
			_enemyPoint++;
			enemyCount++;
		}
	
		if (enemyCount >= _em->getMaxEnemy())
		{
			for (int i = 0; i < _em->getMaxEnemy(); ++i)
			{
				_em->setUse(i, false);
			}
			truePlayerFalseEnemy = true;
			useCount = 0;
			enemyCount = 0;
			_playerPoint = 255;
			_enemyPoint = 0;
		}
	
		_pm->update(_pt.indexX, _pt.indexY);
		_em->update(_pt.indexX, _pt.indexY);
		
	}
}

void stageScene::release()
{

}

void stageScene::render()
{
	
	_tileSet->render();
	
	if (isbattle)
	{
		_battleScene->render(CAMERAMANAGER->getCameraLEFT(), CAMERAMANAGER->getCameraTOP() , true);
	}
	else
	{
		_em->render();
		_pm->render();
		_pt._img->render(_tileSet->getMapDC(), _pt._rc.left, _pt._rc.top);
	}


	CAMERAMANAGER->render(_tileSet->getTileBuffer(), getMemDC());

}
