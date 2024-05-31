#include "../lib/nlohmann/json.hpp"
#include "../utility/Utility.h"
#include <vector>
#include <map>
#include <cmath>
#include <iostream>
#include<random>
using json=nlohmann::json;

std::map<string,std::vector<int>> Leavings(){ //return number of leavings at each ward choronologicaly
    json dt=Utility::readInputData("data/input.json");
    json data=Utility::readInputData("data/Pedestrian.json");
    json dtw=Utility::readInputData("data/Ward.json");
    int numOfAgents=dt["numOfAgents"]["value"];
    std::vector<string> Ward; // vector Ward's name
    for(int i=0;i<dtw.size();i++){
        Ward.push_back(dtw[i]);
    }
    std::map<string,std::vector<int>> res; 
    std::map<string,int> total_value;
    for(int i=0;i<numOfAgents;i++){
        total_value[data[i]["start"]]++;
    }
    std::random_device rd{};
    std::mt19937 gen{rd()}; 
    for(int i=0;i<Ward.size();i++){
        int start=(int) dt["leavingDistribution"]["distribution"][Ward[i]]["normal"]["end"];
        int end=(int) dt["leavingDistribution"]["distribution"][Ward[i]]["normal"]["start"];
        int timeStep= (int) dt["leavingDistribution"]["distribution"][Ward[i]]["normal"]["timeStep"];
        int numOfSamples=(int)((end-start+1)/timeStep);
        int std_dev=(int)dt["leavingDistribution"]["distribution"][Ward[i]]["normal"]["std_dev"];
        double mean=(double) total_value[Ward[i]]/numOfSamples;
        std::vector<int> leaving(numOfSamples,0); // so luong nguoi ra khoi Ward[i] theo cac moc thoi gian
        normal_distribution<double> d(mean,std_dev);
        do{
            for(int i=0;i<numOfSamples;i++){
                leaving[i]=round(d(gen));
            }
        }while(accumulate(leaving.begin(),leaving.end(),0)!=total_value[Ward[i]]);
        res[Ward[i]]=leaving;
    }
    return res;
}

