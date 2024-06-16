
#include "Personality.h"
#include "src/utility/Utility.h"
using namespace Utility;

Personality::Personality() {};
Personality::Personality(string _name): name(move(_name)) {};

Personality::Personality(string _name, double _positiveEmotionThreshold, double _negativeEmotionThreshold, int _lambda):
    name(move(_name)), positiveEmotionThreshold(_positiveEmotionThreshold),
    negativeEmotionThreshold(_negativeEmotionThreshold), lambda(_lambda) {};

void Personality::setPositiveEmotionThreshold(double positiveEmotionThreshold)
{
    this->positiveEmotionThreshold=positiveEmotionThreshold;
}

void Personality::setNegativeEmotionThreshold(double negativeEmotionThreshold)
{
    this->negativeEmotionThreshold=negativeEmotionThreshold;
}

void Personality::setLambda(int lambda)
{
    this->lambda=lambda;
}

int Personality::getLambda() const {
    return lambda;
}

void Personality::setName(string name){
    this->name=name;
}
string Personality::getName() const{
    return name;
}
