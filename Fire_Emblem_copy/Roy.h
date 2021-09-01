#pragma once
#include "unit.h"

class Roy : public unit 
{

public:
	HRESULT init(int idx, int idy, TYPE type);
	void update(int idx, int idy);
	void release();
	void render();

	void action();
};

