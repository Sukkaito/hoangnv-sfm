#include <bits/stdc++.h>
#include "src/personality/Personality.h"  // Include the header where Personality is declared
#include "src/ward/Ward.h"        // Include the header where Ward is declared
#include "src/event/Event.h"
#include "src/agvEvent/AgvEvent.h"   
using namespace std;
class Pedestrian
{
private:
    float acceleration;
    float desiredSpeed;
    struct nodes
    {
        string description;
        struct distribution
        {
            struct normal
            {
                string description;
                int samples;
                int numberOfValues;
                int minValue;
                int maxValue;
            } normalDistribution;
        } distribution;
    } ageDistribution;
    Ward start,end;
    vector<Ward> journey;
    int id;
    double velocity;
    Personality personality;
    Point2d tempPoints;
    double walkingTime;
    double distance;
    double age;
    vector<Event> events;
    AgvEvent impactOfAGV;
    double lambda;
    std::vector<double> timeDistances;
    double pleasure=0.75;
    double surprise=0.5;
    double anger=-0.2;
    double fear=-0.2;
    double hate=-0.4;
    double sad=-0.4;
public:
    void setAcceleration(float acceleration);
    double getAcceleration() const { return acceleration; }
    void setDesiredSpeed(float speed);
    void setAgeDistribution(string description, string normal_description, int numberOfValues, int minValue, int maxValue, int numOfAgents);
    nodes getAgeDistribution() const { return ageDistribution; }
    void setId(int id);
    void setStart(Ward start);
    void setEnd(Ward end);
    void setJourney(vector<Ward> journey);
    void setVelocity(double velocity);
    void setPersonality(Personality personality);
    void setTempPoints(Point2d tempPoints);
    void setWalkingTime(double walkingTime);
    void setDistance(double distance);
    void setAge(double age);
    void setEvents(vector<Event> events);
    void setImpactOfAGV(AgvEvent impactOfAGV);
    int getLambda();
    void setLambda();

    vector<Event> getEvents();

    vector<double> getTimeDistances();
    void setTimeDistances(vector<double> timeDistances);
    double getPleasure(){
        return pleasure;
    }
    double getSurprise(){
        return surprise;
    }
    double getAnger(){
        return anger;
    }
    double getFear(){
        return fear;
    }
    double getHate(){
        return hate;
    }
    double getSad(){
        return sad;
    }
};