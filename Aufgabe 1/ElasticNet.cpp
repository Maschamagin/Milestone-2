#include <iostream>
#include <math.h>
#include <vector>
#include "ElasticNet.h"

using namespace std;

// Default Constructor
// radius = 0.1, cvRatio = 2.5
ElasticNet::ElasticNet()
: radius(0.1), cvRatio(2.5), numberCities(0), numberNodes(0),
  centerPoint(Point(0,0)) , cities(vector<Point>()), nodes(vector<Point>())
  {}

// Constructor with Radius and CVRatio given as parameters
ElasticNet::ElasticNet(float radius, float cvRatio)
: radius(radius), cvRatio(cvRatio), numberCities(0), numberNodes(0),
  centerPoint(Point(0,0)) , cities(vector<Point>()), nodes(vector<Point>())
  {}

// ---
// Getter and Setter
// ---
int ElasticNet::getNumberCities(){
    return this->numberCities;
}

int ElasticNet::getNumberNodes(){
    return this->numberNodes;
}

Point ElasticNet::getCenter(){
    return this->centerPoint;
}

float ElasticNet::getRadius(){
    return this->radius;
}

void ElasticNet::setRadius(float radius){
    this->radius=radius;
}

float ElasticNet::getCVRatio(){
    return this->cvRatio;
}

void ElasticNet::setCVRatio(float cvRatio){
    this->cvRatio=cvRatio;
}

vector<Point> ElasticNet::getCities(){
    return this->cities;
}

vector<Point> ElasticNet::getNodes(){
    return this->nodes;
}

void ElasticNet:: changeNet(int index, Point delta){
    this->nodes[index] += delta;
}



// ---
// Net initialitation and addition of cities
// ---
void ElasticNet::initializeNet(){
    // Calculate number of nodes and resize vector
    this->numberNodes = int(this->cvRatio * this->numberCities);
    this->nodes.resize(this->numberNodes);

    // Calculate initial position of each node
    // Nodes lay equidistant on circle with radius 'radius'
    for(int i=0;i < this->numberNodes;i++){

        // Each position can be calculated on the unit cirlce and scaled by the radius
        double x = this->radius * cos(2 * M_PI * i/this->numberNodes);
        double y = this->radius * sin(2 * M_PI * i/this->numberNodes);

        // The circle center is then moved to the centerPoint of all cities
        this->nodes[i] = Point(x,y);
        this->nodes[i] += this->centerPoint;

    }
}


void ElasticNet::addCity(Point city){
    // Recalculate the centerPoint of all cities
    this->centerPoint *= this->numberCities;
    this->centerPoint += city;
    this->numberCities++;
    this->centerPoint /= this->numberCities;

    // Add new city to vector
    this->cities.push_back(city);

    // Initialize net and calculate initial node position
    this->initializeNet();
}


void ElasticNet::addCity(float xPos,float yPos){
    // Create Point from coordinates and use addCity(Point)
    Point city = Point(xPos, yPos);
    this->addCity(city);
}
