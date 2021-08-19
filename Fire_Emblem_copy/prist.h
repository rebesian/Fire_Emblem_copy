#pragma once
#include "unit.h"

class prist : public unit
{
public:
	HRESULT init(int idx, int idy, TYPE type = PLAYER);
	void update();
	void release();
	void render();
};

