#ifndef ELASTICNET_H
#define ELASTICNET_H

// TODO: More setters?

#include <vector>
#include "point.h"
#include <QObject>

class ElasticNet : public QObject{
Q_OBJECT

private:

    // Vectors to store cities and nodes each as a coordinate pair (Point)
    std::vector<Point> cities;
    std::vector<Point> nodes;

    // Number of cities/nodes = size of respective vector 'cities'/'nodes'
    int numberNodes;
    int numberCities;

    // Coordinates of the center point among all cities in the 'cities' vector
    Point centerPoint;

    // Radius of the inital node circle and node per city ratio
    float radius;
    float cvRatio;

public slots:

    void clearNet();
    void setRadius(double radius);
    void setCVRatio(double cvRatio);

public:

    // Default constructor
    ElasticNet();
    // Constructor with given radius and cvRatio
    ElasticNet(float radius, float cvRatio);

    // Getter
    std::vector<Point> getCities();
    std::vector<Point> getNodes();
    int getNumberCities();
    int getNumberNodes();
    Point getCenter();
    float getRadius();
    float getCVRatio();

    // Initialize 'cvRatio'*'numberCities' many nodes on a circle with radius 'radius'
    // Cirlce is centered around center of cities (centerPoint) and nodes are split equidistant
    void initializeNet();

    // Add a city to the vector 'cities' using a Point or a pair of coordinates
    void addCity(Point city);
    void addCity(double xPos,double yPos);
    void changeNet(int index, Point delta);

};

#endif
