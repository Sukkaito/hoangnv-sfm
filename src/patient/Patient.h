#ifndef PATIENT_H
#define PATIENT_H
#include<bits/stdc++.h>
#include "src/walkability/Walkability.h"
#include <src/pedestrian/Pedestrian.h>


class Patient : public Pedestrian {
    private:
        Walkability walkability;
    public:
        void setWalkability(Walkability walkability);
        Patient();
        Patient(Pedestrian& p, Walkability w);
        friend void to_json(nlohmann::json& json, const Patient& p);

};

#endif