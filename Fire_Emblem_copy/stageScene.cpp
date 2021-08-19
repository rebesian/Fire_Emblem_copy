#include "stdafx.h"
#include "stageScene.h"

HRESULT stageScene::init()
{
	_tileSet = new tileSet;
	_tileSet->init();
	_tileSet->load();

	_warrior = new warrior;
	_warrior->setLinkMap(_tileSet);
	_warrior->init(2,5,ENEMY);
	
	_roy = new Roy;
	_roy->setLinkMap(_tileSet);
	_roy->init(2, 10);

	return S_OK;
}

void stageScene::update()
{
	_tileSet->update();
	_warrior->update();
	_roy->update();
}

void stageScene::release()
{

}

void stageScene::render()
{
	
	_tileSet->render();
	_warrior->render();
	_roy->render();
	CAMERAMANAGER->render(_tileSet->getTileBuffer(), getMemDC());
}
