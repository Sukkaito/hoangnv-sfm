#include "Visitor.h"
#include "src/walkability/Walkability.h"
#include<bits/stdc++.h>
void Visitor::setWalkability(Walkability walkability)
{
    this->walkability=walkability;
}

Visitor::Visitor() : Pedestrian() {}
Visitor::Visitor(Pedestrian& p, Walkability w): Pedestrian(p), walkability(w) {}

void to_json(nlohmann::json &json, const Visitor &p)
{
    to_json(json, (Pedestrian) p);
    json["type"] = "Visitor";
    json["walkability"] = p.walkability;
}
