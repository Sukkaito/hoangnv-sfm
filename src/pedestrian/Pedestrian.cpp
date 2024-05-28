
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

// Getters
int Pedestrian::getID() const {
    return ID;
}

Ward Pedestrian::getStart() const {
    return start;
}

Ward Pedestrian::getEnd() const {
    return end;
}

std::vector<Ward> Pedestrian::getJourney() const {
    return journey;
}

double Pedestrian::getVelocity() const {
    return velocity;
}

Personality Pedestrian::getPersonality() const {
    return personality;
}

Emotion Pedestrian::getEmotion() const {
    return emotion;
}

std::vector<Event> Pedestrian::getEvents() const {
    return events;
}

double Pedestrian::getWalkingTime() const {
    return walkingTime;
}

double Pedestrian::getDistance() const {
    return distance;
}

double Pedestrian::getAge() const {
    return age;
}

AGVEvent Pedestrian::getImpactOfAGV() const {
    return impactOfAGV;
}

Point2d Pedestrian::getTempPoints() const {
    return tempPoints;
}

// Setters
void Pedestrian::setID(int id) {
    this->ID = id;
}

void Pedestrian::setStart(const Ward& start) {
    this->start = start;
}

void Pedestrian::setEnd(const Ward& end) {
    this->end = end;
}

void Pedestrian::setJourney(const std::vector<Ward>& journey) {
    this->journey = journey;
}

void Pedestrian::setVelocity(double velocity) {
    this->velocity = velocity;
}

void Pedestrian::setPersonality(const Personality& personality) {
    this->personality = personality;
}

void Pedestrian::setEmotion(const Emotion& emotion) {
    this->emotion = emotion;
}

void Pedestrian::setEvents(const std::vector<Event>& events) {
    this->events = events;
}

void Pedestrian::setWalkingTime(double walkingTime) {
    this->walkingTime = walkingTime;
}

void Pedestrian::setDistance(double distance) {
    this->distance = distance;
}

void Pedestrian::setAge(double age) {
    this->age = age;
}

void Pedestrian::setImpactOfAGV(const AGVEvent& impactOfAGV) {
    this->impactOfAGV = impactOfAGV;
}

void Pedestrian::setTempPoints(const Point2d& tempPoints) {
    this->tempPoints = tempPoints;
}

int Pedestrian::getLambda() const {
    return personality.getLambda();
}

double Pedestrian::getPleasure() const {
    return emotion.getPleasure();
}

double Pedestrian::getSurprise() const {
    return emotion.getSurprise();
}

double Pedestrian::getAnger() const {
    return emotion.getAnger();
}

double Pedestrian::getFear() const {
    return emotion.getFear();
}

double Pedestrian::getHate() const {
    return emotion.getHate();
}

double Pedestrian::getSad() const {
    return emotion.getSad();
}

std::vector<int> Pedestrian::getTimeDistances() const {
    std::vector<int> timeDists;
    for (auto event : events) {
        timeDists.push_back(event.getTime());
    }
    return timeDists;
}
