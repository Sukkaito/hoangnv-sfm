
// acceleration
// agvDesiredSpeed
// ageDistribution
// walkability
#include "Pedestrian.h"
#include "src/personality/Personality.h"  // Include the header where Personality is declared
#include <src/patient/Patient.h>
#include <src/personel/Personel.h>
#include <src/visitor/Visitor.h>
#include "src/ward/Ward.h"        // Include the header where Ward is declared
#include "src/event/Event.h"
#include "src/agvEvent/AgvEvent.h"
#include "src/utility/Utility.h"
using namespace std;
using namespace Utility;

void to_json(nlohmann::json& json, const Pedestrian& p) {
        json["ID"] = p.ID; 
        json["start"] = p.start.getName();
        json["end"] = p.end.getName();
        std::vector<string> journey;
        for (auto& j : p.journey) journey.push_back(j.getName());
        json["journey"] = journey;
        json["velocity"] = p.velocity; 
        json["personality"] = p.personality; 
        json["emotion"] = p.emotion; 
        json["events"] = p.events; 
        json["walkingTime"] = p.walkingTime; 
        json["distance"] = p.distance; 
        json["age"] = p.age; 
        json["impactOfAGV"] = p.impactOfAGV;
        double point[2];
        p.tempPoints.get(point);
        json["tempPoints"] = point;
    }

void from_json(const nlohmann::json& json, Pedestrian& p) {
        // cout << json << endl;
        json.at("ID").get_to(p.ID);
        // cout << "ID: " << p.ID << endl;
        //cout << "json[\"start\"]: " << (string) json["start"] << endl;
        p.start = Ward(json["start"]);
        // cout << "p.start = " << p.start.getName() << endl;
        p.end = Ward(json["end"]);
        // cout << "p.end = " << p.end.getName() << endl;
        try {
            auto jour = json["journey"];
            std::vector<Ward> journey;
            for (auto& j : jour) journey.push_back(Ward(j));
            p.journey = journey;
        }
        catch (...) {
            p.journey = std::vector<Ward> {Ward(json["journey"])};
        }
        
        // cout << "p.journey = ";
        // for (auto j : p.journey) cout << j.getName() << " ";
        // cout << endl;

        //json.at("velocity").get_to(p.velocity);
        p.velocity = Pedestrian::velocityMap[json["walkability"]]; //Map velocity according to input.json
        // cout << "p.velocity = " << p.velocity << endl;

        // cout << json["personality"] << endl;
        p.personality = Personality::personalityMap[json["personality"]];
        // cout << "p.personality = " << p.personality.getName() << endl;
        
        json.at("emotion").get_to(p.emotion);
        // cout << p.emotion.getAnger() << endl;

        json.at("events").get_to(p.events);
        // for (auto t: p.getTimeDistances()) cout << t << " ";
        // cout << endl;

        json.at("walkingTime").get_to(p.walkingTime); 
        json.at("distance").get_to(p.distance); 
        json.at("age").get_to(p.age);
        // cout << "Age: " << p.age << endl;

        json.at("impactOfAGV").get_to(p.impactOfAGV);
        // cout << "impactOfAGV_time: " << p.impactOfAGV.getTime() << endl;

        std::vector<double> point = json.at("tempPoints").get<std::vector<double>>();
        p.tempPoints = Point2d(point[0], point[1]);
    }


Pedestrian::Pedestrian() {}
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

ostream& operator<<(ostream &os, const Pedestrian& p)
{
    nlohmann::json j;
    to_json(j, p);
    os << j;
    return os;
}
