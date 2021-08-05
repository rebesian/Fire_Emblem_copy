#pragma once
#include "tileNode.h"
#include "gameNode.h"

class tankMap : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];		//Ÿ��
	DWORD _attribute[TILEX * TILEY];	//Ÿ�ϼӼ�

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
	//Ÿ�ϼӼ��� ���� �����ڵ� �������� ��ũ ��ü�� �����Ҽ�����.
	
	DWORD* getAttribute() { return _attribute; }

	int getPosFirst() { return _pos[0]; }
	int getPosSecond() { return _pos[1]; }
};

