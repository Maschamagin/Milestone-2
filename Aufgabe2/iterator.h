#ifndef ITERATOR_H
#define ITERATOR_H

#include "elasticnet.h"
#include <QObject>

class Iterable{

public:
    virtual void apply() = 0;

};

class Iterator : public QObject, public Iterable{
Q_OBJECT

private:

    int iterMax;
    int iterCounter;
    double etaTarget; // Precision target
    double currentTemperature; // K(n) parameter
    double initialTemperature; // K(0) parameter
    double alpha; // Alpha parameter
    double beta; // Beta parameter
    ElasticNet *net; // Pointer on given net - changes are global!

public slots:

    void solve();
    void apply();
    void setInitialTemperature(double temp);
    void setCurrentTemperature();
    void setIterMax(int iterMax);
    void setAlpha(double alpha);
    void setBeta(double beta);
    void setEtaTarget(double eta);

public:

    Iterator();
    Iterator(ElasticNet *net, double alpha, double beta, double temperature);
    Iterator(ElasticNet *net);


    void setNet(ElasticNet *net);

    double getInitialTemperature();
    double getCurrentTemperature();
    double getT();
    double getIterMax();
    double getAlpha();
    double getBeta();
    double getEtaTarget();

    ElasticNet* getNet();

    double calcEta();
};

#endif
