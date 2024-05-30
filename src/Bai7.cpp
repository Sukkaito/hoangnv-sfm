#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include "src/pedestrian/Pedestrian.h"

using namespace std;

int countYounger(const vector<Pedestrian>& pedestrians) {
    int count = 0;
    for (const auto& p : pedestrians) {
        if (p.getAge() < 12) {
            count++;
        }
    }
    return count;
}

int countOlder(const vector<Pedestrian>& pedestrians) {
    int count = 0;
    for (const auto& p : pedestrians) {
        if (p.getAge() > 60) {
            count++;
        }
    }
    return count;
}
///ALKW
int countALKW(const vector<Pedestrian>& pedestrians) {
    int count = 0;
    for (const auto& p : pedestrians) {
        if (p.getStart().getName() == "A" || p.getStart().getName() == "L" || p.getStart().getName() == "K" || p.getStart().getName() == "W") {
            count++;
        }
    }
    return count;
}
///BFG
int countBFGMEN(const vector<Pedestrian>& pedestrians) {
    int count = 0;
    for (const auto& p : pedestrians) {
        if (p.getStart().getName() == "B" || p.getStart().getName() == "F" || p.getStart().getName() == "G" || p.getStart().getName() == "M" || p.getStart().getName() == "E" || p.getStart().getName() == "N") {
            count++;
        }
    }
    return count;
}

vector<double> getImpact(int numOfSamples, double minValue, double maxValue) {
    vector<double> impact(numOfSamples);
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(minValue, maxValue);
    for (int i = 0; i < numOfSamples; ++i) {
        impact[i] = dis(gen);
    }
    return impact;
}

vector<Pedestrian> assignImpact(vector<Pedestrian>& allPedestrians) {
    int nChildren = countYoungerThan12(allPedestrians);
    auto impactToChildren = getImpact(nChildren, 0.01, 0.99);

    int nPersonnelOfALKW = countALKW(allPedestrians);
    auto impactToALKW = getImpact(nPersonnelOfALKW, -0.29, 0.99);

    int nPersonnelOfBFGMEN = countBFGMEN(allPedestrians);
    auto impactToBFGMEN = getImpact(nPersonnelOfBFGMEN, -0.99, 0.29);
    for (auto& val : impactToBFGMEN) {
        val *= -1; 
    }

    int nElder = countOlderThan60(allPedestrians);
    auto impactToElder = getImpact(nElder, -0.99, 0.29);
    for (auto& val : impactToElder) {
        val *= -1; 
    }

    int nBlinder = 0; 
    auto impactToBlinder = getImpact(nBlinder, -0.99, 0.29);
    for (auto& val : impactToBlinder) {
        val *= -1; 
    }

    int nOthers = allPedestrians.size() - nBlinder - nElder - nPersonnelOfBFGMEN - nPersonnelOfALKW - nChildren;
    auto impactToOthers = getImpact(nOthers, -0.99, 0.99);

    for (auto& person : allPedestrians) {
        if (person.getAge() < 12) {
            person.setImpactOfAGV(impactToChildren);
        } else if (person.getStart().getName() == "A" || person.getStart().getName() == "L" || person.getStart().getName() == "K" || person.getStart().getName() == "W") {
            person.setImpactOfAGV(impactToALKW);
        } else if (person.getStart().getName() == "B" || person.getStart().getName() == "F" || person.getStart().getName() == "G" || person.getStart().getName() == "M" || person.getStart().getName() == "E" || person.getStart().getName() == "N") {
            person.setImpactOfAGV(impactToBFGMEN);
        } else if (person.getAge() > 60) {
            person.setImpactOfAGV(impactToElder);
        } else if (person.is_blind) {
            person.setImpactOfAGV(impactToBlinder);
        } else {
            person.setImpactOfAGV(impactToOthers);
        }
    }

    return allPedestrians;
}

// Check if  positive impact from AGV
bool majorityPositiveImpact(const vector<Pedestrian>& allPedestrians) {
    pedestrians = assignImpact(allPedestrians);
    int childrenPositiveCount = 0;
    int ALKWPositiveCount = 0;

    for (const auto& p : pedestrians) {
        if (p.getAge() < 12) {
            for (const auto& val : p.getImpactOfAGV().getNumberOfValues()) {
                if (val > 0) {
                    childrenPositiveCount++;
                }
            }
        } else if (p.getStart().getName() == "A" || p.getStart().getName() == "L" || p.getStart().getName() == "K" || p.getStart().getName() == "W") {
            for (const auto& val : p.getImpactOfAGV().getNumberOfValues()) {
                if (val > 0) {
                    ALKWPositiveCount++;
                }
            }
        }
    }

    double childrenPositivePercentage = static_cast<double>(childrenPositiveCount) / countYoungerThan12(pedestrians);
    double ALKWPositivePercentage = static_cast<double>(ALKWPositiveCount) / countALKW(pedestrians);

    return (childrenPositivePercentage > 0.5) || (ALKWPositivePercentage > 0.5);
}

// Check if  negative impact from AGV
bool majorityNegativeImpact(const vector<Pedestrian>& allPedestrians) {
    pedestrians = assignImpact(allPedestrians);
    int elderNegativeCount = 0;
    int blinderNegativeCount = 0;
    int BFGMENNegativeCount = 0;

    for (const auto& p : pedestrians) {
        if (p.getAge() > 60) {
            for (const auto& val : p.getImpactOfAGV().getNumberOfValues()) {
                if (val < 0) {
                    elderNegativeCount++;
                }
            }
        } 
        } else if (p.getStart().getName() == "B" || p.getStart().getName() == "F" || p.getStart().getName() == "G" || p.getStart().getName() == "M" || p.getStart().getName() == "E" || p.getStart().getName() == "N") {
            for (const auto& val : p.getImpactOfAGV().getNumberOfValues()) {
                if (val < 0) {
                    BFGMENNegativeCount++;
                }
            }
        }
        else  { //person is blinder ch biet check dk nhu nao
            for (const auto& val : p.getImpactOfAGV().getNumberOfValues()) {
                if (val < 0) {
                    blinderNegativeCount++;
                }
            }
    }

    double elderNegativePercentage = static_cast<double>(elderNegativeCount) / countOlderThan60(pedestrians);
    double blinderNegativePercentage = static_cast<double>(blinderNegativeCount) / countBlinder(pedestrians);
    double BFGMENNegativePercentage = static_cast<double>(BFGMENNegativeCount) / countBFGMEN(pedestrians);

    return (elderNegativePercentage > 0.5) || (blinderNegativePercentage > 0.5) || (BFGMENNegativePercentage > 0.5);
}