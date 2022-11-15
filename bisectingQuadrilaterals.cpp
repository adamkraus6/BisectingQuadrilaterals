// Mathew Clutter
// Adam Kraus

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

const double EPSILON = .000001;

struct Point
{
    double x, y;
} points[4];

struct Segment
{
    Point a, b;
} segments[4];

struct Vec
{
    double x, y;
};

double bisect(double left, double right);
Point intersect(Segment s1, Segment s2);
double cross(Vec a, Vec b);
double areaOf(Point ps[], int pn);
void sortCW(Point ps[], int pn);
bool compare(Point p1, Point p2, Point c);
double getAngle(Point p, Point c);
Point makePoint(double x, double y);
Segment makeSegment(Point a, Point b);
Vec makeVec(Point a, Point b);

int main(int argc, char **argv)
{
    ifstream fin("quad.in");
    ofstream fout("quad.out");
    int caseNum = 1;

    if (!fin)
    {
        cout << "Bad quad.in" << endl;
        fin.close();
        fout.close();
        return -1;
    }

    if (!fout)
    {
        cout << "Bad quad.out" << endl;
        fin.close();
        fout.close();
        return -1;
    }

    while (true)
    {
        // Will handle blank lines as is :)

        fin >> points[0].x >> points[0].y;

        if (points[0].x == -1 && points[0].y == -1)
        {
            break;
        }

        double left = points[0].x, right = left;

        // calculate left and rightmost point for recursing
        for (int i = 1; i < 4; i++)
        {
            fin >> points[i].x >> points[i].y;

            if (points[i].x < left)
            {
                left = points[i].x;
            }

            if (points[i].x > right)
            {
                right = points[i].x;
            }
        }

        double bi = bisect(left, right);
        // Think precision and width should be good
        cout << setprecision(5) << fixed;
        fout << setprecision(5) << fixed;
        fout << "Case " << caseNum << ": " << bi << endl;
        cout << "Case " << caseNum << ": " << bi << endl;
        caseNum++;
    }

    fin.close();
    fout.close();

    return 0;
}

double bisect(double left, double right)
{
    double mid = (left + right) / 2;

    // make line segments for quad
    for (int i = 0; i < 3; i++)
    {
        segments[i].a = points[i];
        segments[i].b = points[i + 1];
    }
    segments[3].a = points[3];
    segments[3].b = points[0];

    // make vertical line segment to bisect
    Point a = makePoint(mid, 0), b = makePoint(mid, 1000000);
    Segment m = makeSegment(a, b);

    // points making left and right halves of quad
    Point l[8], r[8];
    int ln = 0, rn = 0;

    // for each segment in quad
    for (int i = 0; i < 4; i++)
    {
        // check if intersect with vertical mid segment
        Point inter = intersect(m, segments[i]);

        if (inter.x != 0 || inter.y != 0)
        {
            // intersect, put in some list
            l[ln] = r[rn] = inter;
            ln++;
            rn++;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        // need to catch going through a vertex
        if (points[i].x == mid)
        {
            l[ln] = r[rn] = points[i];
            ln++;
            rn++;
        }

        // add left points
        if (points[i].x < mid)
        {
            l[ln] = points[i];
            ln++;
        }

        // add right points
        if (points[i].x > mid)
        {
            r[rn] = points[i];
            rn++;
        }
    }

    // need to sort points to be clockwise/counterclockwise
    sortCW(l, ln);
    sortCW(r, rn);

    // calculate area on left and right side, inclusive of intersect points
    double leftArea = areaOf(l, ln), rightArea = areaOf(r, rn);

    if (abs(leftArea - rightArea) <= EPSILON)
    {
        return mid;
    }
    else if (leftArea > rightArea)
    {
        // bisect is in left half
        return bisect(left, mid);
    }
    else
    {
        // bisect is in right half
        return bisect(mid, right);
    }
}

Point makePoint(double x, double y)
{
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

Segment makeSegment(Point a, Point b)
{
    Segment s;
    s.a = a;
    s.b = b;
    return s;
}

Vec makeVec(Point a, Point b)
{
    Vec v;
    v.x = b.x - a.x;
    v.y = b.y - a.y;
    return v;
}

Point intersect(Segment s1, Segment s2)
{
    Point p = makePoint(0, 0);

    Point a = s1.a, b = s1.b, c = s2.a, d = s2.b;

    // get first straddle
    Vec ab = makeVec(a, b);
    Vec bc = makeVec(b, c);
    Vec bd = makeVec(b, d);
    double c1 = cross(ab, bc);
    double c2 = cross(ab, bd);
    bool st1 = ((c1 < 0 && c2 > 0) || (c2 < 0 && c1 > 0)) ? true : false;

    // get second straddle
    Vec cd = makeVec(c, d);
    Vec da = makeVec(d, a);
    Vec db = makeVec(d, b);
    double c3 = cross(cd, da);
    double c4 = cross(cd, db);
    bool st2 = ((c3 < 0 && c4 > 0) || (c4 < 0 && c3 > 0)) ? true : false;

    // if both straddle, find intersection point
    if (st1 & st2)
    {
        double tt = (a.x - c.x) * (c.y - d.y) - (a.y - c.y) * (c.x - d.x);
        double tb = (a.x - b.x) * (c.y - d.y) - (a.y - b.y) * (c.x - d.x);
        double t = tt / tb;

        p.x = a.x + t * (b.x - a.x);
        p.y = a.y + t * (b.y - a.y);
    }

    return p;
}

double cross(Vec a, Vec b)
{
    return a.x * b.y - b.x * a.y;
}

double areaOf(Point ps[], int pn)
{
    double area = 0;

    int j = pn - 1;
    for (int i = 0; i < pn; i++)
    {
        area += (ps[j].x + ps[i].x) * (ps[j].y - ps[i].y);
        j = i;
    }

    return abs(area / 2);
}

void sortCW(Point ps[], int pn)
{
    Point center = makePoint(0, 0);

    for (int i = 0; i < pn; i++)
    {
        center.x += ps[i].x;
        center.y += ps[i].y;
    }

    center.x /= pn;
    center.y /= pn;

    for (int i = 0; i < pn; i++)
    {
        ps[i].x -= center.x;
        ps[i].y -= center.y;
    }

    for (int i = 0; i < pn - 1; i++)
    {
        for (int j = 0; j < pn - i - 1; j++)
        {
            if (compare(ps[j], ps[j + 1], center))
            {
                Point temp = ps[j];
                ps[j] = ps[j + 1];
                ps[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < pn; i++)
    {
        ps[i].x += center.x;
        ps[i].y += center.y;
    }
}

bool compare(Point p1, Point p2, Point c)
{
    double ang1 = getAngle(p1, c), ang2 = getAngle(p2, c);
    if (ang1 < ang2)
        return true;

    return false;
}

double getAngle(Point p, Point c)
{
    double ang = atan2(p.y, p.x);
    if (ang <= 0)
        ang += 2 * M_PI;
    return ang;
}