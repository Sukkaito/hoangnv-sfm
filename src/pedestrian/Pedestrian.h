#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H
#include <bits/stdc++.h>
#include "src/personality/Personality.h"  // Include the header where Personality is declared
#include "src/ward/Ward.h"        // Include the header where Ward is declared
#include "src/event/Event.h"
#include "src/agvEvent/AgvEvent.h"   
#include "src/emotion/Emotion.h"
using namespace std;
class Pedestrian
{
private:
    int ID;
    Ward start;
    Ward end;
    std::vector<Ward> journey;
    double velocity;
    Personality personality;
    Emotion emotion;
    std::vector<Event> events;
    double walkingTime;
    double distance;
    double age;
    AGVEvent impactOfAGV;
    Point2d tempPoints;
public:
    // Getters (const because they do not modify the object)
    int getID() const;
    Ward getStart() const;
    Ward getEnd() const;
    std::vector<Ward> getJourney() const;
    double getVelocity() const;
    Personality getPersonality() const;
    Emotion getEmotion() const;
    std::vector<Event> getEvents() const;
    double getWalkingTime() const;
    double getDistance() const;
    double getAge() const;
    AGVEvent getImpactOfAGV() const;
    Point2d getTempPoints() const;

    //Getter for subatrribs
    int getLambda() const; //Get Personality's lambda
    double getPleasure() const;
    double getSurprise() const;
    double getAnger() const;
    double getFear() const;
    double getHate() const;
    double getSad() const;
    std::vector<int> getTimeDistances() const;

    // Setters
    void setID(int id);
    void setStart(const Ward& start);
    void setEnd(const Ward& end);
    void setJourney(const std::vector<Ward>& journey);
    void setVelocity(double velocity);
    void setPersonality(const Personality& personality);
    void setEmotion(const Emotion& emotion);
    void setEvents(const std::vector<Event>& events);
    void setWalkingTime(double walkingTime);
    void setDistance(double distance);
    void setAge(double age);
    void setImpactOfAGV(const AGVEvent& impactOfAGV);
    void setTempPoints(const Point2d& tempPoints);
};

#endif