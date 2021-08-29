#pragma once
#include "gameNode.h"

class tileSet;
class battleScene : public gameNode
{
private:

	image* battleStage;
	image* playerimage;
	image* enemyimage;
	tileSet* _map;

	string _playerName;
	int _playerHp;
	int _playerAttack;
	int _playerHit;
	int _playerCrit;

	string _enemyName;
	int _enemyHp;
	int _enemyAttack;
	int _enemyHit;
	int _enemyCrit;


	int _playerCount;
	int _playerIndex;
	int _playerRenderX;

	int _enemyCount;
	int _enemyIndex;
	int _enemyRenderX;

	bool action;
	bool attack;

public:
	battleScene();
	~battleScene();

	HRESULT init();
	void release();
	void update();
	void render(int x , int y);

	void setLinkMap(tileSet* map) { _map = map; }

	void getPlayer(string name, int playerHp, int playerAttack, int playerHit, int playerCrit)
	{
		_playerName = name;
		_playerHp = playerHp;
		_playerAttack = playerAttack;
		_playerHit = playerHit;
		_playerCrit = playerCrit;
		char str[20];
		_playerName += "attack";
		playerimage = IMAGEMANAGER->findImage(_playerName);
	}
	void getEnemy(string name, int enemyHp, int enemyAttack, int enemyHit, int enemyCrit)
	{
		_enemyName = name;
		_enemyHp = enemyHp;
		_enemyAttack = enemyAttack;
		_enemyHit = enemyHit;
		_enemyCrit = enemyCrit;
		_enemyName += "attack";
		enemyimage = IMAGEMANAGER->findImage(_enemyName);
	}

	bool getAction() { return action; };
	void setAction(bool isaction) { action = isaction; }
};

