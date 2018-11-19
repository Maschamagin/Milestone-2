#include "ElasticNet.h"
#include <iostream>
#include "Point.h"

using namespace std;

int main(){

	ElasticNet net;

	net.addCity(1.0,1.0);
	net.addCity(2.0,2.0);
	net.addCity(5.0,5.0);

	vector<Point> test = net.getCities();
	for(vector<Point>::iterator i = test.begin(); i != test.end(); ++i){
		cout << i->x << " " << i->y << endl;
	}
	// net.addCity(3.0,3.0);

	cout << "Radius: " << net.getRadius() << endl;
	cout << "CV Ratio: " << net.getCVRatio() << endl;
	cout << "Number of Cities: " << net.getNumberCities() << endl;
	cout << "Center of Cities: " << net.getCenter().x << "," << net.getCenter().y << endl;


	return 0;
}