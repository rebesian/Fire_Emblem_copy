#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ�� ����� �ϼ��� ����
HRESULT playGround::init()
{
	gameNode::init(true);

	SCENEMANAGER->addScene("������", new tankScene);

	SCENEMANAGER->changeScene("������");
	
	
	return S_OK;
}

//�޸� ������ ����� �ϼ��� ����
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
	//================���� �� ���̿� �� �׸��ô�==========================

	SCENEMANAGER->render();


	//TIMEMANAGER->render(getMemDC());
	//==================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
