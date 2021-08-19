#pragma once
#include "Roy.h"
#include "warrior.h"
#include "Swordsman.h"
#include "paladin.h"
#include "archer.h"
#include "ArmorKnight.h"
#include "mage.h"
#include "mercenary.h"
#include "Pegasus.h"
#include "socialKnight.h"
#include "transport.h"
#include ""

class playerManger
{
public:
	HRESULT init(int idx, int idy, TYPE type = PLAYER);
	void update();
	void release();
	void render();
};

