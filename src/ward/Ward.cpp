#include "Ward.h"
using namespace std;
void Ward::setPA(Point2d pA)
{
    this->pA=pA;
}

void Ward::setPB(Point2d pB)
{
    this->pB=pB;
}

void Ward::setPC(Point2d pC)
{
    this->pC=pC;
}


void Ward::setPD(Point2d pD)
{
    this->pD=pD;
}

void Ward::setEntry(Point2d entry){
    this->entry = entry;

}

void Ward::setExit(Point2d exit)
{
    this->exit=exit;
}

void Ward::setName(string name){
    this->name=name;
}
string Ward::getName(){
    return name;
}