#include "../pedestrian/Pedestrian.h"
//#include "../pedestrian/Pedestrian.cpp"
#include "../ward/Ward.h"
//#include "../ward/Ward.cpp"
#include "../utility/Utility.h"
#include "../lib/nlohmann/json.hpp"
#include <vector>

using json=nlohmann::json;

std::vector<Pedestrian> instantiatePedestrians(){
    json dt=Utility::readInputData("data/input.json");
    int numOfAgents=dt["numOfAgents"]["value"];
    json data=Utility::readInputData("data/Pedestrian.json");
    std::vector<Pedestrian> Pedestrians;
    for(int i=0;i<numOfAgents;i++){
        //ID
        Pedestrian tmp;
        tmp.setID(data[i]["ID"]);

        //start,end Ward
        Ward st;
        st.setName(data[i]["start"]);
        tmp.setStart(st);
        Ward ed;
        ed.setName(data[i]["start"]);
        tmp.setEnd(ed);

        //journey
        std::vector<Ward> journey;
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
        
        //event: intensity and time
        std::vector<Event> events;
        for(int j=0;j<data[i]["events"].size();j++){
            Event event;
            vector<double> intensity;
            for(int k=0;k<data[i]["events"]["intensity"].size();k++){
                intensity.push_back(data[i]["events"]["intensity"][k]);
            }
            event.setIntensity(intensity);
            event.setTime(data[i]["event"]["time"]);
            events.push_back(event);
        }
        tmp.setEvents(events);
    }
    return Pedestrians;
}

