#ifndef EVENT_H
#define EVENT_H
#include<bits/stdc++.h>
using namespace std;
class Event
{
    private:
        string description;
        int sample;
        int minValue;
        int maxValue;
        int numberOfValues;
        int numberOfFields;
        vector<double> intensity;
    public:
        void setDescription(string description);
        void setSample(int sample);
        void setMinValue(int minValue);
        void setMaxValue(int maxValue);
        void setNumberOfValues(int numberOfValues);
        void setNumberOfFields(int numberOfFields);

        void setIntensity(vector<double> intensity);
        vector<double> getIntensity();
};
#endif // EVENT_H

