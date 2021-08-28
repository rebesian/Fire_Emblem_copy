#pragma once
#include "gameNode.h"
class battleScene : public gameNode
{
private:

	image* battleStage;


	string _playerName;
	int _playerHp;
	int _playerAttack;
	int _playerAvoid;
	int _playerHit;
	int _playerCrit;

	string _enemyName;
	int _enemyHp;
	int _enemyAttack;
	int _enemyAvoid;
	int _enemyHit;
	int _enemyCrit;

public:
	battleScene();
	~battleScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void getPlayer(string name, int playerHp, int playerAttack, int playerAvoid, int playerHit, int playerCrit)
	{
		_playerName = name;
		_playerAttack = playerAttack;
		_playerAvoid = playerAvoid;
		_playerHit = playerHit;
		_playerCrit = playerCrit;

	}
	void getEnemy(string name, int enemyHp, int enemyAttack, int enemyAvoid, int enemyHit, int enemyCrit)
	{
		_enemyName = name;
		_enemyHp = enemyHp;
		_enemyAttack = enemyAttack;
		_enemyHit = enemyHit;
		_enemyCrit = enemyCrit;
	}
};

