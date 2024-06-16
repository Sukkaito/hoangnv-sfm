#include "Patient.h"
#include "src/walkability/Walkability.h"
#include<bits/stdc++.h>
void Patient::setWalkability(Walkability walkability)
{
    this->walkability=walkability;
}

Patient::Patient() : Pedestrian() {}

Patient::Patient(Pedestrian& p, Walkability w): Pedestrian(p), walkability(w) {}

void to_json(nlohmann::json &json, const Patient &p)
{
    to_json(json, (Pedestrian) p);
    json["type"] = "Patient";
    json["walkability"] = p.walkability;
}