#ifndef PERSONALITY_H
#define PERSONALITY_H
#include <bits/stdc++.h>
#include "lib/vecmath/vecmath.h"
#include "lib/nlohmann/json.hpp"
using namespace std;
using json=nlohmann::json;
class Personality
{
private:
    string name;
    double positiveEmotionThreshold;
    double negativeEmotionThreshold;
    int lambda;
public:
    inline static std::map<string, Personality> personalityMap;
    Personality();
    Personality(string _name);
    Personality(string _name, double _positiveEmotionThreshold, double _negativeEmotionThreshold, int _lambda);
    void setPositiveEmotionThreshold(double positiveEmotionThreshold);
    void setNegativeEmotionThreshold(double negativeEmotionThreshold);
    
    void setName(string name);
    string getName() const;

    void setLambda(int lambda);
    int getLambda() const;

    //Methods
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Personality, name, positiveEmotionThreshold, negativeEmotionThreshold, lambda)
    //void operator=(Personality const &p);
};
#endif // PERSONALITY_H
