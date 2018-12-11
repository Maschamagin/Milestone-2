//
// Created by user on 03.12.18.
//
#include <math.h>
#include <algorithm>
#include <cmath>
#include "Iterator.h"
#include "elastic_net.h"
#include <vector>
#define REDUCE

typedef::vector <tuple<int, int> > tuple_list;

Iterator::Iterator() {
    //defining attributes as asked for test cases
    iter_max = 10000, n = 0, eta = 0.005, initial_temperature = 0.1,
    alpha = 1.0, beta = 1.0;

    //K(n = 0) is initialized
    this->temperature_development = this->initial_temperature;
}

//set iteration counter
void Iterator::set_n(int n){
    this -> n = n;
}

// get the number of iterations
int Iterator::get_n(){
    return this-> n;
}

//set maximum of iteration until loop exit
void Iterator::set_iter_max(int iter_max){
    this-> iter_max = iter_max;
}

//get maximum of iterations until loop exit
int Iterator::get_iter_max() {
    return this -> iter_max;
}

//set scale alpha
void Iterator::set_alpha(double alpha){
    this -> alpha = alpha;
}

double Iterator::get_alpha() {
    return this -> alpha;
}

//set scale beta
void Iterator::set_beta(double beta){
    this -> beta = beta;
}

double Iterator::get_beta() {
    return this -> beta;
}

//set K(0)
void Iterator::set_initial_temperature(double temp){
    this->initial_temperature = temp;
}

double Iterator::get_initial_temperature(){
    return this -> initial_temperature;
}

//set K(n)
void Iterator::set_temperature_development(){
    this -> temperature_development = max(pow(0.99,floor(n/50))*get_initial_temperature(), 0.01);
};

double Iterator::get_temperature_development() {
    return this -> temperature_development;
}

//get T(n)
double Iterator::get_Tn(){
    return 2 * pow(get_temperature_development(), 2.0);
}

//get precision of expanding elastic net
double Iterator::get_eta(){
    return this -> eta;
}


//calculate Manhattan norm of a 2D-vector
double Iterator::manhattan_distance(tuple<int, int> coordinates){
    double coordinate_x = get<0>(coordinates);
    double coordinate_y = get<1>(coordinates);
    double manhattan_dist = (abs(coordinate_x) + abs(coordinate_y));
    return manhattan_dist;
}

//the coordinates are normed for test cases
double Iterator::euclidian_distance(tuple<int, int> coordinates){
    double coordinate_x = get<0>(coordinates);
    double coordinate_y = get<1>(coordinates);
    double euclidian_dist = sqrt((pow(abs(coordinate_x), 2)) + pow((abs(coordinate_y)), 2));
    return euclidian_dist;

}

void Iterator::apply() {
    tuple_list nodes = EN->getposition_of_circle_node();
    tuple_list cities = EN->getpositioncity();
    double K_n = get_temperature_development();
    double T_n = get_Tn();
    double sum_ny_i_a = 0;
    double delta_y0;
    double delta_y1;


    //iteration over all nodes:
    for (int a = 0; a < nodes.size(); a++) {

        //iteration over all cities:
        for (int i = 0; i < cities.size(); i++) {
            double sum_denominator = 0;

            //and once more over all the nodes to calculate the denominator in ny(i, a):
            for (int b = 0; b < nodes.size(); b++) {
                sum_denominator += exp(-(pow(manhattan_distance(cities[i]) - manhattan_distance(nodes[b]), 2) / T_n));
            }
            //calculate ny(i, a)
            double ny_i_a;
            ny_i_a = exp(-(pow(manhattan_distance(cities[i]) - manhattan_distance(nodes[a]), 2) / T_n)) /
                     sum_denominator;
            //calculate the sum of ny_i_y multiplied by the distance of city and node
            sum_ny_i_a += (ny_i_a * manhattan_distance(cities[i]) - manhattan_distance(nodes[a]));
        }
        int next_node_higher;
        int next_node_lower;

        //next to the node on the highest end is the first node of the vector
        if (a == nodes.size()) {
            next_node_higher = 0;
        } else {
            next_node_higher = a + 1;
        }
        //next to the node with index = 0 is the one on the highest end of the vector
        if (a == 0) {
            next_node_lower = nodes.size();
        } else {
            next_node_lower = a - 1;
        }

        delta_y0 = get_alpha() * sum_ny_i_a + get_beta() * K_n * (get<0>(nodes[(next_node_lower) % nodes.size()]) -
                                                                  (2 * get<0>(nodes[a])) +
                                                                  (get<0>(nodes[(next_node_higher) % nodes.size()])));
        delta_y1 = get_alpha() * sum_ny_i_a + get_beta() * K_n * (get<1>(nodes[(next_node_lower) % nodes.size()]) -
                                                                  (2 * get<1>(nodes[a])) +
                                                                  (get<1>(nodes[(next_node_higher) % nodes.size()])));

        get<0>(nodes[a]) = get<0>(nodes[a]) + delta_y0;
        get<1>(nodes[a]) = get<1>(nodes[a]) + delta_y1;
    }
    n++;
    cout << n << endl;
    EN->update_nodes(nodes);
    for (tuple_list::const_iterator g = nodes.begin(); g != nodes.end(); g++) {
        // prints positions of new nodes for bug fixing purpose
        cout << get<0>(*g) << " " << get<1>(*g) << endl;
    }

}

//calculate accuracy: a compare value it installed to compare ist to every euclidian distance of noodes and cities
double Iterator::calculate_accuracy() {
    tuple_list nodes = EN->getposition_of_circle_node();
    tuple_list cities = EN->getpositioncity();
    double distance;
    double min_compare = 10000.0;
    double max_compare = -10000.0;
        for(int i = 0; i < cities.size(); i++){
        for(int a = 0; a < nodes.size(); a++){
            distance = euclidian_distance(cities[i]) - euclidian_distance(nodes[a]);
            min_compare = min(min_compare, distance);

#ifdef REDUCE
            if(distance<=eta){
                nodes.erase(nodes.begin() + a);
            }
#endif
        }
        max_compare = max(min_compare, max_compare);
    }
    //returns the greatest deviation of cities to nodes
    return abs(max_compare);

}

tuple_list Iterator::solve(){
    this->n = 0;

    //execute member function apply until it either reaches a set accuracy(eta) or a maximum of iterations
    while((calculate_accuracy() > eta)&&(n < iter_max)){
        apply();
    }
    //returns a vector with all coordinates of the nodes after executing "apply"

    return EN->getposition_of_circle_node();

}
