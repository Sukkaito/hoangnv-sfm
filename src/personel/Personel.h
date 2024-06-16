#ifndef PERSONEL_H
#define PERSONEL_H
#include <bits/stdc++.h>
#include "src/pedestrian/Pedestrian.h"
#include <src/walkability/Walkability.h>
#include <lib/nlohmann/json.hpp>

class Personel : public Pedestrian{
    private:
        Walkability walkability;
    public:
        void setWalkability(Walkability w);
        Personel();
        Personel(Pedestrian& p, Walkability w);
        friend void to_json(nlohmann::json& json, const Personel& p);
        //could've overload from_json and operator<< as well but too lazy
};

#endif