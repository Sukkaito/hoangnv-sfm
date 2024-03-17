
// acceleration
// agvDesiredSpeed
// ageDistribution
// walkability
#include "Pedestrian.h"
#include "src/personality/Personality.h"  // Include the header where Personality is declared
#include "src/ward/Ward.h"        // Include the header where Ward is declared
#include "src/event/Event.h"
#include "src/agvEvent/AgvEvent.h"
using namespace std;
void Pedestrian::setAcceleration(float acceleration)
{
    this->acceleration = acceleration;
}
void Pedestrian::setDesiredSpeed(float speed)
{
    this->desiredSpeed = speed;
}
void Pedestrian::setAgeDistribution(string description, string distribution_description, int numberOfValues, int minValue, int maxValue, int numOfAgents) {
    this->ageDistribution.description = description;
    this->ageDistribution.distribution.normalDistribution.description = distribution_description;
    this->ageDistribution.distribution.normalDistribution.samples = numOfAgents;
    this->ageDistribution.distribution.normalDistribution.numberOfValues = numberOfValues;
    this->ageDistribution.distribution.normalDistribution.minValue = minValue;
    this->ageDistribution.distribution.normalDistribution.maxValue = maxValue;
}

void Pedestrian::setId(int id)
{
    this->id=id;
}

void Pedestrian::setStart(Ward start)
{
    this->start=start;
}

void Pedestrian::setEnd(Ward end)
{
    this->end=end;
}

void Pedestrian::setJourney(vector<Ward> journey)
{
    this->journey=journey;
}

void Pedestrian::setVelocity(double velocity)
{
    this->velocity=velocity;
}

void Pedestrian::setPersonality(Personality personality)
{
    this->personality=personality;
}

void Pedestrian::setTempPoints(Point2d tempPoints)
{
    this->tempPoints=tempPoints;
}

void Pedestrian::setWalkingTime(double walkingTime)
{
    this->walkingTime=walkingTime;
}

void Pedestrian::setDistance(double distance)
{
    this->distance=distance;
}

void Pedestrian::setAge(double age)
{
    this->age=age;
}

void Pedestrian::setEvents(vector<Event> events)
{
    this->events=events;
}

void Pedestrian::setImpactOfAGV(AgvEvent impactOfAGV)
{
    this->impactOfAGV=impactOfAGV;
}
