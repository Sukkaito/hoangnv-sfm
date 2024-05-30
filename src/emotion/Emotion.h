#ifndef EVENT_H
#define EVENT_H
#include<bits/stdc++.h>
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
        void setPleasure(double pleasure);
        void setSurprise (double surprise);
        void setAnger(double anger);
        void setFear(double fear);
        void setHate(double hate);
        void setSad(double sad);
        double getSurprise() const {
	        return surprise;
        }
        double getPleasure() const{
            return pleasure;
        }
        double getAnger() const{
            return anger;
        }
        double getFear() const{
            return fear;
        }
        double getHate() const{
            return hate;
        }
        double getSad() const{
            return sad;
        }
};
#endif // EVENT_H

