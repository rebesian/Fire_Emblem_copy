#pragma once
#include "gameNode.h"
#include "mapToolScene.h"
#include "stageScene.h"

class playGround : public gameNode
{
private:

	mapToolScene* _mapTool;
	stageScene* _stageScene;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	
	
};

