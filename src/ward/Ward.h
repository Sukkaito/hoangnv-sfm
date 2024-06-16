#ifndef WARD_H
#define WARD_H
#include <bits/stdc++.h>
#include "lib/vecmath/vecmath.h"
#include "lib/nlohmann/json.hpp"
using namespace std;
class Ward
{
private:
    string name;
    Point2d pA,pB,pC,pD;
    Point2d entry,exit;
public:
    Ward();
    Ward(string n);
    void operator=(Ward const& w);
    void setPA(Point2d pA);
    void setPB(Point2d pB);
    void setPC(Point2d pC);
    void setPD(Point2d pD);

    void setEntry(Point2d entry);
    void setExit(Point2d exit);

    void setName(string name);
    string getName() const;
};
#endif // WARD_H