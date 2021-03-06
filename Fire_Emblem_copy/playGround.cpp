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

	inputImage();
	SCENEMANAGER->addScene("맵툴", new mapToolScene);
	SCENEMANAGER->addScene("스테이지", new stageScene);
	SCENEMANAGER->changeScene("맵툴");
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

	//==================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
	
}

void playGround::inputImage()
{

	//맵툴
	IMAGEMANAGER->addImage("load", "image/Tileset/load.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("save", "image/Tileset/save.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TR_Grass", "image/Tileset/TR_GRASS.bmp", 288, 336, 6, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TR_KingDom", "image/Tileset/TR_KingDom.bmp", 144, 336, 3, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TR_MT", "image/Tileset/TR_MT.bmp", 384, 288, 8, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("movement", "image/MapSprite/movement.bmp", 768, 144, 16, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("현재타일", "image/MapSprite/현재타일.bmp", 48, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("route", "image/MapSprite/route.bmp", 192, 192, 4, 4, true, RGB(255, 0, 255));
	
	//UI
	IMAGEMANAGER->addImage("전투Hud", "image/UI/전투Hud1.bmp", 960, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("0", "image/UI/0.bmp", 24,24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("1", "image/UI/1.bmp", 24, 24,  true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2", "image/UI/2.bmp", 24, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("3", "image/UI/3.bmp", 24, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("4", "image/UI/4.bmp", 24, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("5", "image/UI/5.bmp", 24, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("6", "image/UI/6.bmp", 24, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("7", "image/UI/7.bmp", 24, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("8", "image/UI/8.bmp", 24, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("9", "image/UI/9.bmp", 24, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hit", "image/UI/hit.bmp", 39, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("damage", "image/UI/damage.bmp", 45, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("crit", "image/UI/crit.bmp", 39, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hpbar1", "image/UI/hpbar1.bmp", 256, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hpbar2", "image/UI/hpbar2.bmp", 256, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("에너미페이즈", "image/UI/에너미페이즈.bmp", 960, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("플레이어페이즈", "image/UI/플레이어페이즈.bmp", 960, 600, true, RGB(255, 0, 255));

	//병과아이콘
	//아군 Idle
	IMAGEMANAGER->addFrameImage("소셜나이트Idle", "image/MapSprite/소셜나이트Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("팔라딘Idle", "image/MapSprite/팔라딘Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("로이Idle", "image/MapSprite/로이Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("페가수스나이트Idle", "image/MapSprite/페가수스나이트Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("검사Idle", "image/MapSprite/검사Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("메이지Idle", "image/MapSprite/메이지Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("용병Idle", "image/MapSprite/용병Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("전사Idle", "image/MapSprite/전사Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("프리스트Idle", "image/MapSprite/프리스트Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("트루버돌Idle", "image/MapSprite/트루버돌Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("아처Idle", "image/MapSprite/아처Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("아머나이트Idle", "image/MapSprite/아머나이트Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("수송대Idle", "image/MapSprite/수송대Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	//아군 move
	IMAGEMANAGER->addFrameImage("소셜나이트move", "image/MapSprite/소셜나이트move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("팔라딘move", "image/MapSprite/팔라딘move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("로이move", "image/MapSprite/로이move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("페가수스나이트move", "image/MapSprite/페가수스나이트move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("검사move", "image/MapSprite/검사move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("메이지move", "image/MapSprite/메이지move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("용병move", "image/MapSprite/용병move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("전사move", "image/MapSprite/전사move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("프리스트move", "image/MapSprite/프리스트move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("트루버돌move", "image/MapSprite/트루버돌move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("아처move", "image/MapSprite/아처move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("아머나이트move", "image/MapSprite/아머나이트move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("수송대move", "image/MapSprite/수송대move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));



	//적 Idle
	IMAGEMANAGER->addFrameImage("enemy소셜나이트Idle", "image/MapSprite/enemy소셜나이트Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy아머나이트Idle", "image/MapSprite/enemy아머나이트Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy전사Idle", "image/MapSprite/enemy전사Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("군인Idle", "image/MapSprite/군인Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy아처Idle", "image/MapSprite/enemy아처Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("산적Idle", "image/MapSprite/산적Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	
	//적 move
	IMAGEMANAGER->addFrameImage("enemy소셜나이트move", "image/MapSprite/enemy소셜나이트move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy아머나이트move", "image/MapSprite/enemy아머나이트move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy전사move", "image/MapSprite/enemy전사move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy아처move", "image/MapSprite/enemy아처move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("군인move", "image/MapSprite/군인move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("산적move", "image/MapSprite/산적move.bmp", 384, 384, 4, 4, true, RGB(255, 0, 255));


	//used
	IMAGEMANAGER->addFrameImage("used소셜나이트Idle", "image/MapSprite/used소셜나이트Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("used팔라딘Idle", "image/MapSprite/used팔라딘Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("used로이Idle", "image/MapSprite/used로이Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("used페가수스나이트Idle", "image/MapSprite/used페가수스나이트Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("used검사Idle", "image/MapSprite/used검사Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("used메이지Idle", "image/MapSprite/used메이지Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("used용병Idle", "image/MapSprite/used용병Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("used전사Idle", "image/MapSprite/used전사Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("used프리스트Idle", "image/MapSprite/used프리스트Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("used트루버돌Idle", "image/MapSprite/used트루버돌Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("used아처Idle", "image/MapSprite/used아처Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("used아머나이트Idle", "image/MapSprite/used아머나이트Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("used수송대Idle", "image/MapSprite/used수송대Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("used군인Idle", "image/MapSprite/used군인Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("used산적Idle", "image/MapSprite/used산적Idle.bmp", 288, 192, 3, 2, true, RGB(255, 0, 255));


	//전투
	//attack
	IMAGEMANAGER->addFrameImage("소셜나이트attack", "image/character/소셜나이트창attack.bmp", 6780,336, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2소셜나이트attack", "image/character/2소셜나이트창attack.bmp", 6780, 336, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy소셜나이트attack", "image/character/enemy소셜나이트창attack.bmp", 6780, 336, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("소셜나이트검attack", "image/character/소셜나이트검attack.bmp", 1695, 128, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2소셜나이트검attack", "image/character/2소셜나이트검attack.bmp", 1695, 128, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy소셜나이트검attack", "image/character/enemy소셜나이트검attack.bmp", 1695, 128, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("전사attack", "image/character/2전사attack.bmp", 4944, 244, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2전사attack", "image/character/전사attack.bmp", 4944, 244, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy전사attack", "image/character/enemy전사attack.bmp", 4944, 244, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("아머나이트attack", "image/character/아머나이트attack.bmp", 7828, 312, 19, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy아머나이트attack", "image/character/enemy아머나이트attack.bmp", 7828, 312, 19, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("아처attack", "image/character/아처attack.bmp", 768, 42, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy아처attack", "image/character/enemy아처attack.bmp", 768, 42, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("용병attack", "image/character/용병attack.bmp",11560, 556, 34, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy군인attack", "image/character/군인attack.bmp", 4628, 244, 13, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("메이지attack", "image/character/메이지attack.bmp",1403, 41, 23, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("로이attack", "image/character/로이attack.bmp", 9400, 256, 25, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy산적attack", "image/character/산적attack.bmp", 2448, 212, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("팔라딘검attack", "image/character/팔라딘검attack.bmp", 3146, 96, 26, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("팔라딘attack", "image/character/팔라딘창attack.bmp", 15004,384, 31, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("페가수스나이트attack", "image/character/페가수스나이트attack.bmp", 2736, 105, 24, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("검사attack", "image/character/검사attack.bmp", 1150, 69, 15, 1, true, RGB(255, 0, 255));


	//critcal
	IMAGEMANAGER->addFrameImage("소셜나이트critcal", "image/character/소셜나이트창critcal.bmp", 6780, 336, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2소셜나이트critcal", "image/character/2소셜나이트창critcal.bmp", 6780, 336, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy소셜나이트critcal", "image/character/enemy소셜나이트창critcal.bmp", 6780, 336, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("소셜나이트검critcal", "image/character/소셜나이트검critcal.bmp", 1695, 128, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2소셜나이트검critcal", "image/character/2소셜나이트검critcal.bmp", 1695, 128, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy소셜나이트검critcal", "image/character/enemy소셜나이트검critcal.bmp", 1695, 128, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("전사critcal", "image/character/전사critcal.bmp", 3708, 224, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2전사critcal", "image/character/2전사critcal.bmp", 3708, 224, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy전사critcal", "image/character/enemy전사critcal.bmp", 3708, 224, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("아머나이트critcal", "image/character/아머나이트critcal.bmp", 7004 , 312, 17, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy아머나이트critcal", "image/character/enemy아머나이트critcal.bmp", 7004, 312, 17, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("아처critcal", "image/character/아처critcal.bmp", 720, 42, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy아처critcal", "image/character/enemy아처critcal.bmp", 720, 42, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("용병critcal", "image/character/용병critcal.bmp", 17000, 556, 50, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("군인critcal", "image/character/군인critcal.bmp", 5320 ,224 , 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("로이critcal", "image/character/로이critcal.bmp", 3760, 64, 25, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("산적critcal", "image/character/산적critcal.bmp", 4896, 212, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("팔라딘검critcal", "image/character/팔라딘검critcal.bmp",2662, 96, 22, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("팔라딘critcal", "image/character/팔라딘창critcal.bmp", 10648, 384 , 22, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("페가수스나이트critcal", "image/character/페가수스나이트critcal.bmp",1140, 105, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("검사critcal", "image/character/검사critcal.bmp", 1850, 69, 25, 1, true, RGB(255, 0, 255));



	//avoid
	IMAGEMANAGER->addFrameImage("소셜나이트avoid", "image/character/소셜나이트창avoid.bmp", 6780 , 336, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2소셜나이트avoid", "image/character/2소셜나이트창avoid.bmp", 6780, 336, 3, 1,  true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy소셜나이트avoid", "image/character/enemy소셜나이트창avoid.bmp", 6780, 336, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("소셜나이트검avoid", "image/character/소셜나이트검avoid.bmp", 6780, 336, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2소셜나이트검avoid", "image/character/2소셜나이트검avoid.bmp", 6780, 336, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy소셜나이트검avoid", "image/character/enemy소셜나이트검avoid.bmp", 6780, 336, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("전사avoid", "image/character/2전사avoid.bmp", 1236, 224, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2전사avoid", "image/character/전사avoid.bmp", 1236, 224, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy전사avoid", "image/character/enemy전사avoid.bmp", 1236, 224, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("아머나이트avoid", "image/character/아머나이트avoid.bmp", 2060, 312, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy아머나이트avoid", "image/character/enemy아머나이트avoid.bmp", 2060, 312, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("아처avoid", "image/character/아처avoid.bmp", 144, 42, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy아처avoid", "image/character/enemy아처avoid.bmp", 144, 42, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("용병avoid", "image/character/용병avoid.bmp", 1700, 556, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("군인avoid", "image/character/군인avoid.bmp", 1068 , 244, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("메이지avoid", "image/character/메이지avoid.bmp", 183, 41, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("로이avoid", "image/character/로이avoid.bmp", 1880 , 256, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("산적avoid", "image/character/산적avoid.bmp", 1224 , 212, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("팔라딘검avoid", "image/character/팔라딘검avoid.bmp", 2540, 384, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("팔라딘avoid", "image/character/팔라딘창avoid.bmp", 2540 , 384, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("페가수스나이트avoid", "image/character/페가수스나이트avoid.bmp", 342, 105, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("검사avoid", "image/character/검사avoid.bmp", 229, 69, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("검사end", "image/character/검사end.bmp", 814, 69, 11, 1, true, RGB(255, 0, 255));

	//heal
	IMAGEMANAGER->addFrameImage("트루버드heal", "image/character/트루버드heal.bmp",720, 64, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("프리스트end", "image/character/프리스트heal.bmp", 198, 38, 6, 1, true, RGB(255, 0, 255));

	//throw
	IMAGEMANAGER->addFrameImage("소셜나이트throw", "image/character/소셜나이트throw.bmp", 804, 84, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("2소셜나이트throw", "image/character/2소셜나이트throw.bmp", 904, 84, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy소셜나이트throw", "image/character/enemy소셜나이트throw.bmp", 904, 84, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("아머나이트throw", "image/character/아머나이트throw.bmp", 824, 78, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemy아머나이트throw", "image/character/enemy아머나이트throw.bmp", 824, 78, 8, 1, true, RGB(255, 0, 255));

}
