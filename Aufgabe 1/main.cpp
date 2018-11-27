#include "ElasticNet.h"
#include <iostream>
#include "Point.h"
#include "Iterator.h"

using namespace std;

int main(){

    ElasticNet net;

    net.addCity(0.23,0.04);
    net.addCity(0.57,0.38);
    net.addCity(0.89,0.01);
    //net.addCity(4.0, 3.0);

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

    cout << "_____________________apply_________________" << endl;


    Iterator ittest(&net);

    for(int i = 0; i < 10; i++){
        ittest.apply();
        cout << "_____________________\n";
    }

    cout << "Nodes: " << endl;
    vector<Point> testnodes2 = net.getNodes();
    for(vector<Point>::iterator j = testnodes2.begin(); j != testnodes2.end(); ++j){
        cout << j->x << " " << j->y << endl;
    }



    return 0;
}
