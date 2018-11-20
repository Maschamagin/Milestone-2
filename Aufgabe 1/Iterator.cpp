#include "Iterator.h"
#include "ElasticNet.h"
#include "Point.h"

Iterator::Iterator()
: iterMax(10000), etaTarget(0), initialTemperature(0.1),
  alpha(1.0), beta(1.0), net(NULL) 
{
	this->currentTemperature = this->initialTemperature;
}

Iterator::Iterator(ElasticNet *net)
: iterMax(10000), etaTarget(0), initialTemperature(0.1), alpha(1.0), beta(1.0), net(net)
{
	this->currentTemperature = this->initialTemperature;
}

Iterator::Iterator(ElasticNet *net, double alpha, double beta, double temperature)
: iterMax(10000), etaTarget(0), initialTemperature(temperature), alpha(alpha), beta(beta), net(net)
{
	this->currentTemperature = this->initialTemperature;
}

void Iterator::setInitialTemperature(double temp){
 	this->initialTemperature = temp;
 }

void Iterator::setIterMax(int iterMax){
 	this->iterMax = iterMax;
 }

void Iterator::setAlpha(double alpha){
	this->alpha = alpha;
 }

void Iterator::setBeta(double beta){
	this->beta = beta;
 }

void Iterator::setNet(ElasticNet *net){
	this->net = net;
 }

double Iterator::getInitialTemperature(){
 	return this->initialTemperature;
 }

double Iterator::getCurrentTemperature(){
	return this->currentTemperature;
}

double Iterator::getIterMax(){
	return this->iterMax;
}

double Iterator::getAlpha(){
	return this->alpha;
}

double Iterator::getBeta(){
	return this->beta;
}

ElasticNet* Iterator::getNet(){
	return this->net;
}

void Iterator::apply(){

	// Implement algorithm here
}

void Iterator::solve(){

	for(auto iterator=0; iterator < this->iterMax; iterator++){

		// Implement if-statement to check precision etaTarget here
		this->apply();
	}
}

// void Iterator::test(){
// 	this->net->setRadius(2.0);
// }