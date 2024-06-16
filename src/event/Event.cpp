#include<bits/stdc++.h>
#include "Event.h"
using namespace std;

void Event::setIntensity(vector<double>& intensity) {
    this->intensity=intensity;
}

void Event::setTime(int time)
{
    this-> time = time;
}

Event::Event() {}

Event::Event(std::vector<double>& in): intensity(in), time(-1) {};

Event::Event(std::vector<double>& in, int t): intensity(in), time(t) {}

vector<double> Event::getIntensity() const{
    return intensity;
}

int Event::getTime() const
{
    return time;
}
