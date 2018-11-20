#include "ElasticNet.h"
#include <iostream>
#include "Point.h"
#include "Iterator.h"

using namespace std;

int main(){

    ElasticNet net;

    net.addCity(1.0,1.0);
    net.addCity(2.0,2.0);
    net.addCity(5.0,5.0);
    net.addCity(4.0,4.0);

    cout << "Cities: " << endl;
    vector<Point> test = net.getCities();
    
    for(vector<Point>::iterator i = test.begin(); i != test.end(); ++i){
        cout << i->x << " " << i->y << endl;
    }

    cout << "Nodes: " << endl;
    vector<Point> testnodes = net.getNodes();
    for(vector<Point>::iterator j = testnodes.begin(); j != testnodes.end(); ++j){
       cout << j->x << " " << j->y << endl;
    }

    cout << "Radius: " << net.getRadius() << endl;
    cout << "CV Ratio: " << net.getCVRatio() << endl;
    cout << "Number of Cities: " << net.getNumberCities() << endl;
    cout << "Number of Nodes: " << net.getNumberNodes() << endl;
    cout << "Center of Cities: " << net.getCenter().x << "," << net.getCenter().y << endl;
    cout << "Magnitude: " << net.getCenter().magnitude() << endl;

    Iterator ittest(&net);

    return 0;
}
