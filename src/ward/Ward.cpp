#include "src/point/Point.cpp"

class Ward{
private: 
string name;   
Point entrant;
Point exit;
vector<Point> walls;

public:
    Ward(){};
    // Setters with input validation (optional, adjust validation as needed)
    void setName(string s){
        name = s;
    }

    void setEntrant(const Point& newEntrant) {
        entrant = newEntrant;
    }

    void setExit(const Point& newExit) {
        exit = newExit;
    }

    void addWall(const Point& newWall) {
        walls.push_back(newWall);
    }

    // Getters
    const Point& getEntrant() const {
        return entrant;
    }

    const Point& getExit() const {
        return exit;
    }

    const vector<Point>& getWalls() const {
        return walls;
    }
    string getName(){
        return name;
    }
};