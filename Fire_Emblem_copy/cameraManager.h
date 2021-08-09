#pragma once
#include "singletonBase.h"
#include "image.h"


class cameraManager : public singletonBase<cameraManager>
{
private:
	image* _cameraBuffer;
	float x[2];
	float y[2];
	void cameraRange(); //ī�޶� ��� ������ ������ �ʰ� ����� �Լ�

	bool _isHaveToMove; //ī�޶� ������ Ǯ���� ���������ϴ���

	//����
	//ī�޶� ���ߴ� ȭ�� ũ��(WINSIZEX, WINSIZEY)�� ��ǥ(left, right, top, bottom)
	RECT _screen, _zoom;
	int _backWidth, _backHeight;	//backDC ũ��
	int _frontWidth, _frontHeight;	//frontDC ũ��
	float _count;

public:
	//����=================================================
	cameraManager();
	~cameraManager();

	HRESULT init(int width, int height);
	//ī�޶� ��ġ ����
	void updateScreen(float standardX, float standardY,
		float ratioX = 0.5f, float ratioY = 0.5f, float zoom = 1.0f);
	//ī�޶� ����
	void vibrateScreen(float standardX, float standardY,
		float magnitude = 5.0f);
	//ī�޶� ���
	void render(HDC frontDC, int destX, int destY, HDC backDC,
		float zoom = 1.0f);

	void setBackScreenSize(float width, float height) { _backWidth = width, _backHeight = height; }
	//void setFrontScreenSize(float width, float height) { _frontWidth = width, _frontHeight = height; }
	float getBackScreenWidth() { return _backWidth; }
	float getBackScreenHeight() { return _backHeight; }
	//=====================================================

	bool _isFixed; //ī�޶� �����Ǿ�����
	
	HRESULT init();
	void release();
	void update();
	void render(image* backBuffer, HDC frontDC);

	//ī�޶� ������ǥ�� ����
	void setCameraCenter(float x, float y)
	{
		_cameraBuffer->setCenter(x, y);
	}

	//ī�޶� left, top ��ǥ�� ����
	void setCamera(float x, float y)
	{
		_cameraBuffer->setX(x);
		_cameraBuffer->setY(y);
	}

	//ī�޶� ���Ͱ����� ������(�÷��̾ �߽����� �����̰� ������ ���)
	void updateCamera(float x, float y);

	/*
	//�÷��̾ ī�޶� �߽��� �ƴ� �ٸ� ��ġ�� �ְ� �÷��̾ ���� �����̰� ���� �� ���)
	void updateCamera(float x, float y, float ratioX, float ratioY);
	*/

	//�� ��ü�� x, y��ǥ�� �������� ī�޶� ���� ����
	void updateCamera(float x1, float y1, float x2, float y2, float ratioX1, float ratioX);

	//�÷��̾ x�� �������� ������� ������ �Ѿ�� ī�޶� ������(0.5f<ratio<1.0f)
	void updateCamera(float centerX, float centerY, float ratioX);

	// RECT�� X��, y������ ������� ������ �Ѿ�� ī�޶� ������( 0 < ratio < 1.0f)
	// 0�� ������ �� �� ��� ����
	void updateCamera(RECT& player, float ratioX, float ratioY);

	/*
	RECT�� ratio1 �� ratio2 ���̿��� ����� ī�޶� ������(0<ratio1<0.5f, 0.5f<ratio2<1.0f)
	ratio1�� x��->RECT.left, y��->RECT.top ����, ratio2�� x��->RECT.right, y�� ->RECT.bottom �������� ����, ��, ������, �Ʒ��� ������
	���� ������� ���� �ִٸ� 0�� ������ �� (x��, y�� �ϳ����̸� float �ΰ��� �ִ� updateCamera ��õ)
	*/
	void updateCamera(RECT& player, float ratioX1, float ratioX2, float ratioY1, float ratioY2);


	void setCameraX(float x) { _cameraBuffer->setX(x); }
	void setCameraY(float y) { _cameraBuffer->setY(y); }

	void setCameraCenterX(float x) { _cameraBuffer->setX(x - (_cameraBuffer->getWidth() / 2)); }
	void setCameraCenterY(float y) { _cameraBuffer->setY(y - (_cameraBuffer->getHeight() / 2)); }

	float getCameraLEFT() { return _cameraBuffer->getX(); }
	float getCameraTOP() { return _cameraBuffer->getY(); }
	
	float getCameraRIGHT();
	float getCameraBOTTOM();

	float getCameraCenterX() { return _cameraBuffer->getCenterX(); }
	float getCameraCenterY() { return _cameraBuffer->getCenterY(); }
	

	HDC getCameraBuffer() { return _cameraBuffer->getMemDC(); }
};

