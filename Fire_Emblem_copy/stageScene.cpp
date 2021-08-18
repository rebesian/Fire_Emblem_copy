#include "stdafx.h"
#include "stageScene.h"

HRESULT stageScene::init()
{
	_tileSet = new tileSet;
	_tileSet->init();
	_tileSet->load();

	return S_OK;
}

void stageScene::update()
{
	_tileSet->update();

}

void stageScene::release()
{

}

void stageScene::render()
{
	_tileSet->render();
}
