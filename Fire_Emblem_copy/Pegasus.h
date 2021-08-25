#pragma once
#include "unit.h"
class Pegasus : public unit
{
public:
	HRESULT init(int idx, int idy, TYPE type = PLAYER);
	void update(int idx, int idy);
	void release();
	void render();
};

