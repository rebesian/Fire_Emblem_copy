#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기다 하세요 제발
HRESULT playGround::init()
{
	gameNode::init(true);

	IMAGEMANAGER->addImage("load", "image/Tileset/load.bmp" , 64, 64, true, RGB(255,0,255));
	IMAGEMANAGER->addImage("save", "image/Tileset/save.bmp" , 64,64, true , RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("TR_Grass", "image/Tileset/TR_GRASS.bmp", 288, 336, 6, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TR_KingDom", "image/Tileset/TR_KingDom.bmp", 144, 336, 3, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TR_MT", "image/Tileset/TR_MT.bmp", 384, 288, 8, 6, true, RGB(255, 0, 255));
	_mapTool = new mapTool;
	_tileSet = new tileSet;
	_mapTool->init();
	_tileSet->init();
	_mapTool->setLinkMemoryTileSet(_tileSet);
	_mapTool->setUp();

	return S_OK;
}

//메모리 해제는 여기다 하세요 제발
void playGround::release()
{
	gameNode::release();


}


void playGround::update()
{
	gameNode::update();

	
	_mapTool->update();
	


}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================제발 이 사이에 좀 그립시다==========================

	_tileSet->render();
	_mapTool->render();
	char str[20];
	sprintf_s(str, "x : %d, y : %d", _ptMouse.x, _ptMouse.y);
	TextOut(getMemDC(), _ptMouse.x, _ptMouse.y, str, strlen(str));

	//==================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
	
}
