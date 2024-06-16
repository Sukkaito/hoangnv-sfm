#include "Personel.h"
#include<bits/stdc++.h>
#include <src/walkability/Walkability.h>

void Personel::setWalkability(Walkability w)
{
    this->walkability = w;
}

Personel::Personel() : Pedestrian() {}

Personel::Personel(Pedestrian& p, Walkability w): Pedestrian(p), walkability(w) {}

void to_json(nlohmann::json &json, const Personel &p)
{
    to_json(json, (Pedestrian) p);
    json["type"] = "Personel";
    json["walkability"] = p.walkability;
}
