#ifndef EMOTION_H
#define EMOTION_H
#include <bits/stdc++.h>
#include <lib/nlohmann/json.hpp>
using namespace std;
class Emotion 
{
private:
    double pleasure;
    double surprise;
    double anger;
    double fear;
    double hate;
    double sad;

public:
    // Setter for emotion attributes
    void setEmotion(double pleasure, double surprise, double anger, 
                    double fear, double hate, double sad);

    // Getters for emotion attributes
    double getPleasure() const;
    double getSurprise() const;
    double getAnger() const;
    double getFear() const;
    double getHate() const;
    double getSad() const;
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Emotion, pleasure, surprise, anger, fear, hate, sad)
};

#endif