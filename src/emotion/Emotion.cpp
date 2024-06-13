using namespace std;
#include "Emotion.h"
void Emotion::setEmotion(double pleasure, double surprise, double anger, 
                    double fear, double hate, double sad) {
    this->pleasure = pleasure;
    this->surprise = surprise;
    this->anger = anger;
    this->fear = fear;
    this->hate = hate;
    this->sad = sad;
}

double Emotion::getPleasure() const {
    return pleasure;
}

double Emotion::getSurprise() const {
    return surprise;
}

double Emotion::getAnger() const {
    return anger;
}

double Emotion::getFear() const {
    return fear;
}

double Emotion::getHate() const {
    return hate;
}

double Emotion::getSad() const {
    return sad;
}