#ifndef ITERATOR_H
#define ITERATOR_H

#include "elasticnet.h"
#include <QObject>

// Virtual class to be inherited from
class Iterable{

public:
    virtual void apply() = 0;

};

// Implements the apply-function to solve the net
class Iterator : public QObject, public Iterable{
Q_OBJECT

private:

    // Properties of the iterator
    int iterMax; // Maximum of iterations
    int iterCounter; // Current iteration counter (n)
    double etaTarget; // Precision target
    double currentTemperature; // K(n) parameter
    double initialTemperature; // K(0) parameter
    double alpha; // Alpha parameter
    double beta; // Beta parameter
    ElasticNet *net; // Pointer on given net - changes are global!

public slots:

    // Solves the net at once, using the "apply" function
    void solve();
    // Applies one iteration step to the net
    void apply();
    // Set the initial temperature K(0)
    void setInitialTemperature(double temp);
    // Set the maximum of iterations
    void setIterMax(int iterMax);
    // Set the alpha parameter
    void setAlpha(double alpha);
    // Set the beta parameter
    void setBeta(double beta);
    // Set the precision target
    void setEtaTarget(double eta);

public:

    // Constructors
    Iterator();
    Iterator(ElasticNet *net, double alpha, double beta, double temperature);
    Iterator(ElasticNet *net);

    // Set current iteration n (used to reset the iterator)
    void setIterCounter(int iterCounter);
    // Calculate and set the current temperature K(n)
    void setCurrentTemperature();
    void setNet(ElasticNet *net);

    // Getters for parameters
    double getInitialTemperature();
    double getCurrentTemperature();
    double getT();
    double getIterMax();
    double getAlpha();
    double getBeta();
    double getEtaTarget();

    // Return the net
    ElasticNet* getNet();

    // Calculate the current precision
    double calcEta();
};

#endif
