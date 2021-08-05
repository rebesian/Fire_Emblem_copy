#include "stdafx.h"
#include "tank.h"


tank::tank()
{
}


tank::~tank()
{
}

HRESULT tank::init()
{
	_direction = TANKDIRECTION_RIGHT;

	_image = IMAGEMANAGER->addFrameImage("tank", "tank.bmp", 256, 128, 8, 4, true, RGB(255, 0, 255));

	_speed = 100.0f;

	return S_OK;
}

void tank::release()
{
}

void tank::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_direction = TANKDIRECTION_LEFT;
		//tankMove();
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_direction = TANKDIRECTION_RIGHT;
		//tankMove();
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_direction = TANKDIRECTION_UP;
		//tankMove();
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_direction = TANKDIRECTION_DOWN;
		//tankMove();
	}
	tankMove();
}

void tank::render()
{
	Rectangle(getMemDC(), _rc);
	_image->frameRender(getMemDC(), _rc.left, _rc.top);
}

void tank::tankMove()
{
	//여기가 제일 중요한 부분이 아닌가 싶습니다
	RECT rcCollision;	//가상의 충돌판정 렉트를 하나 생성해주자

	
	int tileIndex[2];	//타일 검출에 필요한 인덱스
	int tileX, tileY;	//플레이어가 밟고 있는 타일의 인덱스

	//가상의 판정렉트에 현재 렉트를 대입해주자
	rcCollision = _rc;

	//STEP 3
	//판정렉트를 사알짝 깍아주자


	float elapsedTime = TIMEMANAGER->getElapsedTime();
	float moveSpeed = elapsedTime * _speed;

	switch (_direction)
	{
		case TANKDIRECTION_LEFT:
			_image->setFrameX(0);
			_image->setFrameY(3);

			_x -= moveSpeed;

			rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth()-2, _image->getFrameHeight()-2);
		break;
		case TANKDIRECTION_UP:
			_image->setFrameX(0);
			_image->setFrameY(0);
			_y -= moveSpeed;

			rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth()-2, _image->getFrameHeight()-2);
		break;

		case TANKDIRECTION_RIGHT:
			_image->setFrameX(0);
			_image->setFrameY(2);
			_x += moveSpeed;

			rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth() - 2, _image->getFrameHeight()-2);
		break;

		case TANKDIRECTION_DOWN:
			_image->setFrameX(0);
			_image->setFrameY(1);

			_y += moveSpeed;

			rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth() - 2, _image->getFrameHeight() - 2);
		break;
	
	}

	tileX = rcCollision.left / TILESIZE;
	tileY = rcCollision.top / TILESIZE;

	//STEP 04
	//가장 메인이지 싶으요
	switch (_direction)
	{
		case TANKDIRECTION_LEFT:
			tileIndex[0] = tileX + tileY*TILEX;
			tileIndex[1] = tileX + ((tileY + 1) *TILEX);
		break;
		case TANKDIRECTION_UP:
			tileIndex[0] = tileX + tileY * TILEX;
			tileIndex[1] = (tileX + 1) + tileY * TILEX;
		break;
		case TANKDIRECTION_RIGHT:
			tileIndex[0] = (tileX + tileY * TILEX)+1;
			tileIndex[1] = ((tileX + (tileY+1) * TILEX))+1;
		break;
		case TANKDIRECTION_DOWN:
			tileIndex[0] = (tileX + tileY * TILEX)+TILEX;
			tileIndex[1] = ((tileX + 1) + tileY * TILEX)+TILEX;
		break;
	
	}

	for (int i = 0; i < 2; i++)
	{
		RECT rc;

		if (((_tankMap->getAttribute()[tileIndex[i]] & ATTR_UNMOVE) == ATTR_UNMOVE) &&
			IntersectRect(&rc, &_tankMap->getTile()[tileIndex[i]].rc, &rcCollision))
		{
			switch (_direction)
			{
				case TANKDIRECTION_LEFT:
					_rc.left = _tankMap->getTile()[tileIndex[i]].rc.right;
					_rc.right = _rc.left + 30;

					_x = (_rc.left + _rc.right) / 2;
					break;
				case TANKDIRECTION_UP:
					_rc.top = _tankMap->getTile()[tileIndex[i]].rc.bottom;
					_rc.bottom = _rc.top + 30;
					_y = (_rc.top + _rc.bottom) / 2;
					break;
				case TANKDIRECTION_RIGHT:
					_rc.right = _tankMap->getTile()[tileIndex[i]].rc.left;
					_rc.left = _rc.right - 30;

					_x = (_rc.left + _rc.right) / 2;
					break;
				case TANKDIRECTION_DOWN:
					_rc.bottom = _tankMap->getTile()[tileIndex[i]].rc.top;
					_rc.top = _rc.bottom - 30;
					_y = (_rc.top + _rc.bottom) / 2;
					break;
			}

			return;
		}
	}


	_rc = rcCollision;
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

}

void tank::setTankPosition()
{
	_rc = _tankMap->getTile()[_tankMap->getPosFirst()].rc;

	_x = (_rc.left + _rc.right) / 2;
	_y = (_rc.top + _rc.bottom) / 2;
}
