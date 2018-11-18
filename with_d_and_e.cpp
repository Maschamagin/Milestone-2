//Autor: Julian Gegner
//Milestone 1, Aufgabe 1 a, b, c umgesetzt
//Variablen der Klasse Elastic_net so gesetzt, wie in Aufgabe 1g
//Bei cv ratio geschummelt (siehe Zeile 82)


#include <iostream>
#include <math.h>

using namespace std;


struct city_node{
    float x_coord;
    float y_coord;
    //bool visited;
}city;

struct elastic_net_node{
    float x_coord;
    float y_coord;
}node;

class Elastic_net{

private:
    int array_size = 0;




    float center_x = 0;
    float center_y = 0;
    //needs to be x/y

    float rk = 0.1;
    //radius of elastic net circle

    float cv = 2.5;
    //ratio of #cities and #elastic_net_nodes
    //float cv_save = 0;


public:

    int index_cities = 0;
    city_node * cities = new city_node[array_size];
    city_node * buffer_array = new city_node[array_size];
    elastic_net_node * elastic_net_points = new elastic_net_node[array_size];
    int index_elastic_points = 0;
//    void change_position(int index, float delta_x, float delta_y){
//        elastic_net_points[index].x_coord += delta_x;
//        elastic_net_points[index].y_coord += delta_y;
//    }

    void calculate_positions(){
        //calculation done here is a rotation by the defined angle
        float angle = M_PI/index_elastic_points;
        float alpha = 0;
        elastic_net_points[0].x_coord = get_center_x() + rk*cos(alpha);
        elastic_net_points[0].y_coord = get_center_y() + rk*sin(alpha);
        for(int i = 1; i < index_elastic_points; i++){
            elastic_net_points[i].x_coord = get_center_x() + rk*cos(alpha+angle);
            elastic_net_points[i].y_coord = get_center_y() + rk*sin(alpha+angle);
            alpha += angle;
        }

    }

    void calculate_center(){
        //calculates the x y coords of the cities center
        //klappt
        float x = 0;
        float y = 0;
        for(int i = 0; i < index_cities; i++){
            x += cities[i].x_coord;
            y += cities[i].y_coord;
        }
        x /= index_cities;
        y /= index_cities;
        set_center_x(x);
        set_center_y(y);
    }

    void generate(){
        //adds new nodes to the elastic net and calculates their positions
        //gets called everytime a new city is added
        int j = round(cv); //baaaaaddddd
        elastic_net_node * elastic_net_points = new elastic_net_node[array_size*j];
        for(int i=0; i<j; i++){
            elastic_net_points[index_elastic_points] = node;
            index_elastic_points ++;
        }

        calculate_positions();


    }

    void add(float x,float y){
        //adds a city with coords x and y
        buffer_array = new city_node[array_size];
        buffer_array = cities;
        array_size ++;
        cities = new city_node[array_size];
        for(int i = 0; i < index_cities; i ++){
            cities[i] = buffer_array[i];
        }
        city.x_coord = x;
        city.y_coord = y;
        cities[index_cities] = city;
        index_cities ++;
        calculate_center();
        generate();
    }

    void print_city_array(int index){
        //for testing
        cout << cities[index].x_coord << " " << cities[index].y_coord << endl;
    }

    void print_elastic_net_array(){
        //for testing
        cout << "Elastic net: \n";
        for(int i = 0 ; i < index_elastic_points; i++){
            cout << elastic_net_points[i].x_coord << " " << elastic_net_points[i].y_coord << endl;
        }
        cout << endl << endl;
    }


    float get_center_x(){
        return center_x;
    }

    void set_center_x(float new_center_x){
        center_x = new_center_x;
    }

    float get_center_y(){
        return center_y;
    }

    void set_center_y(float new_center_y){
        center_y = new_center_y;
    }

    float get_rk(){
        return rk;
    }

    void set_rk(float new_rk){
        rk = new_rk;
    }

    float get_cv(){
        return cv;
    }

    void set_cv(float new_cv){
        cv = new_cv;
    }


};

class Iterable{

private:
    float alpha = 1;
    float beta = 1;
    float k = 0.1;


public:

    Elastic_net elastic_net;
    void apply(){
        float delta_x = 0;
        float delta_y = 0;
        float sum_x = 0;
        float sum_y = 0;
        float v_i_a = 0;
        int index_left_node = 0;
        int index_right_node = 0;

        for(int a = 0; a < elastic_net.index_elastic_points; a++){
            for(int i = 0; i < elastic_net.index_cities; i++){
                v_i_a = calculate_v_i_a(i,a);
                sum_x += v_i_a * (elastic_net.cities[i].x_coord - elastic_net.elastic_net_points[a].x_coord);
                sum_y += v_i_a * (elastic_net.cities[i].y_coord - elastic_net.elastic_net_points[a].y_coord);
            }
            delta_x = sum_x*alpha;
            delta_y = sum_y*alpha;

            sum_x = 0;
            sum_y = 0;

            //elastic net is a circle, saved in an array. therefore we have to assign the indices of left and right node correctly
            if(a == 0){
                index_left_node = elastic_net.index_elastic_points;
            }else{
                index_left_node = a-1;
            }

            if(a == elastic_net.index_elastic_points){
                index_right_node = 0;
            }else{
                index_right_node = a+1;
            }

            sum_x = elastic_net.elastic_net_points[index_left_node].x_coord + elastic_net.elastic_net_points[index_right_node].x_coord -
                    2 * elastic_net.elastic_net_points[a].x_coord;

            sum_y = elastic_net.elastic_net_points[index_left_node].y_coord + elastic_net.elastic_net_points[index_right_node].y_coord -
                    2 * elastic_net.elastic_net_points[a].y_coord;

            delta_x += beta * k * sum_x;
            delta_y += beta * k * sum_y;

            elastic_net.elastic_net_points[a].x_coord += delta_x;
            elastic_net.elastic_net_points[a].y_coord += delta_y;

            //reset
            sum_x = 0;
            sum_y = 0;


        }

    }

    float calculate_v_i_a(int i, int a){
        float sum = 0;
        for(int b = 0; b < elastic_net.index_elastic_points; b++){
            sum += exp(-(pow(elastic_net.cities[i].x_coord - elastic_net.elastic_net_points[b].x_coord, 2)+
                         pow(elastic_net.cities[i].x_coord - elastic_net.elastic_net_points[b].x_coord, 2))/2*pow(calculate_k(),2));
        }

        float result = (exp(-(pow(elastic_net.cities[i].x_coord - elastic_net.elastic_net_points[a].x_coord, 2)+
                             pow(elastic_net.cities[i].x_coord - elastic_net.elastic_net_points[a].x_coord, 2))/2*pow(calculate_k(),2)))/sum;

        return result;
    }

    float calculate_k(){


        return k;
    }

    float get_alpha(){
        return alpha;
    }

    void set_alpha(float new_alpha){
        alpha = new_alpha;
    }

    float get_beta(){
        return beta;
    }

    void set_beta(float new_beta){
        alpha = new_beta;
    }

    float get_k(){
        return alpha;
    }

    void set_k(float new_alpha){
        alpha = new_alpha;
    }

};


int main(){

    Iterable interface;
    //interface.elastic_net.set_rk(1);
        interface.elastic_net.add(1,1);
        interface.elastic_net.add(3,3);
        interface.elastic_net.add(2,1.3);
        interface.elastic_net.add(4.2,3.1);
        interface.elastic_net.add(2.5,1.5);
        interface.elastic_net.add(1.7,2.7);
        interface.elastic_net.add(5,1.4);
        interface.elastic_net.add(4.1,2.2);
        interface.elastic_net.add(2.3,3.2);
        interface.elastic_net.add(1.9,2.9);


        interface.elastic_net.print_elastic_net_array();
        for(int i = 0; i < 100; i++){
            interface.apply();
            interface.elastic_net.print_elastic_net_array();
        }


//    Elastic_net pls;
//    pls.add(1,1);
//    pls.add(3,3);
//    pls.add(2,1.3);
//    pls.add(4.2,3.1);
//    pls.add(2.5,1.5);
//    pls.add(1.7,2.7);
//    pls.add(5,1.4);
//    pls.add(4.1,2.2);
//    pls.add(2.3,3.2);
//    pls.add(1.9,2.9);

//    cout << "cities\n";
//    for(int i = 0; i < 10; i++){
//        pls.print_city_array(i);
//    }

//    cout << "Center of elastic net (x,y): " << pls.get_center_x() << " " << pls.get_center_y() << endl;


//    cout << "\n elastic net\n";
//    for(int i = 0; i < 20; i++){
//        pls.print_elastic_net_array(i);
//    }

    return 0;
}
