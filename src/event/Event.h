#ifndef EVENT_H
#define EVENT_H
#include<bits/stdc++.h>
#include <lib/nlohmann/json.hpp>
using namespace std;
class Event
{
private:
    std::vector<double> intensity {0,0,0,0,0,0};
    int time = -1;

public:
    Event();
    Event(std::vector<double>& in);
    Event(std::vector<double>& in, int t);
    // Getters
    std::vector<double> getIntensity() const;
    int getTime() const;

    // Setters
    void setIntensity(std::vector<double>& intensity);
    void setTime(int time);
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Event, intensity, time)
};
#endif // EVENT_H

