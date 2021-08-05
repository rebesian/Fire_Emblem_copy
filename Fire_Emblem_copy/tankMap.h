#pragma once
#include "tileNode.h"
#include "gameNode.h"

class tankMap : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];		//타일
	DWORD _attribute[TILEX * TILEY];	//타일속성

	int _pos[2];

public:
	tankMap();
	~tankMap();

	HRESULT init();
	void release();
	void update();
	void render();

	void load();


	tagTile* getTile() { return _tiles; }

	//STEP02
	//타일속성에 대한 접근자도 만들어줘야 탱크 객체랑 연산할수있음.
	
	DWORD* getAttribute() { return _attribute; }

	int getPosFirst() { return _pos[0]; }
	int getPosSecond() { return _pos[1]; }
};

