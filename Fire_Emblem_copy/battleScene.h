#pragma once
#include "gameNode.h"

class tileSet;
class battleScene : public gameNode
{
private:
	struct UI
	{
		image *hit = IMAGEMANAGER->findImage("hit"), *damage = IMAGEMANAGER->findImage("damage"), *crit = IMAGEMANAGER->findImage("crit"), *hp1 = IMAGEMANAGER->findImage("hpbar1"), *hp2 = IMAGEMANAGER->findImage("hpbar2");
	
	};

	image* battleStage;
	image* playerimage;
	image* enemyimage;
	UI _player, _enemy;
	tileSet* _map;
	TYPE type;

	string _playerName;
	float _playerHp;
	float _playerCurrentHp;
	int _playerAttack;
	int _playerHit;
	int _playerCrit;

	string _enemyName;
	float _enemyHp;
	float _enemyCurrentHp;
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
	bool _truePlayerFalseEnemy;
	bool attack;

public:
	battleScene();
	~battleScene();

	HRESULT init();
	void release();
	void update(TYPE _type);
	void render(int x , int y , bool truePlayerFalseEnemy);

	void setLinkMap(tileSet* map) { _map = map; }

	void getPlayer(string name, int playerHp, int playerAttack, int playerHit, int playerCrit)
	{
		_playerIndex = 0;
		_playerCount = 0;
		_playerName = name;
		_playerCurrentHp = _playerHp = playerHp;
		_playerAttack = playerAttack;
		_playerHit = playerHit;
		_playerCrit = playerCrit;
		char str[20];
		_playerName += "attack";
		playerimage = IMAGEMANAGER->findImage(_playerName);
		_truePlayerFalseEnemy = true;
		playerStart(_playerName);
	}
	void getEnemy(string name, int enemyHp, int enemyAttack, int enemyHit, int enemyCrit)
	{
		_enemyIndex = 0;
		_enemyCount = 0;
		_enemyName = "enemy";
		_enemyName += name;
		_enemyCurrentHp = _enemyHp = enemyHp;
		_enemyAttack = enemyAttack;
		_enemyHit = enemyHit;
		_enemyCrit = enemyCrit;
		_enemyName += "attack";
		enemyimage = IMAGEMANAGER->findImage(_enemyName);
		_truePlayerFalseEnemy = false;
		enemyStart(_enemyName);
	}

	void playerStart(string name);
	void enemyStart(string name);
	void playerAction(string name);
	void enemyAction(string name);

	int getPlayerCurrentHp() { return _playerCurrentHp; }
	int getEnemyCurrentHp() { return _enemyCurrentHp; }
	bool getAction() { return action; };
	void setAction(bool isaction) { action = isaction; }
};

