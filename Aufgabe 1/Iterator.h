#ifndef ITERATOR_H
#define ITERATOR_H

#include "ElasticNet.h"

class Iterable{

public:
	virtual void apply() = 0;
	
};

class Iterator : public Iterable{

private:

	int iterMax;

	double etaTarget; // Precision target
	double currentTemperature; // K(n) parameter
	double initialTemperature; // K(0) parameter
 	double alpha; // Alpha parameter
	double beta; // Beta parameter

	// Wenn man in Iterator das Netz ändert, ist es global geändert
	ElasticNet *net; // Pointer auf das übergebene Netz

public:

	Iterator();
	Iterator(ElasticNet *net, double alpha, double beta, double temperature);
	Iterator(ElasticNet *net);

	void setInitialTemperature(double temp);
	void setIterMax(int iterMax);
	void setAlpha(double alpha);
	void setBeta(double beta);

	void setNet(ElasticNet *net);

	double getInitialTemperature();
	double getCurrentTemperature();
	double getIterMax();
	double getAlpha();
	double getBeta();

	// Mal schauen wie das funktioniert oder ob wir das Net public machen
	ElasticNet* getNet();

	void solve();
	void apply();

	// void test(); // Zum Testen ob Änderungen am Netz global sind
};

#endif