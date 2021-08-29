#include "stdafx.h"
#include "playerManger.h"
#include "tileSet.h"

HRESULT playerManger::init(TYPE type)
{
	_roy = new Roy;
	_roy->setLinkMap(_map);
	_roy->init(2, 10, type);
	_vplayer.push_back(_roy);
	//_mage =new mage;

	_warrior = new warrior;
	_warrior->setLinkMap(_map);
	_warrior->init(3, 10, type);
	_vplayer.push_back(_warrior);

	_paladin = new paladin;
	_paladin->setLinkMap(_map);
	_paladin->init(1, 10, type);
	_vplayer.push_back(_paladin);
	//_archer = new archer;

	_armor = new ArmorKnight;
	_armor->setLinkMap(_map);
	_armor->init(2, 9, type);
	_vplayer.push_back(_armor);

	//_Pegasus = new Pegasus;
	_social = new socialKnight;
	_social->setLinkMap(_map);
	_social->init(2, 11, type);
	_vplayer.push_back(_social);

	//_transport = new transport;
	//_transport->setLinkMap(_map);
	//_transport->init(2, 10, type);
	//_vplayer.push_back(_transport);
	//_sword = new Swordsman;
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
