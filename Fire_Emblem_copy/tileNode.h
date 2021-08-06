#pragma once

#define TILESIZE 32

#define TILEX 20	//가로 타일 갯수
#define TILEY 20	//세로 타일 갯수

#define TILESIZEX TILESIZE * TILEX	//640 32 * 20
#define TILESIZEY TILESIZE * TILEY	//640 32 * 20

//타일셋 정의
#define SAMPLETILEX 20
#define SAMPLETILEY 9

//옛날엔 메모리 아낀다고 참 극한의 효율때문에 사용했는데
//요샌....... 기본이 16기가... 
//비트필드
#define ATTR_UNMOVE 0x00000001	//못가는 타일
#define ATTR_SWAMP	0x00000002	//밟으면 느려지는 타일
#define ATTR_POISON	0x00000004	//유 아 마 포이즌~
#define ATTR_FROZEN 0x00000008	//레릿꼬~



//오브젝트
enum OBJECT
{
	OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS,
	OBJ_FLAG1, OBJ_FLAG2,
	OBJ_TANK1, OBJ_TANK2,
	OBJ_NONE
};



//타일 정보 담은 구조체
struct tagTile
{
	TERRAIN		terrain;
	OBJECT		obj;
	RECT		rc;
	int			terrainFrameX;
	int			terrainFrameY;
	int			objFrameX;
	int			objFrameY;
};

//타일셋 정보 담을 구조체
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};

