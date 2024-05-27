#include "../pedestrian/Pedestrian.h"
//#include "../pedestrian/Pedestrian.cpp"
#include "../ward/Ward.h"
//#include "../ward/Ward.cpp"
#include "../utility/Utility.h"
#include "../lib/nlohmann/json.hpp"
#include <vector>

using json=nlohmann::json;

void instantiatePedestrians(){
    json dt=Utility::readInputData("data/input.json");
    int numOfAgents=dt["numOfAgents"]["value"];
    json data=Utility::readInputData("data/Pedestrian.json");
    std::vector<Pedestrian> objPedestrians;
    for(int i=0;i<numOfAgents;i++){
        //ID
        Pedestrian tmp;
        tmp.setId(data[i]["ID"]);

        //start,end Ward
        Ward st;
        st.setName(data[i]["start"]);
        tmp.setStart(st);
        Ward ed;
        ed.setName(data[i]["start"]);
        tmp.setEnd(ed);

        //journey
        vector<Ward> journey;
        for(int j=0;j<data[i]["journey"].size();j++){
            Ward w;
            w.setName(data[i]["journey"][j]);
            journey.push_back(w);
        }
        tmp.setJourney(journey);

        //velocity
        tmp.setVelocity(data[i]["velocity"]);

        //personality
        Personality per;
        per.setName(data[i]["personality"]);
        tmp.setPersonality(per);
        
        //event
        vector<Event> events;
        for(int j=0;j<data[i]["events"].size();j++){
            Event event;
            vector<double> intensity;
            for(int k=0;k<data[i]["events"]["intensity"].size();k++){
                intensity.push_back(data[i]["events"]["intensity"][k]);
            }
            event.setIntensity(intensity);
            events.push_back(event);
        }
        tmp.setEvents(events);
        //timeDistances
        vector<double> timeDistances;
        for(int j=0;j<data[i]["events"].size();j++){
            double time=data[i]["events"][j]["time"];
            timeDistances.push_back(time);
        }
        tmp.setTimeDistances(timeDistances);
        objPedestrians.push_back(tmp);
    }
}

