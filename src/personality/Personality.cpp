
#include "Personality.h"

void Personality::setPositiveEmotionThreshold(string positiveEmotionThreshold)
{
    this->positiveEmotionThreshold=positiveEmotionThreshold;
}

void Personality::setNegativeEmotionThreshold(string negativeEmotionThreshold)
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
