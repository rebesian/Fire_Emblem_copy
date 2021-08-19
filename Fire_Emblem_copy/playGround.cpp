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

	inputImage();
	SCENEMANAGER->addScene("����", new mapToolScene);
	SCENEMANAGER->addScene("��������", new stageScene);
	SCENEMANAGER->changeScene("��������");
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



	//==================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
	
}

void playGround::inputImage()
{

	//����
	IMAGEMANAGER->addImage("load", "image/Tileset/load.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("save", "image/Tileset/save.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TR_Grass", "image/Tileset/TR_GRASS.bmp", 288, 336, 6, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TR_KingDom", "image/Tileset/TR_KingDom.bmp", 144, 336, 3, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TR_MT", "image/Tileset/TR_MT.bmp", 384, 288, 8, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("moving", "image/Tileset/moveing.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("attack", "image/Tileset/attack.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("heal", "image/Tileset/heal.bmp", 48, 48, true, RGB(255, 0, 255));

	//����������
	//�Ʊ� Idle
	IMAGEMANAGER->addFrameImage("�Ҽȳ���ƮIdle", "image/MapSprite/�Ҽȳ���ƮIdle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ȶ��Idle", "image/MapSprite/�ȶ��Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����Idle", "image/MapSprite/����Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�䰡��������ƮIdle", "image/MapSprite/�䰡��������ƮIdle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�˻�Idle", "image/MapSprite/�˻�Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������Idle", "image/MapSprite/������Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�뺴Idle", "image/MapSprite/�뺴Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����Idle", "image/MapSprite/����Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������ƮIdle", "image/MapSprite/������ƮIdle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Ʈ�����Idle", "image/MapSprite/Ʈ�����Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��óIdle", "image/MapSprite/��óIdle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�Ƹӳ���ƮIdle", "image/MapSprite/�Ƹӳ���ƮIdle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���۴�Idle", "image/MapSprite/���۴�Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	//�Ʊ� move
	IMAGEMANAGER->addFrameImage("�Ҽȳ���Ʈmove", "image/MapSprite/�Ҽȳ���Ʈmove.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ȶ��move", "image/MapSprite/�ȶ��move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����move", "image/MapSprite/����move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�䰡��������Ʈmove", "image/MapSprite/�䰡��������Ʈmove.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�˻�move", "image/MapSprite/�˻�move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������move", "image/MapSprite/������move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�뺴move", "image/MapSprite/�뺴move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����move", "image/MapSprite/����move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������Ʈmove", "image/MapSprite/������Ʈmove.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Ʈ�����move", "image/MapSprite/Ʈ�����move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��ómove", "image/MapSprite/��ómove.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�Ƹӳ���Ʈmove", "image/MapSprite/�Ƹӳ���Ʈmove.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���۴�move", "image/MapSprite/���۴�move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));



	//�� Idle
	IMAGEMANAGER->addFrameImage("enemy�Ҽȳ���ƮIdle", "image/MapSprite/enemy�Ҽȳ���ƮIdle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy�Ƹӳ���ƮIdle", "image/MapSprite/enemy�Ƹӳ���ƮIdle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy����Idle", "image/MapSprite/enemy����Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����Idle", "image/MapSprite/����Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy��óIdle", "image/MapSprite/enemy��óIdle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����Idle", "image/MapSprite/����Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	
	//�� move
	IMAGEMANAGER->addFrameImage("enemy�Ҽȳ���Ʈmove", "image/MapSprite/enemy�Ҽȳ���Ʈmove.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy�Ƹӳ���Ʈmove", "image/MapSprite/enemy�Ƹӳ���Ʈmove.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy����move", "image/MapSprite/enemy����move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy��ómove", "image/MapSprite/enemy��ómove.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����move", "image/MapSprite/����move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����move", "image/MapSprite/����move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));


	//used
	IMAGEMANAGER->addFrameImage("used�Ҽȳ���ƮIdle", "image/MapSprite/used�Ҽȳ���ƮIdle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("used�ȶ��Idle", "image/MapSprite/used�ȶ��Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("used����Idle", "image/MapSprite/used����Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("used�䰡��������ƮIdle", "image/MapSprite/used�䰡��������ƮIdle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("used�˻�Idle", "image/MapSprite/used�˻�Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("used������Idle", "image/MapSprite/used������Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("used�뺴Idle", "image/MapSprite/used�뺴Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("used����Idle", "image/MapSprite/used����Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("used������ƮIdle", "image/MapSprite/used������ƮIdle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("usedƮ�����Idle", "image/MapSprite/usedƮ�����Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("used��óIdle", "image/MapSprite/used��óIdle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("used�Ƹӳ���ƮIdle", "image/MapSprite/used�Ƹӳ���ƮIdle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("used���۴�Idle", "image/MapSprite/used���۴�Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("used����Idle", "image/MapSprite/used����Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("used����Idle", "image/MapSprite/used����Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));


	//����
	//attack
	IMAGEMANAGER->addFrameImage("�Ҽȳ���Ʈâattack", "image/character/�Ҽȳ���Ʈâattack.bmp", 1695, 128, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2�Ҽȳ���Ʈâattack", "image/character/2�Ҽȳ���Ʈâattack.bmp", 1695, 128, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy�Ҽȳ���Ʈâattack", "image/character/enemy�Ҽȳ���Ʈâattack.bmp", 1695, 128, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�Ҽȳ���Ʈ��attack", "image/character/�Ҽȳ���Ʈ��attack.bmp", 1695, 128, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2�Ҽȳ���Ʈ��attack", "image/character/2�Ҽȳ���Ʈ��attack.bmp", 1695, 128, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy�Ҽȳ���Ʈ��attack", "image/character/enemy�Ҽȳ���Ʈ��attack.bmp", 1695, 128, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����attack", "image/character/����attack.bmp", 1236, 56, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2����attack", "image/character/2����attack.bmp", 1236, 56, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy����attack", "image/character/enemy����attack.bmp", 1236, 56, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�Ƹӳ���Ʈattack", "image/character/�Ƹӳ���Ʈattack.bmp", 1236, 56, 19, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy�Ƹӳ���Ʈattack", "image/character/enemy�Ƹӳ���Ʈattack.bmp", 1957,78, 19, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��óattack", "image/character/��óattack.bmp", 768, 42, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy��óattack", "image/character/enemy��óattack.bmp", 768, 42, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�뺴attack", "image/character/�뺴attack.bmp", 2890, 139, 34, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����attack", "image/character/����attack.bmp", 1157,61, 13, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������attack", "image/character/������attack.bmp",1403, 41, 23, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����attack", "image/character/����attack.bmp", 2350, 64, 25, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����attack", "image/character/����attack.bmp", 612, 53, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ȶ���attack", "image/character/�ȶ���attack.bmp", 3146, 96, 26, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ȶ��âattack", "image/character/�ȶ��âattack.bmp", 3751, 96, 31, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�䰡��������Ʈattack", "image/character/�䰡��������Ʈattack.bmp", 2736, 105, 24, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�˻�attack", "image/character/�˻�attack.bmp", 1150, 69, 15, 1, true, RGB(255, 0, 255));


	//critcal
	IMAGEMANAGER->addFrameImage("�Ҽȳ���Ʈâcritcal", "image/character/�Ҽȳ���Ʈâcritcal.bmp", 1695, 128, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2�Ҽȳ���Ʈâcritcal", "image/character/2�Ҽȳ���Ʈâcritcal.bmp", 1695, 128, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy�Ҽȳ���Ʈâcritcal", "image/character/enemy�Ҽȳ���Ʈâcritcal.bmp", 1695, 128, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�Ҽȳ���Ʈ��critcal", "image/character/�Ҽȳ���Ʈ��critcal.bmp", 1695, 128, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2�Ҽȳ���Ʈ��critcal", "image/character/2�Ҽȳ���Ʈ��critcal.bmp", 1695, 128, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy�Ҽȳ���Ʈ��critcal", "image/character/enemy�Ҽȳ���Ʈ��critcal.bmp", 1695, 128, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����critcal", "image/character/����critcal.bmp", 927, 56, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2����critcal", "image/character/2����critcal.bmp", 927, 56, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy����critcal", "image/character/enemy����critcal.bmp", 927, 56, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�Ƹӳ���Ʈcritcal", "image/character/�Ƹӳ���Ʈcritcal.bmp", 1751, 78, 17, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy�Ƹӳ���Ʈcritcal", "image/character/enemy�Ƹӳ���Ʈcritcal.bmp", 1751, 78, 17, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��ócritcal", "image/character/��ócritcal.bmp", 720, 42, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy��ócritcal", "image/character/enemy��ócritcal.bmp", 720, 42, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�뺴critcal", "image/character/�뺴critcal.bmp", 4250, 139, 50, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����critcal", "image/character/����critcal.bmp", 1335, 61, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����critcal", "image/character/����critcal.bmp", 3760, 64, 25, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����critcal", "image/character/����critcal.bmp", 1224, 53, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ȶ���critcal", "image/character/�ȶ���critcal.bmp",2662, 96, 22, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ȶ��âcritcal", "image/character/�ȶ��âcritcal.bmp", 2662, 96, 22, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�䰡��������Ʈcritcal", "image/character/�䰡��������Ʈcritcal.bmp",1140, 105, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�˻�critcal", "image/character/�˻�critcal.bmp", 1850, 69, 25, 1, true, RGB(255, 0, 255));



	//avoid
	IMAGEMANAGER->addFrameImage("�Ҽȳ���Ʈâavoid", "image/character/�Ҽȳ���Ʈâavoid.bmp", 339, 84, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2�Ҽȳ���Ʈâavoid", "image/character/2�Ҽȳ���Ʈâavoid.bmp", 339, 84, 3, 1,  true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy�Ҽȳ���Ʈâavoid", "image/character/enemy�Ҽȳ���Ʈâavoid.bmp", 339, 84, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�Ҽȳ���Ʈ��avoid", "image/character/�Ҽȳ���Ʈ��avoid.bmp", 339, 84, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2�Ҽȳ���Ʈ��avoid", "image/character/2�Ҽȳ���Ʈ��avoid.bmp", 339, 84, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy�Ҽȳ���Ʈ��avoid", "image/character/enemy�Ҽȳ���Ʈ��avoid.bmp", 339, 84, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����avoid", "image/character/����avoid.bmp", 309, 56, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2����avoid", "image/character/2����avoid.bmp", 309, 56, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy����avoid", "image/character/enemy����avoid.bmp", 309, 56, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�Ƹӳ���Ʈavoid", "image/character/�Ƹӳ���Ʈavoid.bmp", 515, 78, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy�Ƹӳ���Ʈavoid", "image/character/enemy�Ƹӳ���Ʈavoid.bmp", 515, 78, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��óavoid", "image/character/��óavoid.bmp", 144, 42, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy��óavoid", "image/character/enemy��óavoid.bmp", 144, 42, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�뺴avoid", "image/character/�뺴avoid.bmp", 425, 139, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����avoid", "image/character/����avoid.bmp", 267, 61, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������avoid", "image/character/������avoid.bmp", 183, 41, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����avoid", "image/character/����avoid.bmp", 470, 64, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����avoid", "image/character/����avoid.bmp", 306, 53, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ȶ���avoid", "image/character/�ȶ���avoid.bmp", 635, 96, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ȶ��âavoid", "image/character/�ȶ��âavoid.bmp", 635, 96, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�䰡��������Ʈavoid", "image/character/�䰡��������Ʈavoid.bmp", 342, 105, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�˻�avoid", "image/character/�˻�avoid.bmp", 229, 69, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�˻�end", "image/character/�˻�end.bmp", 814, 69, 11, 1, true, RGB(255, 0, 255));

	//heal
	IMAGEMANAGER->addFrameImage("Ʈ�����heal", "image/character/Ʈ�����heal.bmp",720, 64, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������Ʈend", "image/character/������Ʈheal.bmp", 198, 38, 6, 1, true, RGB(255, 0, 255));

	//throw
	IMAGEMANAGER->addFrameImage("�Ҽȳ���Ʈthrow", "image/character/�Ҽȳ���Ʈthrow.bmp", 804, 84, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2�Ҽȳ���Ʈthrow", "image/character/2�Ҽȳ���Ʈthrow.bmp", 904, 84, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy�Ҽȳ���Ʈthrow", "image/character/enemy�Ҽȳ���Ʈthrow.bmp", 904, 84, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�Ƹӳ���Ʈthrow", "image/character/�Ƹӳ���Ʈthrow.bmp", 824, 78, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy�Ƹӳ���Ʈthrow", "image/character/enemy�Ƹӳ���Ʈthrow.bmp", 824, 78, 8, 1, true, RGB(255, 0, 255));

}
