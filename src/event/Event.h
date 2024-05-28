#ifndef EVENT_H
#define EVENT_H
#include<bits/stdc++.h>
using namespace std;
class Event
{
private:
    std::vector<double> intensity {0,0,0,0,0,0};
    int time;

public:
    // Getters
    std::vector<double> getIntensity() const;
    int getTime() const;

    // Setters
    void setIntensity(std::vector<double>& intensity);
    void setTime(int time);
};
#endif // EVENT_H

