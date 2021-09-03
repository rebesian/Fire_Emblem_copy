#include "stdafx.h"
#include "playerManger.h"
#include "tileSet.h"

HRESULT playerManger::init(TYPE type)
{
	_roy = new Roy;
	_roy->setLinkMap(_map);
	_roy->init(2, 10, type);
	_vplayer.push_back(_roy);

	_warrior = new warrior;
	_warrior->setLinkMap(_map);
	_warrior->init(3, 10, type);
	_vplayer.push_back(_warrior);

	_paladin = new paladin;
	_paladin->setLinkMap(_map);
	_paladin->init(1, 10, type);
	_vplayer.push_back(_paladin);
	
	_armor = new ArmorKnight;
	_armor->setLinkMap(_map);
	_armor->init(2, 9, type);
	_vplayer.push_back(_armor);

	
	_social = new socialKnight;
	_social->setLinkMap(_map);
	_social->init(2, 11, type);
	_vplayer.push_back(_social);

	for (int i = 0; i < _vplayer.size(); ++i)
	{
		_vplayer[i]->setMoveTile(_vplayer[i]->getIndexX(), _vplayer[i]->getIndexY() , type);
	}

	return S_OK;
}

void playerManger::update(int idx, int idy)
{
	for (_viplayer = _vplayer.begin(); _viplayer != _vplayer.end(); ++_viplayer)
	{
		(*_viplayer)->update(idx, idy);
	}
}

void playerManger::release()
{

}

void playerManger::render()
{
	for (_viplayer = _vplayer.begin(); _viplayer != _vplayer.end(); ++_viplayer)
	{
		(*_viplayer)->render();
	}
}

void playerManger::dead(int pointed)
{
	_vplayer.erase(_vplayer.begin() + pointed);
}

int playerManger::isPoint(int _ptx, int _pty )
{
	int pointing = 255;
	for (int i = 0;  i < _vplayer.size(); ++i)
	{
		if (_vplayer[i]->getIndexX() == _ptx && _vplayer[i]->getIndexY() == _pty)
		{
			_vplayer[i]->setpointing(true);
			pointing = i;
		}
		else
		{
			_vplayer[i]->setpointing(false);
		}
	}
	
	return pointing;

}
