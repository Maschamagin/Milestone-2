#include <iostream>
#include <math.h>
#include <vector>
#include "ElasticNet.h"

using namespace std;

ElasticNet::ElasticNet(){
	this->radius = 0.1;
	this->cvRatio = 2.5;
	this->numberCities = this->numberNodes = 0;
}

// Constructor initializes dimension of elastic net
ElasticNet::ElasticNet(float radius, float cvRatio){
	this->radius = radius;
	this->cvRatio = cvRatio;
	this->numberCities = this->numberNodes = 0;
}

// ---
// Getter and Setter
// ---
int ElasticNet::getNumberCities(){
	return this->numberCities;
}

int ElasticNet::getNumberNodes(){
	return this->numberNodes;
}

double ElasticNet::getCenterX(){
	return this->centerX;
}

double ElasticNet::getCenterY(){
	return this->centerY;
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


vector<City> ElasticNet::getCities(){
	return this->cities;
}


vector<Node> ElasticNet::getNodes(){
	return this->nodes;
}

// ---
// Net initialitation and addition of cities
// ---
void ElasticNet::initializeNet(){
	this->numberNodes = int(this->cvRatio*this->numberCities);
	this->nodes.resize(this->numberNodes);

	// Calculate position of each node in nodes
	// Nodes lay equidistant on circle with radius 'radius' 
	for(int i=0;i<this->numberNodes;i++){

        double x = this->radius * cos(2 * M_PI * i/this->numberNodes);
        double y = this->radius * sin(2 * M_PI * i/this->numberNodes);

        // Move point to center of Cities
        x += this->getCenterX();
        y += this->getCenterY();

        this->nodes[i].x = x;
        this->nodes[i].y = y;
    }
}


void ElasticNet::addCity(City city){
	this->cities.push_back(city);
	this->numberCities++; 

	// Recalculate center of all cities
	double SumX = 0, SumY = 0;

	for(vector<City>::iterator i = this->cities.begin(); i != this->cities.end(); i++){
		SumX += i->x;
		SumY += i->y;
	}

	this->centerX = SumX/this->numberCities;
	this->centerY = SumY/this->numberCities;

	// Initialize net and calculate initial node position
	this->initializeNet();
}


void ElasticNet::addCity(float xPos,float yPos){
	City newCity = {xPos, yPos};
	this->addCity(newCity);
}


