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

	//HRESULT 마소 전용 반환형식인데
	//S_OK, E_FAIL, SUCCEDED
	virtual HRESULT init();			//초기화 함수
	virtual HRESULT init(bool managerInit);
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 함수
	virtual void render();	//그리기 함수

	image* getBackBuffer() { return _backBuffer; }

	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};

