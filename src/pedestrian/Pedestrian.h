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
    
    //Phương thức lấy tọa độ các điểm trung gian
    //Nhận điểm đầu,điểm đích, các điểm trung gian.
    //Trả 1 mảng các điểm theo thứ tự từ đích -> đầu
    vector<Point2d> getWayPoint(Point2d s, Point2d d,vector<Point2d> mid);
};
