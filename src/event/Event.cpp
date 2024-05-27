#include<bits/stdc++.h>
#include "Event.h"
using namespace std;

void Event::setDescription(string description)
{
    this->description=description;
}

void Event::setSample(int sample)
{
    this->sample=sample;
}

void Event::setMinValue(int minValue)
{
    this->minValue=minValue;
}

void Event::setMaxValue(int maxValue)
{
    this->maxValue=maxValue;
}

void Event::setNumberOfValues(int numberOfValues)
{
    this->numberOfValues=numberOfValues;
}

void Event::setNumberOfFields(int numberOfFields)
{
    this->numberOfFields=numberOfFields;
}

void Event::setIntensity(vector<double> intensity){
    this->intensity=intensity;
}

vector<double> Event::getIntensity(){
    return intensity;
}
