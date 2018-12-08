#include "iterator.h"
#include "elasticnet.h"
#include "point.h"
#include <cmath>

#define limit 0.003

using namespace std;


//Default constructor
//Parameters are set like in 1 g)
//iterCounter counts number of iterations of apply()
Iterator::Iterator()
: iterMax(10000), iterCounter(0), etaTarget(0), initialTemperature(0.1),
  alpha(1.0), beta(1.0), net()
{
    //K(n = 0) is initialized
    this->currentTemperature = this->initialTemperature;
}

//Constructor with given ElasticNet
Iterator::Iterator(ElasticNet *net)
: iterMax(10000), iterCounter(0), etaTarget(0), initialTemperature(0.1), alpha(1.0), beta(1.0), net(net)
{
    this->currentTemperature = this->initialTemperature;
}

//Constructor with net and parameters
Iterator::Iterator(ElasticNet *net, double alpha, double beta, double temperature)
: iterMax(10000), etaTarget(0), initialTemperature(temperature), alpha(alpha), beta(beta), net(net)
{
    this->currentTemperature = this->initialTemperature;
}

//setter for K(0)
void Iterator::setInitialTemperature(double temp){
    this->initialTemperature = temp;
 }

//setter for K(n) := max{(0.99^(n/50))*K(0), 0.01}
void Iterator::setCurrentTemperature(){
    this->currentTemperature = max(pow(0.99,floor(iterCounter/50))*getInitialTemperature(), 0.01);
 }

//setter for remainig parameters
//---------------------------------
void Iterator::setIterMax(int iterMax){
    this->iterMax = iterMax;
 }

void Iterator::setAlpha(double alpha){
    this->alpha = alpha;
 }

void Iterator::setBeta(double beta){
    this->beta = beta;
 }

void Iterator::setEtaTarget(double eta){
    this->etaTarget = eta;
}

void Iterator::setNet(ElasticNet *net){
    this->net = net;
 }

void Iterator::setIterCounter(int iterCounter){
    this->iterCounter = iterCounter;
}
//---------------------------------


//getter
//---------------------------------
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

double Iterator::getEtaTarget(){
    return this->etaTarget;
}

ElasticNet* Iterator::getNet(){
    return this->net;
}
//---------------------------------


void Iterator::apply(){
     //calculates for each elastic net node (y(a)) its displacement (delta(y(a)))
     //and moves all y(a) by delta(y(a))

     this->setCurrentTemperature();
     //set K(n)
  
     double K = this->getCurrentTemperature();
     double T = this->getT();

     int numberNodes = this->net->getNumberNodes();

     Point * deltaY = new Point[numberNodes];
     //set up array to save all delta(y(a)) into

     vector<Point> nodes = this->net->getNodes();
     vector<Point> cities = this->net->getCities();
     //set up 2 vectors for nodes and cities to work with

     Point deltaYa = Point();
     //set up the point delta(y(a)) which will get calculated
     //in the upcoming for-loops and saved in deltaY

     int a_counter = 0;
     //because we are going to loop through the elements of
     //the vectors 'nodes' and 'cities, but want to save our
     //delta(y(a)) in an array, we need an int value indicating the index

     for(auto a = nodes.begin(); a != nodes.end(); a++){
     //loop through nodes
       
         double vIA = 0;
       
         for(auto i = cities.begin(); i != cities.end(); i++){
         //loop through cities to calculate the sum of (vIA*(x(i)-y(a)) for all i
           
             double denominator = 0; 
             //denominator of vIA

             for(auto b = nodes.begin(); b != nodes.end(); b++){
                 //iterate through nodes again to calc denominator of vIA
                 denominator += exp(-(pow((*i-*b).manhattanDistance(),2))/T);
                 //sum(for all b in nodes) e^((|x_i - y_b|^2)/T)
             }
             vIA = exp(-(pow((*i - *a).manhattanDistance(),2))/T)/denominator;
             //e^((|x_i - y_a|^2)/T) / sum(for all b in nodes) e^((|x_i - y_b|^2)/T)

             deltaYa += (*i - *a) * vIA;
             //vIA*(x(i) - y(a))

         }

         deltaYa *= getAlpha();
         //at this point the left part of the formula is calculated
       

         auto left = a-1;
         auto right = a+1;

         if (left < nodes.begin())
         //if a is the first node, its left neighbour is the last node
             left += numberNodes;

         if (right >= nodes.end())
         //if a is the last node, its right neighbour is the first node
             right -= numberNodes;

         deltaYa += (*left + *right - (*a * 2)) * getBeta()*K;
         //at this point the right part of the formula is calculated
       
         deltaY[a_counter] = deltaYa;
         //save delta(y(a)) in the array

         //reset
         deltaYa = Point();
         a_counter++;

     }

     a_counter = 0;

     for(int a = 0; a < net->getNumberNodes(); a++){
             //y(a) gets moved by delta(y(a))
             net->changeNet(a, deltaY[a]);
        }


 iterCounter += 1;

 }


double Iterator::calcEta(){
   //calculates and returns accuracy

   double dist = 0;
   double distMin = 100000;
   double distMax = -100000;

   vector<Point> nodes = this->net->getNodes();
   vector<Point> cities = this->net->getCities();

   for(auto i = cities.begin(); i != cities.end(); i++){
       for(auto a = nodes.begin(); a != nodes.end(); a++){
           dist = (*i - *a).euclidianDistance();
           distMin = min(dist, distMin);
       }
       distMax = max(distMin, distMax);
   }

   return distMax;

}

void Iterator::solve(){
   //calls apply until either iterMax iterations are executed
   //or accuracy etaTarget is accomplished
   this->iterCounter=0;

   while((calcEta() > etaTarget)&&(iterCounter < iterMax)){
       apply();
   }
}


