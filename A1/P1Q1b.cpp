#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <math.h>

using namespace std;

struct station {
	int id;
	int loadFactor;
	int x;
	int y;
};

vector <station> radar;
vector <station*> xsortedp;
vector <station*> ysortedp;

void readInput(int numStations) {
	while (numStations > 0) {
		int inputID;
		int inputX;
		int inputY;
		string input = "";
		getline (cin, input);
		stringstream sstream2(input);
		sstream2 >> inputID;
		sstream2 >> inputX;
		sstream2 >> inputY;
		radar.push_back(station());
		radar[radar.size()-1].id = inputID;
		radar[radar.size()-1].x = inputX;
		radar[radar.size()-1].y = inputY;
		radar[radar.size()-1].loadFactor = 0;
		numStations--;
	}
}

bool stationCompare(const station& lhs, const station& rhs) {
	return lhs.id < rhs.id;
}


bool xCompare(const station* lhs, const station* rhs) {
	if (lhs->x == rhs->x) {
		return lhs->y < rhs->y;
	} else { 
		return lhs->x < rhs->x;
	}
}

bool yCompare(const station* lhs, const station* rhs) {
	if (lhs->y == rhs->y) {
		return lhs->x < rhs->x;
	} else {
		return lhs->y < rhs->y;
	}
	
}

void combine(vector <station*> x1, vector <station*> y1, vector <station*> x2, vector <station*> y2) {
	int j = y1.size();
	int i = y2.size();

	while (i > 0 && j > 0) {
		if (y1.at(j-1)->y <= y2.at(i-1)->y) {
			y2.at(i-1)->loadFactor += j;
			i--;
		} else {
			j--; 
		}
	}
}

void computeLoadFactor(vector <station*> X, vector <station*> Y) {
if (X.size() > 1) {
		vector <station*> x1;
		vector <station*> x2;	
		vector <station*> y1;
		vector <station*> y2;

		int numLeft = 0;
		int midIndex = 0;
		int xMidValue = 0;

		midIndex = X.size() / 2;
		xMidValue = (X.at((X.size() / 2) -1))->x;


		for (int i = 0; i < X.size(); i++) {
			if (i < midIndex) {
				x1.push_back(X.at(i));
				numLeft++;
			} else {
				x2.push_back(X.at(i));
			}
		}
		for (int i = 0; i < Y.size(); i++) {
			if (Y.at(i)->x <= xMidValue && numLeft > 0) { 
				y1.push_back(Y.at(i));
				numLeft--;
			} else {
				y2.push_back(Y.at(i));
			}
		}
		computeLoadFactor(x1, y1);
		computeLoadFactor(x2, y2);

		combine (x1, y1, x2, y2);
	}
}

void printStations () {
	for (int i = 0; i < radar.size(); i++) {
		cout << radar.at(i).id << " " << radar.at(i).loadFactor << endl;
	}
}

int main () {
	string input = "";
	int numStations;
	getline (cin,input);
	stringstream sstream1 (input);
	sstream1 >> numStations;
	readInput(numStations);
	sort(radar.begin(), radar.end(), stationCompare);

	for (int i = 0; i < radar.size(); i++) {
		xsortedp.push_back(&radar.at(i));
	}
	for (int i = 0; i < radar.size(); i++) {
		ysortedp.push_back(&radar.at(i));
	}

	sort (xsortedp.begin(), xsortedp.end(), xCompare);
	sort (ysortedp.begin(), ysortedp.end(), yCompare);

	computeLoadFactor(xsortedp, ysortedp);
	 
	printStations();
	return 0;
}
