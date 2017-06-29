#include "rect.h"

int main() {
	ifstream fcin;	
	fcin.open("in.txt");


	Rect R[50];
	
	int n;
	fcin >> n;
	
	for(int i = 0; i < n; i++)
		R[i].getPoints(fcin);

	
	int endp = 0;
	int endc = n;
	int tend, newrc;
	Rect* tmp = NULL;
	tmp = new Rect;	
	int k = 0;
	
	while(endc != endp){
		cout << "итерация номер: " << k << endl;
		k++;
		tend = endc;
		newrc = 0;

		for(int i = 0; i < endc; i++) 
			for(int j = 0; j < endc; j++) {
//			cout << i << " " << j << endl;
				if((tmp = R[i].crossRect(R[j])) != NULL && unique(R, tend + newrc, *tmp)) {
					R[endc + newrc] = *tmp;
					tmp->print();
					cout << endl;
					newrc++;				
				}
				if((tmp = R[i].unionRect(R[j])) != NULL && unique(R, tend + newrc, *tmp)) {
					R[endc + newrc] = *tmp;
					tmp->print();
					cout << endl;
					newrc++;				
				}
				if((tmp = R[i].residRect(R[j])) != NULL && unique(R, tend + newrc, *tmp)) {
					R[endc + newrc] = *tmp;
					tmp->print();
					cout << endl;
					newrc++;				
				}		
			}
		endp = tend;
		endc = tend + newrc;	
	}
	
	cout << "видимых четырехугольников:" << endc << endl;		
	delete[] tmp;
	fcin.close();
	//fcout.close();
	return 0;
}
