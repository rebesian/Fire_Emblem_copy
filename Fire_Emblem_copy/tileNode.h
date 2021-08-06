#pragma once

#define TILESIZE 32

#define TILEX 20	//���� Ÿ�� ����
#define TILEY 20	//���� Ÿ�� ����

#define TILESIZEX TILESIZE * TILEX	//640 32 * 20
#define TILESIZEY TILESIZE * TILEY	//640 32 * 20

//Ÿ�ϼ� ����
#define SAMPLETILEX 20
#define SAMPLETILEY 9

//������ �޸� �Ƴ��ٰ� �� ������ ȿ�������� ����ߴµ�
//���....... �⺻�� 16�Ⱑ... 
//��Ʈ�ʵ�
#define ATTR_UNMOVE 0x00000001	//������ Ÿ��
#define ATTR_SWAMP	0x00000002	//������ �������� Ÿ��
#define ATTR_POISON	0x00000004	//�� �� �� ������~
#define ATTR_FROZEN 0x00000008	//������~



//������Ʈ
enum OBJECT
{
	OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS,
	OBJ_FLAG1, OBJ_FLAG2,
	OBJ_TANK1, OBJ_TANK2,
	OBJ_NONE
};



//Ÿ�� ���� ���� ����ü
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

//Ÿ�ϼ� ���� ���� ����ü
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};

