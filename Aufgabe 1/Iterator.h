#ifndef ITERATOR_H
#define ITERATOR_H

#include "elasticnet.h"

class Iterable{

public:
    virtual void apply() = 0;

};

class Iterator : public Iterable{

private:

    int iterMax;
    int iterCounter;
    double etaTarget; // Precision target
    double currentTemperature; // K(n) parameter
    double initialTemperature; // K(0) parameter
    double alpha; // Alpha parameter
    double beta; // Beta parameter
    ElasticNet *net; // Pointer on given net - changes are global!

public:



    Iterator();
    Iterator(ElasticNet *net, double alpha, double beta, double temperature);
    Iterator(ElasticNet *net);

    void setInitialTemperature(double temp);
    void setCurrentTemperature();
    void setIterMax(int iterMax);
    void setAlpha(double alpha);
    void setBeta(double beta);

    void setNet(ElasticNet *net);

    double getInitialTemperature();
    double getCurrentTemperature();
    double getT();
    double getIterMax();
    double getAlpha();
    double getBeta();

    ElasticNet* getNet();

    double calcEta();

    void solve();
    void apply();
};

#endif
