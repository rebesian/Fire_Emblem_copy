#pragma once
#include "gameNode.h"
class unit : public gameNode
{
protected:

public:
	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();
};

