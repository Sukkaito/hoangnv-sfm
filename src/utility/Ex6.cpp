#include "src/pedestrian/Pedestrian.h"
#include "src/pedestrian/Pedestrian.cpp"
#include "src/event/Event.h"
#include <vector>
using namespace std;
std:: vector<vector<double>> Ex6(Pedestrian p,int timeHorizon){
    std::vector<Event> events =p.getEvents();
    int lambda=p.getLambda();
    std::vector<int> times=p.getTimeDistances();
    std::vector<std::vector<double>> allEmotions={
        {p.getPleasure()},
        {p.getSurprise()},
        {p.getAnger()},
        {p.getFear()},
        {p.getHate()},
        {p.getSad()}
    };
    double pl, su, a, f, h, sa;
    pl = events[0].getIntensity()[0] + allEmotions[0][0] * exp(-lambda) + allEmotions[0][0];
    su = events[1].getIntensity()[0] + allEmotions[1][0] * exp(-lambda) + allEmotions[1][0];
    a = events[2].getIntensity()[0] + allEmotions[2][0] * exp(-lambda) + allEmotions[2][0];
    f = events[3].getIntensity()[0] + allEmotions[3][0] * exp(-lambda) + allEmotions[3][0];
    h = events[4].getIntensity()[0] + allEmotions[4][0] * exp(-lambda) + allEmotions[4][0];
    sa = events[5].getIntensity()[0] + allEmotions[5][0] * exp(-lambda) + allEmotions[5][0];
    int lastTime = 0;
    int index = 0;
    allEmotions[0].push_back(pl);
    allEmotions[1].push_back(su);
    allEmotions[2].push_back(a);
    allEmotions[3].push_back(f);
    allEmotions[4].push_back(h);
    allEmotions[5].push_back(sa);
    for (int i = 1; i < timeHorizon; ++i) {
        pl = allEmotions[0][i];
        su = allEmotions[1][i];
        a = allEmotions[2][i];
        f = allEmotions[3][i];
        h = allEmotions[4][i];
        sa = allEmotions[5][i];

        if (i - lastTime == times[index]) {
            index += 1;
            lastTime = i;
            pl += allEmotions[0][i] * exp(-lambda) + events[0].getIntensity()[index];
            su += allEmotions[1][i] * exp(-lambda) + events[1].getIntensity()[index];
            a += allEmotions[2][i] * exp(-lambda) + events[2].getIntensity()[index];
            f += allEmotions[3][i] * exp(-lambda) + events[3].getIntensity()[index];
            h += allEmotions[4][i] * exp(-lambda) + events[4].getIntensity()[index];
            sa += allEmotions[5][i] * exp(-lambda) + events[5].getIntensity()[index];
        }

        allEmotions[0].push_back(pl);
        allEmotions[1].push_back(su);
        allEmotions[2].push_back(a);
        allEmotions[3].push_back(f);
        allEmotions[4].push_back(h);
        allEmotions[5].push_back(sa);
    }

    return allEmotions;

}

