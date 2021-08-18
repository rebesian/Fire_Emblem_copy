#pragma once
#include "image.h"
#define TILESIZE 48

static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

enum TERRAIN
{
	TR_NONE,
	TR_GRASS,
	TR_KINGDOM,
	TR_MOUNTIN
};

enum TYPE
{
	PLAYER,
	ENEMY
};

enum PLAYER_ENEMY_DIRECTION
{
	NONE,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;
	
public:
	gameNode();
	virtual ~gameNode();

	int _ctrSelect;

	//HRESULT ���� ���� ��ȯ�����ε�
	//S_OK, E_FAIL, SUCCEDED
	virtual HRESULT init();			//�ʱ�ȭ �Լ�
	virtual HRESULT init(bool managerInit);
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� �Լ�
	virtual void render();	//�׸��� �Լ�

	image* getBackBuffer() { return _backBuffer; }

	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};

