#include<iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <sstream>
struct PersonData {
    double fooot_size_cm;
    double penis_size_cm;
};

double f(double x,double w){
    double b = 0;
    return x*w+b;
}
double cost(std::vector<PersonData> data ,double weight){
        double sum_cost = 0;
        for (const PersonData p:data){
            double cost = pow(p.penis_size_cm - f(p.fooot_size_cm,weight) , 2);
            sum_cost += cost;
        }
        int samples_size = data.size();
        double average_cost=sum_cost/(2*samples_size);
        return average_cost;

}
double train_model(std::vector<PersonData> data ){
    // try varios weights and return the best one 
    double weight =1;
    double step = 0.01;
    for(int i = 0 ;i < 1000; i++){
        double add_cost = cost(data , weight+step);
        double sub_cost = cost(data , weight-step);
        weight = add_cost>sub_cost?weight-step:weight+step;
        std::cout << "current w:"<<weight<<std::endl;
    }
    return weight;
}

int main(){
    
    std::vector<PersonData> data;
    std::string line;
    std::ifstream file("./data.csv");
    
    if(!file.is_open()){
        std::cout << "error opening data file"<<std::endl;
        return 1;
    }
    
    std::getline(file , line); // skipping the first line 
    int samples_size = 0;
    while(getline(file,line)){
        std::stringstream ss(line);
        std::string cell1 , cell2;
        std::getline(ss , cell1 , ',');
        std::getline(ss , cell2 , ',');
        PersonData temp_p = {std::stod(cell1) , std::stod(cell2)};
        data.push_back(temp_p);
        samples_size++;
    }
    std::cout<<train_model(data)<<std::endl;
    std::cout<<f(42,train_model(data))<<std::endl;
   
    return 0 ;
}