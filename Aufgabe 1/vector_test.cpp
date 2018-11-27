#include "ElasticNet.h"
#include <iostream>
#include "Point.h"
#include "Iterator.h"

using namespace std;

int main(){

	ElasticNet testNet;

	testNet.addCity(1.0,1.0);
	testNet.addCity(2.0,2.0);

	vector<Point> cities = testNet.getCities();
	vector<Point> nodes = testNet.getNodes();

	int numberNodes = testNet.getNumberNodes();

	cout << "Cities: " << endl;
    for(auto i = cities.begin(); i != cities.end(); ++i){
        cout << i->x << "," << i->y << endl;
    }

    int counter = 1;

    cout << "Nodes: " << endl;
    for(auto j = nodes.begin(); j != nodes.end(); ++j){
        auto jPlus = j+1;
        auto jMinus = j-1;

        if (jPlus >= nodes.end())
        	jPlus -= numberNodes;

        cout << "--- Node " << counter << " ---" << endl;
        cout << counter << ":" << j->x << "," << j->y << endl;
        cout << counter-1 << ":" << jMinus->x << "," << jMinus->y << endl;
        cout << counter+1 << ":" << jPlus->x << "," << jPlus->y << endl;

        counter++;
    }

	return 0;
}