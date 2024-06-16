#include <bits/stdc++.h>
#include <src/pedestrian/Pedestrian.h>
#include <src/personel/Personel.h>
#include <src/patient/Patient.h>
#include <src/visitor/Visitor.h>
#include <src/ward/Ward.h>
#include <src/personality/Personality.h>
#include <src/utility/Utility.h>

#include <lib/nlohmann/json.hpp>


using json=nlohmann::json;
int main() {
    const json input = Utility::readInputData("data/input.json");
    const json personalityDist = input["personalityDistribution"]["distribution"];
    Personality::personalityMap = {
        {
            "open", Personality("open",
            stod((string) personalityDist["open"]["positiveEmotionThreshold"]),
            stod((string) personalityDist["open"]["negativeEmotionThreshold"]),
            personalityDist["open"]["lambda"])
        },
        {
            "neurotic", Personality("neurotic",
            stod((string) personalityDist["neurotic"]["positiveEmotionThreshold"]),
            stod((string) personalityDist["neurotic"]["negativeEmotionThreshold"]),
            personalityDist["neurotic"]["lambda"])
        }
    };

    const json velocityDist = input["walkability"]["distribution"];
    Pedestrian::velocityMap = {
        {"noDisabilityNoOvertaking", (double) velocityDist["noDisabilityNoOvertaking"]["velocity"]},
        {"noDisabilityOvertaking", (double) velocityDist["noDisabilityOvertaking"]["velocity"]},
        {"crutches", (double) velocityDist["crutches"]["velocity"]},
        {"sticks", (double) velocityDist["sticks"]["velocity"]},
        {"wheelchairs", (double) velocityDist["wheelchairs"]["velocity"]},
        {"blind", (double) velocityDist["blind"]["velocity"]}
    };

    const json data = Utility::readInputData("data/Pedestrian.json");
    //std::vector<Pedestrian> pedes = data.get<vector<Pedestrian>>();
    std::vector<Personel> personels;
    std::vector<Visitor> visitors;
    std::vector<Patient> patients;
    //std::variant<Personel, Visitor, Patient> pedes; //slow
    
    for (auto& pedes : data) {
        string type = (string) pedes["type"];
        string walkString = (string) pedes["walkability"];
        Pedestrian p;
        from_json(pedes, p);
        if (type == "Personel") personels.push_back(Personel(p, NODISABILITY));
        else if (type == "Visitor") visitors.push_back(Visitor(p, Pedestrian::walkabilityMap[walkString]));
        else if (type == "Patient") patients.push_back(Patient(p, Pedestrian::walkabilityMap[walkString]));
    }
    json j;
    for (auto& p : personels) {
        json j;
        to_json(j, p);
        cout << j << endl;
        // cout << typeid(p).name() << endl;
    }
    return 0;
}