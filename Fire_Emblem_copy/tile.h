#pragma once
#include "gameNode.h"
#include "tileSet.h"


class tile : public gameNode
{
private:
	int _idX;
	int _idY;
	
	POINT _center;
	RECT _rc;
	//F = G + H 
	//F == �� �Ÿ� ��� (TotalCost)
	//G == ���������κ��� ���� ������ ��κ��(CostFromStart)
	//H == ������κ��� ���������� ��κ��(CostToGoal)

	float _totalCost;
	float _costFromStart;
	float _costToGoal;

	bool _isOpen; // �����ִ� Ÿ������ �˾ƺ���

	tileSet* _map;
	tile* _parentNode; //���� ���� Ÿ�� 
	
	image* 
	
	string _attribute;
	int _parentNodenumber;
	
public:
	tile();
	~tile();

	HRESULT init(int idX, int idY);
	void release();
	void update();
	void render();

	int getIdX() { return _idX; }
	int getIdY() { return _idY; }
	RECT getRect() { return _rc; }
	float getTotalCost() { return _totalCost; }
	float getFromCost() { return _costFromStart; }
	float getToGoal() { return _costToGoal; }
	POINT getCenter() { return _center; }
	string getAttribute() { return _attribute; }
	tile* getParentNode() { return _parentNode; }
	bool getIsOpen() { return _isOpen; }
	int getparentNumber() { return _parentNodenumber; }

	void setIdX(int idx) { _idX = idx; }
	void setIdY(int idy) { _idY = idy; }
	void setRect(RECT rc) { _rc = rc; }
	void setCetner(POINT center) { _center = center; }
	void setTotalCost(float totalCost) { _totalCost = totalCost; }
	void setCostFromStart(float costFromStart) {  _costFromStart = costFromStart; }
	void setCostToGoal(float costToGoal) { _costToGoal = costToGoal; }
	void setParentNode(tile* t) { _parentNode = t; }
	void setIsOpen(bool isOpen) { _isOpen = isOpen; }
	void setAttribute(string attribute) { _attribute = attribute; }
	void setparentNumber(int number) { _parentNodenumber = number; }
	void setLinkRandomMap(tileSet* map) { _map = map; }

	void setColor(COLORREF color)
	{
		DeleteObject(_brush);
		_color = color;
		_brush = CreateSolidBrush(_color);
	}

};

