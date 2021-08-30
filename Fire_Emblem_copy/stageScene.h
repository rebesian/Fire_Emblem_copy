#pragma once
#include "gameNode.h"
#include "tileSet.h"
#include "playerManger.h"
#include "enemyManger.h"
#include "battleScene.h"
class stageScene : public gameNode
{
private:
	struct POINTER
	{
		int indexX;
		int indexY;
		RECT _rc;
		image* _img = IMAGEMANAGER->findImage("현재타일");
	};

	tileSet* _tileSet;
	battleScene* _battleScene;
	warrior* _warrior;
	Roy* _roy;
	POINTER _pt;

	playerManger* _pm;
	enemyManger* _em;


	int mapSizeX;
	int mapSizeY;
	
	int useCount;
	int selectEnemy;
	int _playerPoint;
	int _enemyPoint;

	int enemyCount;

	bool isbattle;
	bool isMoveSelect;
	bool isAttackSelect;
	bool truePlayerFalseEnemy;
	bool enemytargetOn;

public:

	HRESULT init();
	void update();
	void release();
	void render();

};

