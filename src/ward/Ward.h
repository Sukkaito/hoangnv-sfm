#ifndef WARD_H
#define WARD_H
#include <bits/stdc++.h>
#include "lib/vecmath/vecmath.h"
using namespace std;
class Ward
{
private:
    Point2d pA,pB,pC,pD;
    Point2d entry,exit;

public:
    void setPA(Point2d pA);
    void setPB(Point2d pB);
    void setPC(Point2d pC);
    void setPD(Point2d pD);

    void setEntry(Point2d entry);
    void setExit(Point2d exit);
};
#endif // WARD_H