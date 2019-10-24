#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

//bool debug = true;
bool debug = false;

typedef double CoordinateType;
class Point
{
private:
    CoordinateType xCoord;
    CoordinateType yCoord;
    CoordinateType zCoord;

public:
    Point( CoordinateType x, CoordinateType y, CoordinateType z);
    const void GetAxes(CoordinateType& x, CoordinateType& y, CoordinateType& z) const;
};

Point::Point(CoordinateType x, CoordinateType y, CoordinateType z)
{
    xCoord = x;
    yCoord = y;
    zCoord = z;
}

const void Point::GetAxes(CoordinateType& x, CoordinateType& y, CoordinateType& z) const
{
   x  = xCoord;
   y  = yCoord;
   z  = zCoord;
}

void printPointVector(const vector<Point>& points)
{
    int loop = 0;
    for ( vector<Point>::const_iterator iter = points.begin(); iter != points.end(); iter ++, loop++)
    {
        CoordinateType x , y , z;
        iter->GetAxes(x,y,z);
        cout << "Point " << (loop+1) << " =[" << x << " "<<y<<" " <<z<<" ]"<<endl;
    }

}
void printIntVector(const vector<int>& vertices)
{

    for ( vector<int>::const_iterator iter = vertices.begin(); iter != vertices.end(); iter ++)
    {
        cout << *iter << " ";
    }

}

double circuitLength(const vector<Point> &points, const vector<int> &order)
{
    double totalLength = 0;
    if (debug)
    {
        cout << __func__ << "order"<<endl;
        printIntVector(order);
        cout << __func__ << "order"<<endl;
    }
    for ( vector<int>::const_iterator iter = order.begin(); iter != order.end() ; )
    {
        double length =0 ;
        CoordinateType x1,y1,z1;
        CoordinateType x2,y2,z2;
        points[*iter].GetAxes(x1,y1,z1);
        iter++;
        if (iter == order.end() )
        {
            iter = order.begin();
            points[*iter].GetAxes(x2,y2,z2);
            iter = order.end();
        }  
        else
        {
            points[*iter].GetAxes(x2,y2,z2);
        }
        length = sqrt ( pow((x2 - x1),2) + pow ((y2 - y1), 2) + pow ( (z2 - z1), 2)); 
        totalLength += length;

        if (debug)
        {
            cout << "Point 1 [" << x1 << " "<< y1 <<" "<< z1 << "] "<< "Point 2 [" << x2 << " "<< y2 <<" "<< z2 <<"] "<<"distance" << length<<endl;
        } 
    }

    return totalLength;
}


vector<int> findShortestPath(const vector<Point> &points)
{
    int size = points.size();
    vector<int> vertices,returnVertices;
    double shortestPath = 0;
    int permutationCount = 0;
    for (int loop =0; loop < size; loop ++)
    {
        vertices.push_back(loop);
    }

    do 
    {
        permutationCount++;
        double path = circuitLength(points,vertices);
        if ( shortestPath == 0  || (shortestPath > path )) 
        {
            shortestPath = path;
            returnVertices = vertices;
        } 

        if (debug)
        {
            cout << "Permutations are " <<endl;
            printIntVector(vertices);
            cout << "with distance = "<< path <<endl;
        }
    }while ( next_permutation(vertices.begin() , vertices.end()) ); 

    if (debug)
    {
        cout << "Total permutation = " << permutationCount << endl;
    }
    return returnVertices;
}

int main()
{
    int noOfPoints;
    CoordinateType x, y, z;
    vector<Point> VerticesVector;
    vector<int> shortestVectorPath;
    double shortestDistance = 0;
    cout << "Enter the number of points" << endl;
    cin >> noOfPoints;
    for (int loop =0; loop < noOfPoints;loop++)
    {
        cout << "Enter Point[" << loop<<"]:"<<endl;  
        cin >> x;
        cin >> y;
        cin >> z;
        VerticesVector.push_back(Point(x,y,z));
    }

    printPointVector(VerticesVector);
    shortestVectorPath = findShortestPath(VerticesVector);
    shortestDistance = circuitLength(VerticesVector,shortestVectorPath);
    cout << "Shortest Path is [ ";
    printIntVector(shortestVectorPath);
    cout << "] with distance = " <<  shortestDistance <<endl;
}

