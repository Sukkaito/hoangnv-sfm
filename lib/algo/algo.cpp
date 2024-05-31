#include <bits/stdc++.h>
using namespace std;
double max_y,max_x,min_y,min_x;

void setMinMax(double x, double y){
    if(max_y<y){
        max_y=y;
    }
    if(max_x<x){
        max_x=x;
    }
    if(min_y>y){
        min_y=y;
    }
    if(min_x>x){
        min_x=x;
    }
}
struct point {
    double x;
    double y;
    point(double x,double y){
        this->x = x;
        this->y = y;
        setMinMax( x, y);
    }
    point(){

    }
    bool operator==(const point &other) const {
        return (this->x==other.x && this->y==other.y);
    }
};
struct lineSegment {
    point p;
    point q;
    lineSegment(point p,point q){
        this->p = p;
        this->q = q;
    };
    lineSegment(){

    }
    bool operator==(const lineSegment &other) const {
        return (this->p==other.p && this->q==other.q) ||
               (this->p==other.q && this->q==other.p);
    }
};

typedef std::pair<double,std::pair<int,int> > pq_pair;

double dist(point p, point q){
    //calculate euclidean distance sqrt( (p.x-q.x)^2+(p.y-q.y)^2 )
    return (double) sqrt(pow(p.x-q.x,2.0)+pow(p.y-q.y,2.0));
}

double rightTurn(point p1, point p2, point p3){
    return (p1.y-p2.y)*(p2.x-p3.x)-(p2.y-p3.y)*(p1.x-p2.x);
}

int crosses(lineSegment l1, lineSegment l2){
    if(l1==l2) return -1;

    int returnValue = 0;
    if(l1.p == l2.p) returnValue++;
    if(l1.p == l2.q) returnValue++;
    if(l1.q == l2.p) returnValue++;
    if(l1.q == l2.q) returnValue++;

    if(returnValue>0) return returnValue;

    double rt_1 = rightTurn(l1.p,l1.q,l2.p);
    double rt_2 = rightTurn(l1.p,l1.q,l2.q);
    double rt_3 = rightTurn(l2.p,l2.q,l1.p);
    double rt_4 = rightTurn(l2.p,l2.q,l1.q);

    double r1 = rt_1*rt_2;
    double r2 = rt_3*rt_4;

    if((r1==0 && r2<=0) || (r2==0 && r1<=0)){
        returnValue=10;
    }

    if((r1<=0) &&  (r2<=0)) returnValue = 10;
    return returnValue;
}

int numberOfCrossings(vector<vector<lineSegment> > &polygons, lineSegment l){
    int n=0;
    for(size_t i = 0; i < polygons.size();i++){
        int numberOfvaolation=0;
        for(size_t j=0;j<polygons[i].size();j++){
            int result = crosses(l,polygons[i][j]);
            if(result==-1){
                return 0;
            }
            else if(result==10){
                numberOfvaolation=10;
            }
            else{
                numberOfvaolation+=result;
            }
        }
        if(numberOfvaolation>2){
            n++;
        }
    }
    return n;
}

double dijkstra(vector< vector< double > > &graphDistance, vector<vector< int> > &graph ,vector<int> &route){
    int start = 0;
    size_t end = graph.size()-1;

    route.resize(graph.size());

    //Create a vector to see if we already visited the point
    vector<bool> visited(graph.size());

    //Create a priority queue where pq_pair consists of
    //the distance to the point and the point index in points vector
    priority_queue< tuple<double,int,int> > pq;

    //Put the start point in the queue

    pq.push(make_tuple(0,start,-1));

    //While there a still points we haven't visited we run
    while(!pq.empty()){
        //Get the top point
        tuple<double,int,int> t = pq.top();

        //Remove it
        pq.pop();

        //How far have we travelled until now
        double distanceSoFar = -1*get<0>(t);

        //What point are we at
        int current = get<1>(t);

        int whereFrom = get<2>(t);

        //If we already visited the current continue
        if(visited[current]) continue;

        route[current] = whereFrom;

        //We we have reached the distination return the distance
        if(current == end) return distanceSoFar;

        //Set the current to true in the visited vector
        visited[current] = true;

        //Go through every current we have an edge to and haven't visited
        for(size_t i = 0; i < graph[current].size() ; i++){
            int next = graph[current][i];
            if(visited[next]) continue;

            //calculate the complete distance to that current
            double newdistance = distanceSoFar + graphDistance[current][i];

            //And push it to the queue
            tuple<double,int,int> newTuple = make_tuple(-1*newdistance,next,current);

            pq.push(newTuple);
        }
    }
    return -1;
}

int makeVisabilityGraph(vector< vector < int > > &graph, vector< vector < double > > &graphDistance,vector< vector<int> > &crossesNumber, vector<point> &points){

    //Get how many points we have
    size_t numberOfPoints = points.size();

    //Go through all pairs of points and calculate the distance
    for(size_t i=0;i<graph.size();i++){
        for(size_t j=0;j<numberOfPoints;j++){

            size_t from = i;

            size_t from_point_index = from%numberOfPoints;

            size_t to_point_index = j;

            size_t to = (i/numberOfPoints)*numberOfPoints+crossesNumber[from_point_index][j]*numberOfPoints+j;


            //If it is the same point don't make an edge
            if(graph.size()>to){
                //if(crossesNumber[from][to]==0){
                //Call dist function to calculate the distance
                double distance = dist(points[from_point_index],points[to_point_index]);

                graphDistance[from].push_back(distance);
                graph[from].push_back(to);
            }
        }
    }

    return 0;
}

int calculateNumberOfCrossings(vector < vector < int > > &crossesNumber,vector<vector<lineSegment> > &polygons, vector<point> &points){
    crossesNumber.resize(points.size(),vector<int>(points.size()));
    for(size_t i=0;i<points.size();i++){
        for(size_t j=0;j<points.size();j++){
            lineSegment l;
            l.p = points[i];
            l.q = points[j];

            //Call numberOfCrossings, which
            //suprise suprise counts the number of crossings
            crossesNumber[i][j] = numberOfCrossings(polygons,l);
        }
    }
    return 0;
}

void prepareAlgorithm(vector<point> &diem, vector< vector < lineSegment> > &dagiac)
{
    ifstream file;
    string filename = "data/maphospital.txt";
    file.open(filename);
    if (!file) {
        cout << "can not open!" << endl;
    }
    string line;
    int i = 0;
    while (getline(file, line)) {
        istringstream iss(line);
        double x, y;
        iss>>x>>y;
        point fp = point(x,y);
        point lp = fp;
        diem.push_back(fp);
        while (iss >> x >> y) {
            point cp = point(x,y);
            diem.push_back(cp);
            lineSegment l;
            l.p = lp;
            l.q = cp;
            dagiac[i].push_back(l);
            lp = cp;
        }
        lineSegment l;
        l.p = lp;
        l.q = fp;
        dagiac[i].push_back(l);
        i++;
    }
    file.close();
}

vector<point> findPath(point S, point D)
{
    vector<point> result;
    max_x=max_y=min_y=min_x=0;
    vector< vector < lineSegment> > polygons;
    vector<point> points;
    points.push_back(S);
    polygons.resize(10, vector<lineSegment>());
    /*MAP HERE
    * A (40, 30) (340, 30) (340, 150) (40, 150)
    * L (400, 30) (650, 30) (650, 150) (400, 150)
    * B (710, 30) (960, 30) (960, 150) (710, 150)
    * G (40, 450) (340, 450) (340, 570) (40, 570)
    * K (400, 450) (650, 450) (650, 570) (400, 570)
    * N (710, 450) (960, 450) (960, 570) (710, 570)
    * F (30, 180) (115, 180) (115, 420) (30, 420)
    * E (145, 180) (485, 180) (485, 420) (145, 420)
    * M (515, 180) (855, 180) (855, 420) (515, 420)
    * W (885, 180) (970, 180) (970, 420) (885, 420)  */
    prepareAlgorithm(points, polygons);
    points.push_back(D);
    vector< vector < int > > graph;
    vector< vector < double > > graphDistance;
    vector<int> route;
    vector< vector < int > > crossesNumber;
    size_t numberOfPoints = points.size();
    size_t dimension = numberOfPoints;
    graph.resize(dimension,vector<int>());
    graphDistance.resize(dimension,vector<double>());
    calculateNumberOfCrossings(crossesNumber, polygons, points);
    makeVisabilityGraph(graph, graphDistance, crossesNumber, points);
    double distance = dijkstra(graphDistance,graph,route);
    int current = route.size()-1;
    while(current!=-1){
        point p =  points[current%points.size()];
        result.push_back(p);
        current = route[current];
    }
    return result;
}


