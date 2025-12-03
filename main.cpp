#include<iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <sstream>
struct PersonData {
    double foot_size_cm;
    double penis_size_cm;
};

double f(double x,double w){
    double b = 0;
    return x*w+b;
}
double cost(std::vector<PersonData> data ,double weight){
        double sum_cost = 0;
        for (const PersonData p:data){
            double cost = pow(p.penis_size_cm - f(p.foot_size_cm,weight) , 2);
            sum_cost += cost;
        }
        int samples_size = data.size();
        double average_cost=sum_cost/(2*samples_size);
        return average_cost;

}
double train_model_bruteForce_hillClimbing(std::vector<PersonData> data ){
    std::ofstream weight_file("weight_file");
    if(!weight_file.is_open()){
        std::cout << "error opening the weight file (creating) !!" <<std::endl;
    }
    std::ofstream cost_file("cost_file");
    if(!cost_file.is_open()){
        std::cout << "error opening the cost file (creating) !!" <<std::endl;
    }
    double weight =1;
    double step = 0.01;
    double chanding_past=0;
    double add_cost , sub_cost;
    do
    {        
        add_cost = cost(data , weight+step);
        sub_cost = cost(data , weight-step);
        
        weight = add_cost>sub_cost?weight-step:weight+step;
        
        weight_file << weight<< std::endl;
        cost_file << add_cost << std::endl;

        std::cout << add_cost<<std::endl;
    
    } while (add_cost>=0.1 and sub_cost >=0.1 );
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
    std::cout<<f(34,train_model_bruteForce_hillClimbing(data))<<std::endl;
   
    return 0 ;
}