#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;


struct station {
	int id;
	int loadFactor;
	int x;
	int y;
};

vector <station> radar;


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

void computeLoadFactor() {
	for (int i = 0; i < radar.size(); i++) {
		for (int j = 0; j < radar.size(); j++) {
			int loadCount = 0;
			if ((radar.at(i).x >= radar.at(j).x) && (radar.at(i).y >= radar.at(j).y)) {
				radar.at(i).loadFactor++;
			}
		}
		radar.at(i).loadFactor--;
	}
}

bool stationCompare(const station& lhs, const station& rhs) {
	return lhs.id < rhs.id;
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
	computeLoadFactor();
	sort(radar.begin(), radar.end(), stationCompare);
	printStations();

	return 0;
}
