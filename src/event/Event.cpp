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

vector<double> Event::getIntensity() const{
    return intensity;
}

int Event::getTime() const
{
    return time;
}
