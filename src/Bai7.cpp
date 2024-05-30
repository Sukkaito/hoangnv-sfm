#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include "src/pedestrian/Pedestrian.h"

using namespace std;

int countYounger(const vector<Pedestrian> &pedestrians, int age)
{
    return count_if(pedestrians.begin(), pedestrians.end(), [age](const Pedestrian &p) { return p.getAge() < age; });
}

int countOlder(const vector<Pedestrian> &pedestrians, int age)
{
    return count_if(pedestrians.begin(), pedestrians.end(), [age](const Pedestrian &p) { return p.getAge() > age; });
}

int countALKW(const vector<Pedestrian> &pedestrians)
{
    return count_if(pedestrians.begin(), pedestrians.end(), [](const Pedestrian &p) {
        string name = p.getStart().getName();
        return name == "A" || name == "L" || name == "K" || name == "W";
    });
}

int countBFGMEN(const vector<Pedestrian> &pedestrians)
{
    return count_if(pedestrians.begin(), pedestrians.end(), [](const Pedestrian &p) {
        string name = p.getStart().getName();
        return name == "B" || name == "F" || name == "G" || name == "M" || name == "E" || name == "N";
    });
}

vector<vector<double>> getImpact(int numOfSamples, int numOfValues, double minValue, double maxValue)
{
    vector<vector<double>> impact(6, vector<double>(numOfSamples));
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(minValue, maxValue);
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < numOfSamples; ++j)
        {
            impact[i][j] = dis(gen);
        }
    }
    return impact;
}

vector<vector<double>> multiplyByNegativeOne(vector<vector<double>> matrix)
{
    for (auto &row : matrix)
    {
        for (auto &val : row)
        {
            val *= -1;
        }
    }
    return matrix;
}

vector<Pedestrian> assignImpact(vector<Pedestrian> &allPedestrians)
{
    int cnt_child = countYounger(allPedestrians, 12);
    auto impactToChildren = getImpact(cnt_child, 100, 0.01, 0.99);

    int nPersonnelOfALKW = countALKW(allPedestrians);
    auto impactToALKW = getImpact(nPersonnelOfALKW, 100, -0.29, 0.99);

    int nPersonnelOfBFGMEN = countBFGMEN(allPedestrians);
    auto impactToBFGMEN = multiplyByNegativeOne(getImpact(nPersonnelOfBFGMEN, 100, -0.29, 0.99));

    int cnt_elder = countOlder(allPedestrians, 60);
    auto impactToElder = multiplyByNegativeOne(getImpact(cnt_elder, 100, -0.29, 0.99));

    int cnt_blinder = 0; // Giả sử không có người mù
    auto impactToBlinder = multiplyByNegativeOne(getImpact(cnt_blinder, 100, -0.29, 0.99));

    int nOthers = 0; // Đếm số người còn lại
    for (const auto &p : allPedestrians)
    {
        if (!(p.getAge() < 12 || p.getAge() > 60 || p.getStart().getName() == "A" || p.getStart().getName() == "L" || p.getStart().getName() == "K" || p.getStart().getName() == "W" ||
              p.getStart().getName() == "B" || p.getStart().getName() == "F" || p.getStart().getName() == "G" || p.getStart().getName() == "M" || p.getStart().getName() == "E" || p.getStart().getName() == "N"))
        {
            nOthers++;
        }
    }

    auto impactToOthers = getImpact(nOthers, 100, -0.69, 0.99);

    for (auto &p : allPedestrians)
    {
        vector<double> impactOfAGV(6, 0.0);
        if (p.getAge() < 12)
        {
            for (int i = 0; i < 6; ++i)
            {
                impactOfAGV[i] += impactToChildren[i][0];
            }
            for (auto &row : impactToChildren)
            {
                row.erase(row.begin());
            }
        }
        else if (p.getStart().getName() == "A" || p.getStart().getName() == "L" || p.getStart().getName() == "K" || p.getStart().getName() == "W")
        {
            for (int i = 0; i < 6; ++i)
            {
                impactOfAGV[i] += impactToALKW[i][0];
            }
            for (auto &row : impactToALKW)
            {
                row.erase(row.begin());
            }
        }
        else if (p.getStart().getName() == "B" || p.getStart().getName() == "F" || p.getStart().getName() == "G" || p.getStart().getName() == "M" || p.getStart().getName() == "E" || p.getStart().getName() == "N")
        {
            for (int i = 0; i < 6; ++i)
            {
                impactOfAGV[i] += impactToBFGMEN[i][0];
            }
            for (auto &row : impactToBFGMEN)
            {
                row.erase(row.begin());
            }
        }
        else if (p.getAge() > 60)
        {
            for (int i = 0; i < 6; ++i)
            {
                impactOfAGV[i] += impactToElder[i][0];
            }
            for (auto &row : impactToElder)
            {
                row.erase(row.begin());
            }
        }
        else if (p.isBlind())
        {
            for (int i = 0; i < 6; ++i)
            {
                impactOfAGV[i] += impactToBlinder[i][0];
            }
            for (auto &row : impactToBlinder)
            {
                row.erase(row.begin());
            }
        }
        else
        {
            for (int i = 0; i < 6; ++i)
            {
                impactOfAGV[i] += impactToOthers[i][0];
            }
            for (auto &row : impactToOthers)
            {
                row.erase(row.begin());
            }
        }
        p.setImpactOfAGV(impactOfAGV);
    }

    return allPedestrians;
}

bool majorityPositiveImpact(const vector<Pedestrian> &allPedestrians)
{
    auto pedestrians = assignImpact(allPedestrians);
    int childrenPositiveCount = 0;
    int ALKWPositiveCount = 0;

    for (const auto &p : pedestrians)
    {
        if (p.getAge() < 12)
        {
            for (const auto &val : p.getImpactOfAGV())
            {
                if (val > 0)
                {
                    childrenPositiveCount++;
                }
            }
        }
        else if (p.getStart().getName() == "A" || p.getStart().getName() == "L" || p.getStart().getName() == "K" || p.getStart().getName() == "W")
        {
            for (const auto &val : p.getImpactOfAGV())
            {
                if (val > 0)
                {
                    ALKWPositiveCount++;
                }
            }
        }
    }

    double childrenPositivePercentage = static_cast<double>(childrenPositiveCount) / countYounger(pedestrians, 12);
    double ALKWPositivePercentage = static_cast<double>(ALKWPositiveCount) / countALKW(pedestrians);

    return (childrenPositivePercentage > 0.5) || (ALKWPositivePercentage > 0.5);
}

bool majorityNegativeImpact(const vector<Pedestrian> &allPedestrians)
{
    auto pedestrians = assignImpact(allPedestrians);
    int elderNegativeCount = 0;
    int blinderNegativeCount = 0;
    int BFGMENNegativeCount = 0;

    for (const auto &p : pedestrians)
    {
        if (p.getAge() > 60)
        {
            for (const auto &val : p.getImpactOfAGV())
            {
                if (val < 0)
                {
                    elderNegativeCount++;
                }
            }
        }
        else if (p.getStart().getName() == "B" || p.getStart().getName() == "F" || p.getStart().getName() == "G" || p.getStart().getName() == "M" || p.getStart().getName() == "E" || p.getStart().getName() == "N")
        {
            for (const auto &val : p.getImpactOfAGV())
            {
                if (val < 0)
                {
                    BFGMENNegativeCount++;
                }
            }
        }
        else if (p.isBlind())
        {
            for (const auto &val : p.getImpactOfAGV())
            {
                if (val < 0)
                {
                    blinderNegativeCount++;
                }
            }
        }
    }

    double elderNegativePercentage = static_cast<double>(elderNegativeCount) / countOlder(pedestrians, 60);
    double blinderNegativePercentage = static_cast<double>(blinderNegativeCount) / pedestrians.size();
    double BFGMENNegativePercentage = static_cast<double>(BFGMENNegativeCount) / countBFGMEN(pedestrians);

    return (elderNegativePercentage > 0.5) || (blinderNegativePercentage > 0.5) || (BFGMENNegativePercentage > 0.5);
}

// int main()
// {
//     vector<Pedestrian> pedestrians; 
//     pedestrians = assignImpact(pedestrians);

//     for (const auto &p : pedestrians)
//     {
//         const auto &impact = p.getImpactOfAGV();
//         cout << "Impact of AGV on Pedestrian: ";
//         for (const auto &val : impact)
//         {
//             cout << val << " ";
//         }
//         cout << endl;
//     }
//     bool positiveImpact = majorityPositiveImpact(pedestrians);
//     bool negativeImpact = majorityNegativeImpact(pedestrians);

//     cout << "Majority Positive Impact: " << (positiveImpact ? "Yes" : "No") << endl;
//     cout << "Majority Negative Impact: " << (negativeImpact ? "Yes" : "No") << endl;

//     return 0;
// }
