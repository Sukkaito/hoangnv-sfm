#ifndef PERSONALITY_H
#define PERSONALITY_H
#include <bits/stdc++.h>
#include "lib/vecmath/vecmath.h"
using namespace std;
class Personality
{
private:
    string positiveEmotionThreshold;
    string negativeEmotionThreshold;
    int lambda;
    int percentage;
    

public:
    void setPositiveEmotionThreshold(string positiveEmotionThreshold);
    void setNegativeEmotionThreshold(string negativeEmotionThreshold);
    void setLambda(int lambda);
    void setPercentage(int percentage);
};
#endif // PERSONALITY_H
