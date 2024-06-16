#ifndef VISITOR_H
#define VISITOR_H
#include <bits/stdc++.h>
#include "src/walkability/Walkability.h"
#include "src/pedestrian/Pedestrian.h"

class Visitor : public Pedestrian{
    private:
        Walkability walkability;
    public:
        void setWalkability(Walkability walkability);
        Visitor();
        Visitor(Pedestrian& p, Walkability w);
        friend void to_json(nlohmann::json& json, const Visitor& p);

};

#endif