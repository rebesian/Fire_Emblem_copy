#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기다 하세요 제발
HRESULT playGround::init()
{
	gameNode::init(true);

	SCENEMANAGER->addScene("땅끄씬", new tankScene);

	SCENEMANAGER->changeScene("땅끄씬");
	
	
	return S_OK;
}

//메모리 해제는 여기다 하세요 제발
void playGround::release()
{
	gameNode::release();


}


void playGround::update()
{
	gameNode::update();

	SCENEMANAGER->update();
	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================제발 이 사이에 좀 그립시다==========================

	SCENEMANAGER->render();


	//TIMEMANAGER->render(getMemDC());
	//==================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
