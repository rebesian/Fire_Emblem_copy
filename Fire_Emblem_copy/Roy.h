#pragma once
#include "unit.h"
class Roy : public unit 
{

public:
	HRESULT init(int idx, int idy);
	void update();
	void release();
	void render();
};

