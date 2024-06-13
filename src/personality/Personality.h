#ifndef PERSONALITY_H
#define PERSONALITY_H
#include <bits/stdc++.h>
#include "lib/vecmath/vecmath.h"
using namespace std;
class Personality
{
private:
    string name;
    string positiveEmotionThreshold;
    string negativeEmotionThreshold;
    int lambda;

public:
    void setPositiveEmotionThreshold(string positiveEmotionThreshold);
    void setNegativeEmotionThreshold(string negativeEmotionThreshold);
    
    void setName(string name);
    string getName() const;

    void setLambda(int lambda);
    int getLambda() const;
};
#endif // PERSONALITY_H
