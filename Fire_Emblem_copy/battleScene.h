#pragma once
#include "gameNode.h"

class tileSet;
class battleScene : public gameNode
{
private:
	struct UI
	{
		image *hit = IMAGEMANAGER->findImage("hit"), *damage = IMAGEMANAGER->findImage("damage"), *crit = IMAGEMANAGER->findImage("crit"), *hp1 = IMAGEMANAGER->findImage("hpbar1"), *hp2 = IMAGEMANAGER->findImage("hpbar2");
		image *num1, *num2, *num3, *num4, *num5, *num6, *num7, *num8;
	};

	image* battleStage;
	image* playerimage;
	image* enemyimage;
	UI _player, _enemy;
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


	float _playerActionX, _playerActionY;
	float _enemyActionX, _enemyActionY;

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
	void update(TYPE type);
	void render(int x , int y , bool truePlayerFalseEnemy);

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
		playerStart(_playerName);
	}
	void getEnemy(string name, int enemyHp, int enemyAttack, int enemyHit, int enemyCrit)
	{
		_enemyName = "enemy";
		_enemyName += name;
		_enemyHp = enemyHp;
		_enemyAttack = enemyAttack;
		_enemyHit = enemyHit;
		_enemyCrit = enemyCrit;
		_enemyName += "attack";
		enemyimage = IMAGEMANAGER->findImage(_enemyName);
		enemyStart(_enemyName);
	}

	void playerStart(string name);
	void enemyStart(string name);
	void playerAction(string name);
	void enemyAction(string name);

	bool getAction() { return action; };
	void setAction(bool isaction) { action = isaction; }
};

