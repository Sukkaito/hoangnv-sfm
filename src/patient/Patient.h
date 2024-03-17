#include<bits/stdc++.h>
#include "src/walkability/Walkability.h"
#include "src/pedestrian/Pedestrian.h"

class Patient : public Pedestrian{
    private:
        Walkability walkability;
    public:
        void setWalkability(Walkability walkability);
};