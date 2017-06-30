#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;



class Point{
  int x,y;
public:
    Point();
    Point(int, int);
    void getVal();
    void getVal(ifstream&);
    void setVal(int, int);
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
	void setPoints(Point,Point);	//задаем точки 
	void getPoints(ifstream&);
	void getPoints();
	void print(); // печать атрибутов
	Point copyHl();
	Point copyLr();
	Point projX(Rect);
	Point projY(Rect);

	Rect* crossRect(Rect);	//перечесение
	Rect* unionRect(Rect);	//объединение
	Rect* residRect(Rect);	//разность
	int operator==(Rect&);
};

Point proj(int, int, int, int);
int unique(Rect*, int, Rect);
