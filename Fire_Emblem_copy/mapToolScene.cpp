#include "stdafx.h"
#include "mapToolScene.h"

HRESULT mapToolScene::init()
{
	_mapTool = new mapTool;
	_tileSet = new tileSet;
	_mapTool->init();
	_tileSet->init();
	_mapTool->setLinkMemoryTileSet(_tileSet);
	_mapTool->setUp();
	return S_OK;
}

void mapToolScene::release()
{

}

void mapToolScene::update()
{
	_mapTool->update();
}

void mapToolScene::render()
{
	_tileSet->render();
	CAMERAMANAGER->render(_tileSet->getTileBuffer(), getMemDC());
	_mapTool->render();
	//CAMERAMANAGER->render(_tileSet->getTileBuffer(), getMemDC());
}
