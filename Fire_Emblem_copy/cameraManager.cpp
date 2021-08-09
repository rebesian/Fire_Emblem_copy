#include "stdafx.h"
#include "cameraManager.h"

void cameraManager::cameraRange()
{
	if (_cameraBuffer->getX() < 0) _cameraBuffer->setX(0);
	else if (_cameraBuffer->getX() + CAMERAX > BACKGROUNDX)_cameraBuffer->setX(BACKGROUNDX - CAMERAX);
	if (_cameraBuffer->getY() < 0)_cameraBuffer->setY(0);
	else if (_cameraBuffer->getY() + CAMERAY > BACKGROUNDY) _cameraBuffer->setY(BACKGROUNDY - CAMERAY);
}

//����
cameraManager::cameraManager()
{
}

cameraManager::~cameraManager()
{
}

//����
HRESULT cameraManager::init(int width, int height)
{
	//backDC�� frontDCũ�� ����
	_backWidth = width;
	_backHeight = height;
	_frontWidth = WINSIZEX;
	_frontHeight = WINSIZEY;
	//ȭ�� Rect ����
	_screen = RectMake(0, 0, WINSIZEX, WINSIZEY);
	_zoom = RectMake(0, 0, WINSIZEX, WINSIZEY);

	_count = 0;

	return S_OK;
}

HRESULT cameraManager::init()
{
	_cameraBuffer = new image;
	_cameraBuffer->init(CAMERAX, CAMERAY);
	for (int i = 0; i < 2; i++)
	{
		x[i] = 0;
		y[i] = 0;
	}
	return S_OK;
}

void cameraManager::release()
{
	SAFE_DELETE(_cameraBuffer);
}

//����
void cameraManager::updateScreen(float standardX, float standardY,
	float ratioX, float ratioY, float zoom)
{
	//�÷��̾� �������� ȭ��(_screen)����
	//playground.cpp�� update()���� ��� �������ָ� ��
	//�μ��� ������ �Ǵ� ��ü�� x, y��ǥ�� ����(����� player�� x, y)
	float x = standardX;
	float y = standardY;

	//X�� (��, ��)
	if (x - _frontWidth * ratioX < 0)
		x = 0;
	else if (x + _frontWidth * (1 - ratioX) > _backWidth)
		x = _backWidth - _frontWidth;
	else
		x -= _frontWidth * ratioX;
	//Y�� (��, ��)
	if (y - _frontHeight * ratioY < 0)
		y = 0;
	else if (y + _frontHeight * (1 - ratioY) > _backHeight)
		y = _backHeight - _frontHeight;
	else
		y -= _frontHeight * ratioY;

	//����
	_screen = RectMake(x, y, _frontWidth, _frontHeight);

	if (zoom != 1.0) {
		x = standardX;
		y = standardY;
		float width = _frontWidth * zoom;
		float height = _frontHeight * zoom;

		//X�� (��, ��)
		if (x - width * ratioX < 0)
			x = 0;
		else if (x + width * (1 - ratioX) > _backWidth)
			x = _backWidth - width;
		else
			x -= width * ratioX;
		//Y�� (��, ��)
		if (y - height * ratioY < 0)
			y = 0;
		else if (y + height * (1 - ratioY) > _backHeight)
			y = _backHeight - height;
		else
			y -= height * ratioY;

		_zoom = RectMake(x, y, width, height);
	}
}

//����
void cameraManager::vibrateScreen(float standardX, float standardY, float magnitude)
{
	//_count += TIMEMANAGER->getElapsedTime();
	updateCamera(standardX + RND->getFromFloatTo(-magnitude, magnitude),
		standardY + RND->getFromFloatTo(-magnitude, magnitude));
	//_count = 0;

	//ī��Ʈ�� �� �����ϱ�.........
	//interval(���� �ֱ�) ����
	/*if (_count >= interval) {
	}*/
}



void cameraManager::update()
{
	if (_isFixed)
	{
		_isHaveToMove = true;
	}
}


void cameraManager::render(image* backBuffer, HDC frontDC)
{
	HDC cameraDC = _cameraBuffer->getMemDC();
	HDC backDC = backBuffer->getMemDC();

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < 2; i++)
		{
			if (x[i] != 0)
			{
				LineMake(backDC, x[i], _cameraBuffer->getY(), x[i], _cameraBuffer->getY() + CAMERAY);
			}
			if (y[i] != 0)
			{
				LineMake(backDC, _cameraBuffer->getX(), y[i], _cameraBuffer->getX() + CAMERAX, y[i]);
			}
		}
	}

	backBuffer->render(cameraDC, 0, 0, _cameraBuffer->getX(), _cameraBuffer->getY(), CAMERAX, CAMERAY);
	
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		TIMEMANAGER->render(cameraDC);
		char str[128];
		sprintf_s(str, "_isFixed: %d", _isFixed);
		TextOut(cameraDC, 0, 100, str, strlen(str));
		sprintf_s(str, "_isHaveToMove: %d", _isHaveToMove);
		TextOut(cameraDC, 0, 120, str, strlen(str));
	}


	_cameraBuffer->render(frontDC, 0, 0);
}

//����
void cameraManager::render(HDC frontDC, int destX, int destY, HDC backDC, float zoom)
{
	/********* �μ� ���� *********/ /*
	HDC frontDC: ���縦 ���� DC (������ �츮�� ���� ȭ��)
	int destX: �츮�� ���� ȭ�鿡�� ������� x��ǥ
	int destY: �츮�� ���� ȭ�鿡�� ������� y��ǥ
	HDC backDC: ������ �� DC (������ �츮�� �׸��� ȭ��)
	bool map: true�� ��ü�� ���, false�� �� ���
	bool mini: true�� �̴ϸ� ���, false�� �� ���
	*/

	if (zoom != 1.0) {
		StretchBlt(
			backDC,
			_screen.left,
			_screen.top,
			_frontWidth,
			_frontHeight,
			backDC,
			_zoom.left,
			_zoom.top,
			_zoom.right - _zoom.left,
			_zoom.bottom - _zoom.top,
			SRCCOPY);
	}

	//DC�������� ��Ӻ��縦 ����(ȭ�� ������ ����)
	BitBlt(
		frontDC,				//����޴� DC
		destX,					//����޴� ��ǥ(left)
		destY,					//����޴� ��ǥ(top)
		_frontWidth,			//����Ǵ� ����ũ��
		_frontHeight,			//����Ǵ� ����ũ��
		backDC,					//����Ǵ� DC
		_screen.left, _screen.top,	//����Ǵ� ������ǥ(left, top)
		SRCCOPY);				//�״�� �����ؿ���(���)
}

void cameraManager::updateCamera(float x, float y)
{
	_cameraBuffer->setCenter(x, y);
	cameraRange();
}

void cameraManager::updateCamera(float x1, float y1, float x2, float y2, float ratioX1, float ratioX2)
{
	//x1�� ���� ������ ������ ȭ�� ����
	if (x1 >= _cameraBuffer->getX() + ratioX2 * CAMERAX)
	{
		_cameraBuffer->setX(x1 - ratioX2 * CAMERAX);
	}
	if (x1 <= _cameraBuffer->getX() + ratioX1 * CAMERAX)
	{
		_cameraBuffer->setX(x1 - ratioX1 * CAMERAX);
	}

	//x2�� ��ǥ�� ȭ�� ������ �������� �ϸ� ī�޶� ����
	if (getCameraRIGHT() <= x2)
	{
		_cameraBuffer->setX(x2 - WINSIZEX);
	}
	else if (getCameraLEFT() >= x2)
	{
		_cameraBuffer->setX(x2);
	}

	cameraRange();
	x[0] = _cameraBuffer->getX() + ratioX1 * CAMERAX;
	x[1] = _cameraBuffer->getX() + ratioX2 * CAMERAX;
}

void cameraManager::updateCamera(float centerX, float centerY, float ratioX)
{
	if (_isFixed) return;

	if (centerX >= _cameraBuffer->getX() + ratioX * CAMERAX)
	{
		if (_isHaveToMove)
		{
			_cameraBuffer->setX(_cameraBuffer->getX() + 10);
			if (centerX <= _cameraBuffer->getX() + ratioX * CAMERAX)
			{
				_cameraBuffer->setX(centerX - ratioX * CAMERAX);
				_isHaveToMove = false;
			}
		}
		else
		{
			_cameraBuffer->setX(centerX - ratioX * CAMERAX);
		}
	}
	cameraRange();
	x[0] = _cameraBuffer->getX() + ratioX * CAMERAX;
	x[1] = 0;
	
}

/*
void cameraManager::updateCamera(float x, float y, float ratioX, float ratioY)
{
	float cX, cY;
	if (ratioX > 0 && ratioY > 0 && ratioX < 1.0f && ratioY < 1.0f)
	{
		if (x == 0.5f)
		{
			cX = x;
		}
		else
		{
			cX = x - ratioX * CAMERAX;
		}

		if (y == 0.5f)
		{
			cY = y;
		}
		else
		{
			cY = y - ratioY * CAMERAY;
		}
		setCamera(cX, cY);
	}
	cameraRange();
}
*/



void cameraManager::updateCamera(RECT& player, float ratioX, float ratioY)
{
	int width = player.right - player.left;
	int height = player.bottom - player.top;

	if (ratioX != 0)
	{
		if (ratioX < 0.5f)
		{
			if (player.left <= _cameraBuffer->getX() + ratioX * CAMERAX)
			{
				_cameraBuffer->setX(player.left - ratioX * CAMERAX);
			}
			if (player.right >= _cameraBuffer->getX() + CAMERAX)
			{
				player.right = _cameraBuffer->getX() + CAMERAX;
				player.left = player.right - width;
			}
		}
		else
		{
			if (player.right >= _cameraBuffer->getX() + ratioX * CAMERAX)
			{
				_cameraBuffer->setX(player.right - ratioX * CAMERAX);
			}
			if (player.left <= _cameraBuffer->getX())
			{
				player.left = _cameraBuffer->getX();
				player.right = player.left + width;
			}
		}
		x[0] = _cameraBuffer->getX() + ratioX * CAMERAX;
		x[1] = 0;
	}

	if (ratioY != 0)
	{
		if (ratioY < 0.5f)
		{
			if (player.top <= _cameraBuffer->getY() + ratioY * CAMERAY)
			{
				_cameraBuffer->setY(player.top - ratioY * CAMERAY);
			}
			if (player.bottom >= _cameraBuffer->getY() + CAMERAY)
			{
				player.bottom = _cameraBuffer->getY() + CAMERAY;
				player.top = player.bottom - height;
			}
		}
		else
		{
			if (player.bottom >= _cameraBuffer->getY() + ratioY * CAMERAY)
			{
				_cameraBuffer->setY(player.bottom - ratioY * CAMERAY);
			}
			if (player.top <= _cameraBuffer->getY())
			{
				player.top = _cameraBuffer->getY();
				player.bottom = player.top + height;
			}
		}
		y[0] = _cameraBuffer->getY() + ratioY * CAMERAY;
		y[1] = 0;
	}

	cameraRange();
}

void cameraManager::updateCamera(RECT& player, float ratioX1, float ratioX2, float ratioY1, float ratioY2)
{
	if (ratioX1 > 0 && ratioX1 < 0.5f)
	{
		if (player.left < _cameraBuffer->getX() + ratioX1 * CAMERAX)
		{
			_cameraBuffer->setX(player.left - ratioX1 * CAMERAX);
		}
	}

	if (ratioX2 > 0.5f && ratioX2 < 1.0f)
	{
		if (player.right > _cameraBuffer->getX() + ratioX2 * CAMERAX)
		{
			_cameraBuffer->setX(player.right - ratioX2 * CAMERAX);
		}
	}

	if (ratioY1 > 0 && ratioY1 < 0.5f)
	{
		if (player.top < _cameraBuffer->getY() + ratioY1 * CAMERAY)
		{
			_cameraBuffer->setY(player.top - ratioY1 * CAMERAY);
		}
	}

	if (ratioY2 > 0.5f && ratioY2 < 1.0f)
	{
		if (player.bottom > _cameraBuffer->getY() + ratioY2 * CAMERAY)
		{
			_cameraBuffer->setY(player.bottom - ratioY2 * CAMERAY);
		}
	}
	cameraRange();

	if (ratioX1 != 0)
	{
		x[0] = _cameraBuffer->getX() + ratioX1 * CAMERAX;
	}
	if (ratioX2 != 0)
	{
		x[1] = _cameraBuffer->getX() + ratioX2 * CAMERAX;
	}
	if (ratioY1 != 0)
	{
		y[0] = _cameraBuffer->getY() + ratioY1 * CAMERAY;
	}
	if (ratioY2 != 0)
	{
		y[1] = _cameraBuffer->getY() + ratioY2 * CAMERAY;
	}
}

float cameraManager::getCameraRIGHT()
{
	return (_cameraBuffer->getX() + CAMERAX);
}

float cameraManager::getCameraBOTTOM()
{
	return (_cameraBuffer->getY() + CAMERAY);
}

