#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;



class Point{
  int x,y;
public:
    Point();
    Point(int, int);
    void getVal(ifstream&);
    void setVal(int, int);
//    void moveOn(int x1, int y1);
    int diffX(Point a);
    int diffY(Point a);
    void print();
    int copyX();
    int copyY();
    int operator==(const Point&);
};

class Rect{
	Point hl,lr;
public:
	Rect();
	Rect(Point a, Point b);
//	~Rect();
	void setPoints(Point,Point);//задаем точки 
	void getPoints(ifstream&);
	void print(); // печать атрибутов
	//void moveToPoint(Point а); // пермещение прямунольника в точку а (центр)
	//void mirrorV(); // отображение прямоугольника относительно оси OY
	//void mirrorH(); // отображение прямоугольника относительно оси OX
	//void rotate90();// правый поворот на 90гр. относительно центра
	Point copyHl();
	Point copyLr();
	Point projX(Rect);
	Point projY(Rect);
	Rect* crossRect(Rect);//вернуть прямоугольник — пересечение с прямоугольником а
	Rect* unionRect(Rect);
	Rect* residRect(Rect);
	int operator==(Rect&);
};

Point proj(int, int, int, int);
int unique(Rect*, int, Rect);
