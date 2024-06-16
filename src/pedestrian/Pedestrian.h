#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H
#include <bits/stdc++.h>
#include "src/personality/Personality.h"  // Include the header where Personality is declared
// #include <src/patient/Patient.h>
// #include <src/personel/Personel.h>
// #include <src/visitor/Visitor.h>
/*
    Forward declaration instead of normal include
    Compile order (if normal include):
        PEDESTRIAN_H (in progress) -> PATIENT_H (in progress) -> PEDESTRIAN_H (skip because already def)
        -> Err in PATIENT_H (since class Pedestrian is needed for PATIENT_H)

    => Need forward declaration in PEDESTRIAN_H so it won't def PATIENT_H until finishing PEDESTRIAN_H
    Explanation: https://stackoverflow.com/a/5320021
*/
class Patient;
class Personel;
class Visitor;
#include <src/walkability/Walkability.h>
#include "src/ward/Ward.h"        // Include the header where Ward is declared
#include "src/event/Event.h"
#include "src/agvEvent/AgvEvent.h"   
#include "src/emotion/Emotion.h"
#include <lib/nlohmann/json.hpp>
using namespace std;
//using json=nlohmann::json;

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
    inline static std::map<string, Walkability> walkabilityMap = {
        {"noDisabilityNoOvertaking", NODISABILITY},
        {"noDisabilityOvertaking", NODISABILITY},
        {"crutches", CRUTCHES},
        {"sticks", STICKS},
        {"wheelchairs", WHEELCHAIRS},
        {"blind", BLIND}
    };

    inline static std::map<string, double> velocityMap;
    Pedestrian();
    // NLOHMANN_DEFINE_TYPE_INTRUSIVE(Pedestrian, ID, start, end, journey, velocity, personality, emotion, events, walkingTime, distance, age, impactOfAGV, tempPoints)

    /// @brief Covnert Pedestrian Object to JSON
    /// @param nlohmann_json_j nlohmann::json to store JSON
    /// @param p Pedestrian input
    friend void to_json(nlohmann::json& nlohmann_json_j, const Pedestrian& p);

    /// @brief Convert a JSON objcet to Pedestrian object
    /// @param nlohmann_json_j nlohmann::json data input
    /// @param p Pedestrian to store
    friend void from_json(const nlohmann::json& nlohmann_json_j, Pedestrian& p);

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

    //Methods
    friend ostream& operator<<(ostream& os, const Pedestrian& p);
};

#endif