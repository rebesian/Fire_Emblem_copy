#include "stdafx.h"
#include "tile.h"
#include "aStarTest.h"

//¸â¹ö ÀÌ´Ï¼È¶óÀÌÁî
tile::tile()
	:_totalCost(0), _costFromStart(0),
	_costToGoal(0), _parentNode(NULL),_parentNodenumber(0),
	_idX(0), _idY(0), _isOpen(true) , _attribute("none")
{
}


tile::~tile()
{

}

HRESULT tile::init(int idX, int idY)
{

	_idX = idX;
	_idY = idY;
	_rc = _map->getRect(_idX, _idY);
	_center = PointMake((_rc.right+_rc.left)/2,(_rc.bottom+_rc.top)/2);
	_count = _renderX = 0;
	return S_OK;
}

void tile::release()
{


}

void tile::update()
{
	_count++;
	if (_count % 5 == 0)
	{
		_renderX++;
		if (_renderX > 7)
		{
			_renderX = 0;
		}
	}
}

void tile::render()
{
	_img->frameRender(_map->getMapDC(), _rc.left, _rc.top , _renderX, 1);
}
