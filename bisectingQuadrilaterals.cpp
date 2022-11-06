// Mathew Clutter
// Adam Kraus

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

struct Point
{
    double x, y;
} points[4];

struct Segment
{
    Point a, b;  
} segments[4];

struct vec
{
    double x, y;
};

double bisect(double left, double right);
Point intersect(Segment s1, Segment s2);
double cross(vec a, vec b);

int main(int argc, char **argv)
{
    ifstream fin("quad.in");
    ofstream fout("quad.out");
    int caseNum = 1;

    if(!fin)
    {
        cout << "Bad quad.in" << endl;
        fin.close();
        return -1;
    }

    if(!fout)
    {
        cout << "Bad quad.out" << endl;
        fout.close();
        return -1;
    }

    while(true)
    {
        fin >> points[0].x >> points[0].y;

        if(points[0].x == -1 && points[0].y == -1)
        {
            break;
        }

        double left = points[0].x, right = left;

        for(int i = 1; i < 4; i++)
        {
            fin >> points[i].x >> points[i].y;

            if(points[i].x < left)
            {
                left = points[i].x;
            }

            if(points[i].x > right)
            {
                right = points[i].x;
            }
        }

        double bi = bisect(left, right);
        // TODO set precision and width stuff
        fout << "Case " << caseNum << ": " << bi << endl;
        cout << "Case " << caseNum << ": " << bi << endl;
        caseNum++;
    }

    fin.close();
    fout.close();
}

double bisect(double left, double right)
{
    double mid = (left + right) / 2;

    // make line segments for quad
    for(int i = 0; i < 3; i++)
    {
        segments[i].a = points[i];
        segments[i].b = points[i+1];
    }
    segments[3].a = points[3];
    segments[3].b = points[0];

    Point a, b;
    a.x = b.x = mid;
    a.y = 0;
    b.y = 1000000;
    Segment m;
    m.a = a;
    m.b = b;

    // for each segment in quad
    for(int i = 0; i < 4; i++)
    {
        // check if intersect with vertical mid segment
        Point inter = intersect(m, segments[i]);

        if(inter.x == 0 && inter.y == 0)
        {
            // no intersect
        }
        else
        {
            // intersect, put in some list
        }

        // may need to catch going through a vertex
    }

    // calculate area on left and right side, inclusive of intersect points

    // if area difference < some small amount
        // return mid as bisecting point
    // else
        // recurse on whichever side has bigger area
    
    return 0;
}

Point intersect(Segment s1, Segment s2)
{
    Point p;
    p.x = 0;
    p.y = 0;

    Point a = s1.a, b = s1.b, c = s2.a, d = s2.b;

    // get first straddle
    // ab
    vec ab;
    ab.x = b.x - a.x;
    ab.y = b.y - a.y;
    // bc
    vec bc;
    bc.x = c.x - b.x;
    bc.y = c.y - b.y;
    // bd
    vec bd;
    bd.x = d.x - b.x;
    bd.y = d.y - b.y;

    // ab x bc
    double c1 = cross(ab, bc);
    // ab x bd
    double c2 = cross(ab, bd);

    bool st1 = ((c1 < 0 && c2 > 0) || (c2 < 0 && c1 > 0)) ? true : false;

    // get second straddle
    // cd
    vec cd;
    cd.x = d.x - c.x;
    cd.y = d.y - c.y;
    // da
    vec da;
    da.x = a.x - d.x;
    da.y = a.y - d.y;
    // db
    vec db;
    db.x = b.x - d.x;
    db.y = b.y - d.y;

    // cd x da
    double c3 = cross(cd, da);
    // cd x db
    double c4 = cross(cd, db);

    bool st2 = ((c3 < 0 && c4 > 0) || (c4 < 0 && c3 > 0)) ? true : false;

    // if both straddle, find intersection point
    if(st1 & st2)
    {
        // TODO calculate intersect point
    }

    return p;
}

double cross(vec a, vec b)
{
    return a.x * b.y - b.x * a.y;
}