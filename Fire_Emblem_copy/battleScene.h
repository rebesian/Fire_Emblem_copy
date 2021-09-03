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
	string _enemyName;

	string _playerimageName;
	float _playerHp;
	float _playerCurrentHp;
	int _playerAttack;
	int _playerHit;
	int _playerCrit;

	string _enemyimageName;
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
		_playerimageName = name;
		_playerName = name;
		_playerCurrentHp = _playerHp = playerHp;
		_playerAttack = playerAttack;
		_playerHit = playerHit;
		_playerCrit = playerCrit;
		char str[20];
		_playerimageName += "attack";
		playerimage = IMAGEMANAGER->findImage(_playerimageName);
		_truePlayerFalseEnemy = true;
		playerStart(_playerimageName);
	}
	void getEnemy(string name, int enemyHp, int enemyAttack, int enemyHit, int enemyCrit)
	{
		_enemyIndex = 0;
		_enemyCount = 0;
		_enemyimageName = "enemy";
		_enemyimageName += name;
		_enemyName = name;
		_enemyCurrentHp = _enemyHp = enemyHp;
		_enemyAttack = enemyAttack;
		_enemyHit = enemyHit;
		_enemyCrit = enemyCrit;
		_enemyimageName += "attack";
		enemyimage = IMAGEMANAGER->findImage(_enemyimageName);
		_truePlayerFalseEnemy = false;
		enemyStart(_enemyimageName);
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

