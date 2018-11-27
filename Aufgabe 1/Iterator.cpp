#include "Iterator.h"
#include "ElasticNet.h"
#include "Point.h"
#include "math.h"
#include <iostream> //testing

using namespace std;

Iterator::Iterator()
: iterMax(10000), iterCounter(0), etaTarget(0), initialTemperature(0.1),
  alpha(1.0), beta(1.0), net()
{
    this->currentTemperature = this->initialTemperature;
}

Iterator::Iterator(ElasticNet *net)
: iterMax(10000), iterCounter(0), etaTarget(0), initialTemperature(0.1), alpha(1.0), beta(1.0), net(net)
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

void Iterator::setCurrentTemperature(){
    this->currentTemperature = max(pow(0.99,floor(iterCounter/50))*getInitialTemperature(), 0.01);
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

double Iterator::getT(){
    return 2*pow(getCurrentTemperature(),2);
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

     this->setCurrentTemperature();
     double K = this->getCurrentTemperature();
     double T = this->getT();

     int numberNodes = this->net->getNumberNodes();

     Point * deltaY = new Point[numberNodes];

     vector<Point> nodes = this->net->getNodes();
     vector<Point> cities = this->net->getCities();

     double vIA = 0;
     double denominator = 0; //used to calc vIA
     Point deltaYa = Point();

     int a_counter = 0;

     for(auto a = nodes.begin(); a != nodes.end(); a++){

         for(auto i = cities.begin(); i != cities.end(); i++){

             for(auto b = nodes.begin(); b != nodes.end(); b++){
                 //iterate through nodes again to calc denominator of vIA
                 //denominator += exp(-(pow((net->getCities()[i] - net->getNodes()[b]).magnitude(),2))/getT());
                 denominator += exp(-(pow((*a-*b).magnitude(),2))/getT());
                 //sum(b e nodes) e^((|x_i - y_b|^2)/T)
             }
             vIA = exp(-(pow((*i - *a).magnitude(),2))/getT())/denominator;
             //e^((|x_i - y_a|^2)/T) / sum(b e nodes) e^((|x_i - y_b|^2)/T)

             deltaYa += (*i - *a) * vIA;

         }

         deltaYa *= getAlpha();

         auto left = a-1;
         auto right = a+1;

         if (left < nodes.begin())
             left += numberNodes;

         if (right >= nodes.end())
             right -= numberNodes;

         deltaYa += (*left + *right - (*a * 2)) * getBeta()*getCurrentTemperature();
                                     //c++ doesnt support modulo op. with negative values

         deltaY[a_counter] = deltaYa;


         //reset
         denominator = 0;
         deltaYa = Point();

         a_counter++;

     }

     a_counter = 0;

     //at this point all deltaYa are calculated and saved in deltaY
     //in the next loop all yA get changed by deltaYa
     //cout << "delta Y : \n";
//     for(auto a = this->getNet()->getNodes().begin(); a != this->getNet()->getNodes().end(); a++){
//         *a += deltaY[a_counter];
//         cout << a->x << " " << a->y << endl;
//         a_counter++;
//         //net->changeNet(a_counter, deltaY[a_counter]);
//     }
         for(int a = 0; a < net->getNumberNodes(); a++){
             //net->getNodes()[a] += deltaY[a]; ging nicht
             net->changeNet(a, deltaY[a]);
        }


 iterCounter += 1;

 }

//void Iterator::apply(){

//    setCurrentTemperature();

//    int numberNodes = net->getNumberNodes();
//    //set up array to save all deltaY values
//    Point * deltaY = new Point[numberNodes];

//    double vIA = 0;
//    double denominator = 0; //used to calc vIA
//    Point deltaYa = Point();

//    for(int a = 0; a < numberNodes; a++){
//        //iterate through all elastic net nodes

//        for(int i = 0; i < net->getNumberCities(); i++){
//            //iterate through cities
//            for(int b = 0; b < numberNodes; b++){
//                //iterate through nodes again to calc denominator of vIA
//                denominator += exp(-(pow((net->getCities()[i] - net->getNodes()[b]).magnitude(),2))/getT());
//                //sum(b e nodes) e^((|x_i - y_b|^2)/T)
//            }
//            vIA = exp(-(pow((net->getCities()[i] - net->getNodes()[a]).magnitude(),2))/getT())/denominator;
//            //e^((|x_i - y_a|^2)/T) / sum(b e nodes) e^((|x_i - y_b|^2)/T)

//            deltaYa += (net->getCities()[i] - net->getNodes()[a]) * vIA;

//        }

//        deltaYa *= getAlpha();

//        deltaYa += (net->getNodes()[((a-1) + numberNodes)%numberNodes] + net->getNodes()[(a+1)%numberNodes] - (net->getNodes()[a]*2)) * getBeta()*getCurrentTemperature();
//                                    //c++ doesnt support modulo op. with negative values

//        deltaY[a] = deltaYa;


//        //reset
//        denominator = 0;
//        deltaYa = Point();


//    }

//    //at this point all deltaYa are calculated and saved in deltaY
//    //in the next loop all yA get changed by deltaYa
//    //cout << "delta Y : \n";
//    for(int a = 0; a < net->getNumberNodes(); a++){
//        //net->getNodes()[a] += deltaY[a]; ging nicht
//        net->changeNet(a, deltaY[a]);

//        cout << "(" << deltaY[a].x << " " << deltaY[a].y << "), ";
//        cout << "\n elastic net : \n";
//        cout << net->getNodes()[a].x << " " << net->getNodes()[a].y << endl ;
//    }

//    iterCounter += 1;

//}




void Iterator::solve(){

	for(auto iterator=0; iterator < this->iterMax; iterator++){

		// Implement if-statement to check precision etaTarget here
		this->apply();
	}
}

// void Iterator::test(){
// 	this->net->setRadius(2.0);
// }
