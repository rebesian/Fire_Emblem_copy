#include "stdafx.h"
#include "enemyManger.h"
#include "tileSet.h"
HRESULT enemyManger::init(TYPE type)
{
	_warrior  = new warrior;
	_warrior->setLinkMap(_map);
	_warrior->init(10, 3, type);
	_vEnemy.push_back(_warrior);

	_social = new socialKnight;
	_social->setLinkMap(_map);
	_social->init(11, 3, type);
	_vEnemy.push_back(_social);

	_soider = new soider;
	_soider->setLinkMap(_map);
	_soider->init(11, 4, type);
	_vEnemy.push_back(_soider);

	_armor = new ArmorKnight;
	_armor->setLinkMap(_map);
	_armor->init(10, 4, type);
	_vEnemy.push_back(_armor);



	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		_vEnemy[i]->setMoveTile(_vEnemy[i]->getIndexX(), _vEnemy[i]->getIndexY());
	}

	return S_OK;
}

void enemyManger::update(int idx, int idy)
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->update(idx, idy);
	}
}

void enemyManger::release()
{
}

void enemyManger::render()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->render();
	}
}

int enemyManger::isPoint(int _ptx, int _pty)
{
	int pointing = 255;
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		if (_vEnemy[i]->getIndexX() == _ptx && _vEnemy[i]->getIndexY() == _pty)
		{
			_vEnemy[i]->setpointing(true);
			pointing = i;
		}
		else
		{
			_vEnemy[i]->setpointing(false);
		}
	}
	return pointing;
}
