#include "stdafx.h"
#include "stageScene.h"
#include "warrior.h"
HRESULT stageScene::init()
{
	_tileSet = new tileSet;
	_tileSet->init();
	_tileSet->load();

	_warrior = new warrior;
	_warrior->setLinkMap(_tileSet);
	_warrior->init(2,5);
	

	return S_OK;
}

void stageScene::update()
{
	_tileSet->update();
	_warrior->update();
}

void stageScene::release()
{

}

void stageScene::render()
{
	_tileSet->render();
	_warrior->render();
}
