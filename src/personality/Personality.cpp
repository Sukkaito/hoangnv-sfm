
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

void Personality::setPercentage(int percentage)
{
    this->percentage=percentage;
}

void Personality::setName(string name){
    this->name=name;
}
string Personality::getName(){
    return name;
}
