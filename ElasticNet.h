#include <vector>

// Zusammenfassen von Node und City als Point oder so?
// struct Point{
// 	double x;
// 	double y;
// }


struct City{
	double x;
	double y;
};

struct Node{
	double x;
	double y;
};


class ElasticNet{

private:

	std::vector<City> cities;
	std::vector<Node> nodes;
	int numberNodes; // Nicht unbedingt notwendig
	int numberCities; // Nicht unbedingt notwendig

	// Eventuell zu Point zusammenfassen?
	double centerX;
	double centerY;

	float radius;
	float cvRatio;

public:


	// Constructor
	ElasticNet();
	ElasticNet(float, float);
	
	// Getter and Setter
	int getNumberCities();
	int getNumberNodes();
	double getCenterX();
	double getCenterY();
	float getRadius();
	float getCVRatio();
	std::vector<City> getCities();
	std::vector<Node> getNodes();

	void setRadius(float radius);
	void setCVRatio(float cvRatio);

	// Initialize 'cvRatio'*'numberCities' many nodes on a circle with radius 'radius'
	// Cirlce is centered around center of cities and nodes are split equidistant
	void initializeNet();
	void addCity(City city);
	void addCity(float xPos,float yPos);

};