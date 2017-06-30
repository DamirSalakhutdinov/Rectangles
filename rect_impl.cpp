#include "rect.h"


Point::Point() {
	x = 0;
	y = 0;
};

Point::Point(int x1, int y1) {
	x = x1;
	y = y1;
};

void Point::setVal(int x1, int y1) {
	x = x1;
	y = y1;

};

void Point::getVal(ifstream& fcin) {
	fcin >> x >> y;
};

void Point::getVal() {
	cin >> x >> y;
};

void Point::print() {
	cout << "(" << x << ';' << y << ")" << "\n";
};

int Point::diffX(Point a) {
	return a.x - x;
};

int Point::diffY(Point a) {
	return a.y - y;
};

Rect::Rect() {
	Point zero(0, 0);
	hl = zero;
	lr = zero;
};

Rect::Rect(Point a, Point b) {
	this->setPoints(a, b);
};

void Rect::getPoints(ifstream& fcin) {
	cout << "введите hl:" << "\n";
	hl.getVal(fcin);
	cout << "введите lr:" << "\n";
	lr.getVal(fcin);

	if(hl.diffY(lr) > 0 || hl.diffX(lr) < 0) {
		cout << "invalid rect definition" << "\n";
		exit(1);	
	}
};

void Rect::getPoints() {
	cout << "введите hl:" << "\n";
	hl.getVal();
	cout << "введите lr:" << "\n";
	lr.getVal();

	if(hl.diffY(lr) > 0 || hl.diffX(lr) < 0) {
		cout << "invalid rect definition" << "\n";
		exit(1);	
	}
};

void Rect::setPoints(Point a, Point b) {
	hl = a;
	lr = b;
	if(b.diffY(a) < 0 || a.diffX(b) < 0) {
		cout << "invalid rect definition" << "\n";
		exit(1);	
	}
};

void Rect::print() {
	hl.print();
	lr.print();
};

int Point::copyX() {
	return x;
};

int Point::copyY() {
	return y;
};

Point Rect::copyHl() {
	return hl;
};

Point Rect::copyLr() {
	return lr;
};


Point proj(int a1, int a2, int b1, int b2) {
	Point p(0, -1);	

	if(b1 < a1 && a1 <= b2 && b2 < a2)
		p.setVal(a1, b2);
	else if(a1 < b1 && b1 <= a2 && b2 > a2)
		p.setVal(b1, a2);
	else if(a1 <= b1 && b2 <= a2)
		p.setVal(b1, b2);
	else if(b1 <= a1 && a2 <= b2)
		p.setVal(a1, a2);

	return p;	
};

Point Rect::projX(Rect a) {
	int a1, a2, b1, b2;
	a1 = (this->copyHl()).copyX();
	b1 = (a.copyHl()).copyX();
	a2 = (this->copyLr()).copyX();
	b2 = (a.copyLr()).copyX();

	return proj(a1, a2, b1, b2);
};

Point Rect::projY(Rect a) {
	int a1, a2, b1, b2;
	a1 = this->copyLr().copyY();
	b1 = a.copyLr().copyY();
	a2 = this->copyHl().copyY();
	b2 = a.copyHl().copyY();

	return proj(a1, a2, b1, b2);
};



Rect* Rect::crossRect(Rect a){
	Point px, py, bad(0, -1);
	px = this->projX(a);
	py = this->projY(a);

	if(px == bad || py == bad || 
	px.copyX() == px.copyY() || 
	py.copyX() == py.copyY()) {
//		cout << "не пересеклось\n";		
		return NULL;
	}
	else {
		Rect *tmp;
		tmp = new Rect();  
		Point nhl(px.copyX(), py.copyY()), nlr(px.copyY(), py.copyX()); 
		tmp->setPoints(nhl, nlr);
		return tmp;	
	}  
};

Rect* Rect::unionRect(Rect a){
	Point px, py, bad(0, -1);
	px = this->projX(a);
	py = this->projY(a);
	Point ax, ay, thisx, thisy;

	ax.setVal(a.hl.copyX(), a.lr.copyX());
	ay.setVal(a.lr.copyY(), a.hl.copyY());
	thisx.setVal(hl.copyX(), lr.copyX());
	thisy.setVal(lr.copyY(), hl.copyY());
	
	
	if(ax == thisx && !(py == bad));
	else if(ay == thisy && !(px == bad));
	else {
//		cout << "не объединилось\n";
		return NULL;
	}

	Rect *res;
	res = new Rect();  
	Point nhl, nlr;

	if(a.copyHl().copyX() <= this->copyHl().copyX() && a.copyHl().copyY() >= this->copyHl().copyY())
		nhl = a.copyHl();
	else
		nhl = this->copyHl();

	if(a.copyLr().copyX() >= this->copyLr().copyX() && a.copyLr().copyY() <= this->copyLr().copyY())
		nlr = a.copyLr();
	else
		nlr = this->copyLr();
	

	
	res->setPoints(nhl, nlr);

 	return res;

};

Rect* Rect::residRect(Rect a) {
	Rect *res;
	res = new Rect();  
	Point nhl(0, 0), nlr(0, 0);
	if(hl == a.hl)
		if(a.lr.copyX() == lr.copyX() && hl.copyY() > a.lr.copyY() && a.lr.copyY() > lr.copyY()) {
			nhl.setVal(hl.copyX(), a.lr.copyY());
			nlr = lr;	
		}
		else if(a.lr.copyY() == lr.copyY() && hl.copyX() < a.lr.copyX() && a.lr.copyX() < lr.copyX()) {
			nhl.setVal(a.lr.copyX(), hl.copyY());
			nlr = lr;			
		}
	if(lr == a.lr)
		if(a.hl.copyX() == hl.copyX() && hl.copyY() > a.hl.copyY() && a.hl.copyY() > lr.copyY()) {
			nhl = hl;
			nlr.setVal(lr.copyX(), a.hl.copyY());		
		}
		else if(a.hl.copyY() == hl.copyY() && hl.copyX() < a.hl.copyX() && a.hl.copyX() < lr.copyX()) {
			nhl = hl;
			nlr.setVal(a.hl.copyX(), lr.copyY());
		}
	
	
	Point px, py, bad(0, -1);
	px = this->projX(a);
	py = this->projY(a);
	Point ax, ay, thisx, thisy;

	ax.setVal(a.hl.copyX(), a.lr.copyX());
	ay.setVal(a.lr.copyY(), a.hl.copyY());
	thisx.setVal(hl.copyX(), lr.copyX());
	thisy.setVal(lr.copyY(), hl.copyY());
	
	
	if(ax == thisx && py == ay && a.hl.copyY() < hl.copyY() && a.lr.copyY() > lr.copyY()) {
		nhl = hl;	
		nlr.setVal(a.lr.copyX(), a.hl.copyY());
	}
	else if(ay == thisy && px == ax && hl.copyX() < a.hl.copyX() && a.lr.copyX() < lr.copyX()) {
		nhl.setVal(a.lr.copyX(), a.hl.copyY());	
		nlr = lr;
	}

	if(nhl == nlr) {
		//cout << "не вычлось\n";
		return NULL;
	} else {
		res->setPoints(nhl, nlr);
		return res;
	}
};

int unique(Rect* mas, int n, Rect a){
	for(int i = 0; i < n; i++)
		if(mas[i] == a)
			return 0;
	return 1;		
};

int Point::operator==(const Point& a){
	if(this->diffX(a) == 0 && this->diffY(a) == 0)
		return 1;
	else 
		return 0;
};

int Rect::operator==(Rect& a){
	if(this->copyHl() == a.copyHl() && this->copyLr() == a.copyLr())
		return 1;
	else 
		return 0;
};

