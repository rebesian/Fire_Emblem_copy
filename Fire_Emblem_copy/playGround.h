#pragma once
#include "gameNode.h"
#include "mapTool.h"
#include "tileSet.h"
class playGround : public gameNode
{
private:

	mapTool* _mapTool;
	tileSet* _tileSet;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	
	
};

