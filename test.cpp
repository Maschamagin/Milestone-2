#include "ElasticNet.h"
#include <iostream>

using namespace std;

int main(){

	ElasticNet net;


	net.addCity(1.0,1.0);
	net.addCity(2.0,2.0);
	net.addCity(3.0,3.0);


	cout << "Radius: " << net.getRadius() << endl;
	cout << "CV Ratio: " << net.getCVRatio() << endl;
	cout << "Number of Cities: " << net.getNumberCities() << endl;
	cout << "Center of Cities: " << net.getCenterX() << "," << net.getCenterY() << endl;

	vector<City> cities = net.getCities();
	vector<Node> nodes = net.getNodes();

	for(vector<City>::iterator i = cities.begin(); i != cities.end(); i++){
		cout << "City: (" << i->x << "," << i->y << ")" << endl;
	}

	cout << "Number of Nodes: " << net.getNumberNodes() << endl;

	for(vector<Node>::iterator i = nodes.begin(); i != nodes.end(); i++){
		cout << "Node: (" << i->x << "," << i->y << ")" << endl;
	}


	return 0;
}